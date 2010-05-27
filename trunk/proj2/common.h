#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/time.h>

#define PORT 50000
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

#define REQUEST_ALL 1
#define REQUEST_ONE 2
#define REQUEST_TITLES 3
#define REQUEST_PLOT 4
#define REQUEST_VOTE 5
#define REQUEST_RATE 6


#define GET_ALL 0
#define GET_TITLES 1
#define GET_PLOT 2
#define GET_RATE 3


int idexists(int id, char *out_buffer);
void getinfo(int id, int tipo, char *out_buffer);
void getall(int connfd, int tipo, struct timeval *timer_end, char *out_buffer, struct sockaddr *pcliaddr, socklen_t len);
int getnummovies();
void ratemovie(int id, int nota, char *out_buffer);