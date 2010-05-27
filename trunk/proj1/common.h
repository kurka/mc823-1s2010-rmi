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

/* Informacoes para o banco de dados MySql */
//char *server = "mysql.tolstenko.net";  /* Server IP/address */
//char *user = "rodrigo_yasuda";      /* MySql username */
//char *password = "teste123";     /* MySql password */
//char *database = "rodrigo_yasuda";  /* MySql database name */
char *server = "localhost";  /* Server IP/address */
char *user = "rodrigo";      /* MySql username */
char *password = "test";     /* MySql password */
char *database = "rodrigo";  /* MySql database name */
