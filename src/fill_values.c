#include "dns_heartbeat.h"

void  fill_values(struct sockaddr_in *address, struct timeval *tmout, char *ip) {
	uint16_t	port = PORT;

	address->sin_family = AF_INET;
	address->sin_port = htons(port);
	inet_pton(AF_INET, ip, &address->sin_addr);

	tmout->tv_sec = 1;
	tmout->tv_usec = 0;
}
