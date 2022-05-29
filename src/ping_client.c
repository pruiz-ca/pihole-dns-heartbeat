#include "dns_heartbeat.h"

int  ping_client(struct sockaddr_in *address, struct timeval *tmout, int last_state) {
	int		sockfd;
	int		res;
	int		yes = 1;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error. Socket could not be created\n");
		exit (1);
  	}

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)tmout, sizeof(*tmout));
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)tmout, sizeof(*tmout));

	res = connect(sockfd, (struct sockaddr *)address, sizeof(*address));

	if (res < 0 && last_state == 0) { // FAIL
		if (DEBUG == 1)
			printf("Failed\n");
		system("ssh router nvram set dnsfilter_enable_x=0");
	}
	else if (res >= 0 && last_state != 0) { // SUCCESS
		if (DEBUG == 1)
			printf("Success\n");
		close(sockfd);
		system("ssh router nvram set dnsfilter_enable_x=1");
	}
	return res;
}
