#ifndef DNSHEARTBEAT_H
# define DNSHEARTBEAT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <sys/socket.h>

# ifndef PORT
#  define PORT 53
# endif

# ifndef DEBUG
#  define DEBUG 0
# endif

int		ping_client(struct sockaddr_in *address, struct timeval *tmout, int last_state);
void	fill_values(struct sockaddr_in *address, struct timeval *tmout, char *ip);
void	input_check(const int *argc, char **argv, int *sleep_time);

#endif
