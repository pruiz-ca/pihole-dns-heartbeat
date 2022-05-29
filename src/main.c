#include "dns_heartbeat.h"

int   main(int argc, char **argv) {
	struct sockaddr_in	address;
	struct timeval		tmout;
	int					last_state = -1;
	int					sleep_time = 0;

	input_check(&argc, argv, &sleep_time);
	fill_values(&address, &tmout, argv[1]);

	while (1) {
		last_state = ping_client(&address, &tmout, last_state);
		sleep (sleep_time);
	}

	return (0);
}
