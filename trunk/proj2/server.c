#include "common.h"
#include <signal.h>
#include <sys/wait.h>
#include <mysql.h>

/* Buffers de entrada e saida */
char in_buffer[BUFFER_SIZE + 1];
char out_buffer[10 * BUFFER_SIZE + 1];
int listenfd = 0, connfd = 0;

void trata_sigint(int sig)
{
  if (listenfd != 0)
    close(listenfd);
  if (connfd != 0)
    close(connfd);
  printf("\nClosing server.\n");
  exit(0);
}

void cleanbuffer(char *b, int size)
{
  int i = 0;
  
  for (i = 0; i < size; i++)
    b[i] = '\0';
}

int new_connection(int sockfd, char *recvmsg, int n, struct sockaddr *pcliaddr, socklen_t len)
{
  int i = 0, j = 0, id = 0, nota = 0;
  char *id_str = NULL;
  double totaltime = 0.0f;
  struct timeval timer_start, timer_end;
  int sentbytes = 0, recvbytes = 0;
  
  cleanbuffer(out_buffer, 10*BUFFER_SIZE + 1);
  
  recvbytes = n;
  if(recvbytes <= 0)
    return 0;
  gettimeofday(&timer_start, NULL);
  
  printf("Server Received: %s\n", recvmsg);
  char opcao[2] = {'\0', '\0'};
  opcao[0] = recvmsg[0];
  
  switch(atol(opcao))
  {
    case REQUEST_ALL:  /* Pedido por todas informacoes de todos os filmes */
      #ifdef DEBUG
      printf("Client asked for all %d movies\n", getnummovies());
      #endif
      getall(sockfd, GET_ALL, &timer_end, out_buffer, pcliaddr, len);
      
      //sendto(sockfd, out_buffer, strlen(out_buffer), 0, pcliaddr, len);
      break;
      
    case REQUEST_ONE:  /* Pedido por todas informacoes de um unico filme */
      #ifdef DEBUG
      printf("Client asked for one movie: ");
      #endif
      /* Copy movie id to another string */
      id_str = (char *) malloc(sizeof(char) * (strlen(recvmsg) + 1));
      for (i = 2; i < strlen(recvmsg); i++)
        id_str[i-2] = recvmsg[i];
      id_str[strlen(recvmsg)] = '\0';
      
      /* String to Int */
      id = atoi(id_str);
      #ifdef DEBUG
      printf("%d\n", id);
      #endif
      /* Retrieves movie info */
      getinfo(id, GET_ALL, out_buffer);
      /* Sends info to client */
      if (strlen(out_buffer) == 0)
        sprintf(out_buffer, "Nenhum resultado encontrado.\n\n");
      gettimeofday(&timer_end, NULL);
      sendto(sockfd, out_buffer, strlen(out_buffer), 0, pcliaddr, len);
      
      break;
      
    case REQUEST_TITLES:  /* Pedido por todos os titulos e ids de filmes */
      #ifdef DEBUG
      printf("Client asked for all %d titles\n", getnummovies());
      #endif
      getall(sockfd, GET_TITLES, &timer_end, out_buffer, pcliaddr, len);
      break;
      
    case REQUEST_PLOT:  /* Pedido por sinopse de filme especifico */
      #ifdef DEBUG
      printf("Client asked for one plot: ");
      #endif
      /* Copy movie id to another string */
      id_str = (char *) malloc(sizeof(char) * (strlen(recvmsg) + 1));
      for (i = 2; i < strlen(recvmsg); i++)
        id_str[i-2] = recvmsg[i];
      id_str[strlen(recvmsg)] = '\0';
      
      /* String to Int */
      id = atoi(id_str);
      #ifdef DEBUG
      printf("%d\n", id);
      #endif
      
      getinfo(id, GET_PLOT, out_buffer);
      if (strlen(out_buffer) == 0)
        sprintf(out_buffer, "Nenhum resultado encontrado.\n\n");
      gettimeofday(&timer_end, NULL);
      sendto(sockfd, out_buffer, strlen(out_buffer), 0, pcliaddr, len);
      break;
      
    case REQUEST_RATE:  /* Pedido para dar nota em filme */
      #ifdef DEBUG
      printf("Client asked for one rate: ");
      #endif
      /* Copy movie id to another string */
      id_str = (char *) malloc(sizeof(char) * (strlen(recvmsg) + 1));
      for (i = 2; i < strlen(recvmsg); i++)
        id_str[i-2] = recvmsg[i];
      id_str[strlen(recvmsg)] = '\0';
      
      /* String to Int */
      id = atoi(id_str);
      #ifdef DEBUG
      printf("%d\n", id);
      #endif
      
      getinfo(id, GET_RATE, out_buffer);
      if (strlen(out_buffer) == 0)
        sprintf(out_buffer, "Nenhum resultado encontrado.\n\n");
      gettimeofday(&timer_end, NULL);
      sendto(sockfd, out_buffer, strlen(out_buffer), 0, pcliaddr, len);
      break;
      
    case REQUEST_VOTE:  /* Pedido pelo numero de votos e nota media de um filme */
      #ifdef DEBUG
      printf("Client asked to vote: ");
      #endif
      /* Copy movie id and rate to another string */
      id_str = (char *) malloc(sizeof(char) * (strlen(recvmsg) + 1));
      
      /* Reads movie id */
      for (i = 2; i < strlen(recvmsg); i++)
      {
        if(recvmsg[i] == ' ')
          break;
        id_str[i-2] = recvmsg[i];
      }
      id_str[i++ - 2] = '\0';
      /* String to Int */
      id = atoi(id_str);
      #ifdef DEBUG
      printf("ID=%d ", id);
      #endif
      
      /* Reads rate */
      j = 0;
      while (recvmsg[i] != '\0')
        id_str[j++] = recvmsg[i++];
      id_str[j] = '\0';
      nota = atoi(id_str);
      #ifdef DEBUG
      printf("RATE=%d\n", nota);
      #endif
      
      if (idexists(id, out_buffer))
        ratemovie(id, nota, out_buffer);
      else
        sprintf(out_buffer, "ID inexistente.\n");
      gettimeofday(&timer_end, NULL);
      sendto(sockfd, out_buffer, strlen(out_buffer), 0, pcliaddr, len);
      break;
      
    default:
      sprintf(out_buffer, "Opcao indefinida\n\n");
      gettimeofday(&timer_end, NULL);
      sendto(sockfd, out_buffer, strlen(out_buffer), 0, pcliaddr, len);
  }
  totaltime = (timer_end.tv_sec - timer_start.tv_sec) + (timer_end.tv_usec - timer_start.tv_usec)/1000000.0;
  cleanbuffer(out_buffer, 10*BUFFER_SIZE+1);
  sprintf(out_buffer, "\nSERVERTIME\t%.6lf\n", totaltime);
  sendto(sockfd, out_buffer, strlen(out_buffer) + 1, 0, pcliaddr, len);
  
  
  shutdown(connfd, 2);
  close(connfd);
  connfd = 0;
  
  if (id_str != NULL)
    free(id_str);
  
  return 0;
}

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
  int n;
  socklen_t len;
  char msg[BUFFER_SIZE];
  for(;;)
  {
    len = clilen;
    n = recvfrom(sockfd, msg, BUFFER_SIZE, 0, pcliaddr, &len);
    if(msg[n-1] == '\n') msg[n-1] = 0;
    new_connection(sockfd, msg, n, pcliaddr, len);
  }
}

int main()
{
  struct sockaddr_in ssock, csock;
  
  signal(SIGINT, trata_sigint);
  
  /* Clean buffers */
  cleanbuffer(in_buffer, BUFFER_SIZE + 1);
  cleanbuffer(out_buffer, BUFFER_SIZE + 1);

  /* Creates server listen socket */
  if ((listenfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    fprintf(stderr, "error creating listen socket\n");
    exit(0);
  }
  
  ssock.sin_family = AF_INET;
  ssock.sin_addr.s_addr = INADDR_ANY;
  ssock.sin_port = htons(PORT);
  memset(&(ssock.sin_zero), '\0', 8);

  if (bind(listenfd, (struct sockaddr *) &ssock, sizeof(ssock)) != 0)
  {
    fprintf(stderr, "bind error\n");
    exit(0);
  }
  
  dg_echo(listenfd, (struct sockaddr *) &csock, sizeof(csock));
  
  return 0;
}
