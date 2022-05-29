#include "dns_heartbeat.h"

void  input_check(const int *argc, char **argv, int *sleep_time) {
	struct	sockaddr_in address;
	int		res;

	if (*argc != 3) {
		printf("usage: ./dnsf_heartbeat [pihole/adguard ip] [sleep time in seconds (1-3600)]\n");
		exit (1);
	}

	res = inet_pton(AF_INET, argv[1], &(address.sin_addr));
	if (res < 1) {
		printf("Error. Invalid IP (x.x.x.x)\n");
		exit (1);
	}

	*sleep_time = atoi(argv[2]);
	if (*sleep_time < 1 || *sleep_time > 3600) {
		printf("Error. Invalid Sleep time (1-3600)\n");
		exit (1);
	}
}
