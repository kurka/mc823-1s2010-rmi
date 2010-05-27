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

void trata_sigchild(int sig)
{
  pid_t pid;
  int stat;
  while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) printf("child %d ends\n", pid);
}


void cleanbuffer(char *b, int size)
{
  int i = 0;
  
  for (i = 0; i < size; i++)
    b[i] = '\0';
}

int idexists(int id)
{
  int exists = 0;
  /* MySql variables */
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  
  char query[200];
  
  sprintf(query, "SELECT * FROM movies WHERE id=%d", id);
  
  /* Initializes MySql connection */
  if( (conn = mysql_init(NULL)) == NULL)
  {
    fprintf(stderr, "error on mysql_init\n");
    exit(0);
  }
  
  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* MySql Query */
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* Getting results */
  if( (res = mysql_use_result(conn)) == NULL)
  {
    fprintf(stderr, "mysql result error\n");
    exit(0);
  }
  
  if ((row = mysql_fetch_row(res)) != NULL)
    exists = 1;
  else
    exists = 0;
  
  /* Closes MySql connection */
  mysql_close(conn);
  
  return exists;
}

void getinfo(int id, int tipo)
{
  /* MySql variables */
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  
  char query[200];
  double notamedia = 0.0f;
  char msginicio[100], msgfim[100];
  sprintf(msgfim, "********** -------------- *********\n");
  
  switch(tipo)
  {
    case GET_ALL:
      sprintf(query, "SELECT * FROM movies WHERE id=%d", id);
      break;
    case GET_PLOT:
      sprintf(query, "SELECT id, title, plot FROM movies WHERE id=%d", id);
      break;
    case GET_RATE:
      sprintf(query, "SELECT id, title, ratevotes, ratesum FROM movies WHERE id=%d", id);
      break;
  }
  
  /* Initializes MySql connection */
  if( (conn = mysql_init(NULL)) == NULL)
  {
    fprintf(stderr, "error on mysql_init\n");
    exit(0);
  }
  
  
  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* MySql Query */
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* Getting results */
  if( (res = mysql_use_result(conn)) == NULL)
  {
    fprintf(stderr, "mysql result error\n");
    exit(0);
  }
  
  if ((row = mysql_fetch_row(res)) != NULL)
  {
    sprintf(msginicio, "********** FILME ID %05d *********", atoi(row[0]));
    
    switch(tipo)
    {
      case GET_ALL:
        if (atoi(row[8]) != 0)
          notamedia = atof(row[9]) / atoi(row[8]);
        else
          notamedia = 0.0f;
        sprintf(out_buffer, "%s\nTitulo: %s\nSinopse: %s\nDiretor: %s\nEscritor: %s\nData de estreia: %s\nData de estreia no Brasil: %s\nDuracao: %s minutos\nVotos: %s\nNota media: %.2f\nSessoes: %s\n%s\n", msginicio, row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], notamedia, row[10], msgfim);
        break;
      case GET_PLOT:
        sprintf(out_buffer, "%s\nTitulo: %s\nSinopse: %s\n%s\n", msginicio, row[1], row[2], msgfim);
        break;
      case GET_RATE:
        if (atoi(row[2]) != 0)
          notamedia = atof(row[3]) / atoi(row[2]);
        else
          notamedia = 0.0f;
        sprintf(out_buffer, "%s\nTitulo: %s\nVotos: %s\nNota media: %.2f\n%s\n", msginicio, row[1], row[2], notamedia, msgfim);
        break;
    }
  }
  
  /* Closes MySql connection */
  mysql_close(conn);
}

void getall(int connfd, int tipo, struct timeval *timer_end)
{
  /* MySql variables */
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  
  double notamedia = 0.0f;
  int sentbytes = 0, timer_defined = 0;
  char query[200];
  char msginicio[100], msgfim[100];
  sprintf(msgfim, "********** -------------- *********\n");
  
  switch(tipo)
  {
    case GET_ALL:
      sprintf(query, "SELECT * FROM movies");
      break;
    case GET_TITLES:
      sprintf(query, "SELECT id, title FROM movies");
      break;
  }
  
  /* Initializes MySql connection */
  if( (conn = mysql_init(NULL)) == NULL)
  {
    fprintf(stderr, "error on mysql_init\n");
    exit(0);
  }
  
  
  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* MySql Query */
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* Getting results */
  if( (res = mysql_use_result(conn)) == NULL)
  {
    fprintf(stderr, "mysql result error\n");
    exit(0);
  }
  
  while ((row = mysql_fetch_row(res)) != NULL)
  {
    sprintf(msginicio, "********** FILME ID %05d *********", atoi(row[0]));
    
    switch(tipo)
    {
      case GET_ALL:
        if (atoi(row[8]) != 0)
          notamedia = atof(row[9]) / atoi(row[8]);
        else
          notamedia = 0.0f;
        
        /* Timer nao tao preciso, mas suficiente, dado que o query ao banco de dados ja terminou, basta tratar os dados */
        if (!timer_defined)
        {
          gettimeofday(timer_end, NULL);
          timer_defined = 1;
        }
        sprintf(out_buffer, "%s\nTitulo: %s\nSinopse: %s\nDiretor: %s\nEscritor: %s\nData de estreia: %s\nData de estreia no Brasil: %s\nDuracao: %s minutos\nVotos: %s\nNota media: %.2f\nSessoes: %s\n%s\n", msginicio, row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], notamedia, row[10], msgfim);
        
        /* Sends info to client */
        sentbytes = send(connfd, out_buffer, strlen(out_buffer), 0);
        break;
      case GET_TITLES:
        sprintf(out_buffer, "%s\nTitulo: %s\n%s\n", msginicio, row[1], msgfim);
        
        /* Timer nao tao preciso, mas suficiente dado que o query ao banco de dados ja terminou, basta tratar os dados */
        if (!timer_defined)
        {
          gettimeofday(timer_end, NULL);
          timer_defined = 1;
        }
        
        /* Sends info to client */
        sentbytes = send(connfd, out_buffer, strlen(out_buffer), 0);
        break;
    }
      
    
  }
  
  /* Closes MySql connection */
  mysql_close(conn);
}

int getnummovies()
{
  int nummovies = 0;
  /* MySql variables */
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  
  char query[200];
  
  sprintf(query, "SELECT COUNT(id) FROM movies");
  
  /* Initializes MySql connection */
  if( (conn = mysql_init(NULL)) == NULL)
  {
    fprintf(stderr, "error on mysql_init\n");
    exit(0);
  }
  
  
  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* MySql Query */
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* Getting results */
  if( (res = mysql_use_result(conn)) == NULL)
  {
    fprintf(stderr, "mysql result error\n");
    exit(0);
  }
  
  if ((row = mysql_fetch_row(res)) != NULL)
    nummovies = atoi(row[0]);  /* Converts string to int */
  else
    nummovies = 0;
  
  /* Closes MySql connection */
  mysql_close(conn);

  return nummovies;
}

void ratemovie(int id, int nota)
{
  /* MySql variables */
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  
  char query[200];
  
  sprintf(query, "UPDATE movies SET ratevotes=ratevotes+1, ratesum=ratesum+%d WHERE id=%d", nota, id);
  
  /* Initializes MySql connection */
  conn = mysql_init(NULL);
  
  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* MySql Query */
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  
  /* Closes MySql connection */
  mysql_close(conn);
  
  sprintf(out_buffer, "Nota computada.\n");
}

int main()
{
  pid_t pid = (pid_t) 0;
  int recvbytes = 0, sentbytes = 0;
  int i = 0, j = 0, id = 0, nota = 0;
  char *id_str = NULL;
  struct sockaddr_in ssock;
  unsigned int structure_size = sizeof(struct sockaddr_in);
  double totaltime = 0.0f;
  struct timeval timer_start, timer_end;
  
  signal(SIGINT, trata_sigint);
  signal(SIGCHLD, trata_sigchild);
  
  /* Clean buffers */
  cleanbuffer(in_buffer, BUFFER_SIZE + 1);
  cleanbuffer(out_buffer, BUFFER_SIZE + 1);

  /* Creates server listen socket */
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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
  
  if (listen(listenfd, MAX_CLIENTS) != 0)
  {
    fprintf(stderr, "listen error\n");
    exit(0);
  }

  for(;;)
  {
    if ( (connfd = accept(listenfd, (struct sockaddr *)&ssock, &structure_size)) != -1)
      pid = fork();
    if (pid < 0)
    {
      fprintf(stderr, "fork error\n");
      exit(0);
    }
    if (pid == 0)  /* Desvia execucao para o processo filho */
    {
      /* Closes listen socket */
      close(listenfd);
      listenfd = 0;
      
      cleanbuffer(out_buffer, 10*BUFFER_SIZE + 1);
      
      /* Reads query */
      recvbytes = recv(connfd, in_buffer, BUFFER_SIZE, 0);
      if(recvbytes <= 0)
        return(0);
      gettimeofday(&timer_start, NULL);
      
      printf("Server Received: %s\n", in_buffer);
      char opcao[2] = {'\0', '\0'};
      opcao[0] = in_buffer[0];

      switch(atol(opcao))
      {
        case REQUEST_ALL:
          #ifdef DEBUG
          printf("Client asked for all %d movies\n", getnummovies());
          #endif
          getall(connfd, GET_ALL, &timer_end);
          break;
          
        case REQUEST_ONE:
          #ifdef DEBUG
          printf("Client asked for one movie: ");
          #endif
          /* Copy movie id to another string */
          id_str = (char *) malloc(sizeof(char) * (strlen(in_buffer) + 1));
          for (i = 2; i < strlen(in_buffer); i++)
            id_str[i-2] = in_buffer[i];
          id_str[strlen(in_buffer)] = '\0';
          
          /* String to Int */
          id = atoi(id_str);
          #ifdef DEBUG
          printf("%d\n", id);
          #endif
          /* Retrieves movie info */
          getinfo(id, GET_ALL);
          /* Sends info to client */
          if (strlen(out_buffer) == 0)
            sprintf(out_buffer, "Nenhum resultado encontrado.\n\n");
          gettimeofday(&timer_end, NULL);
          sentbytes = send(connfd, out_buffer, strlen(out_buffer), 0);
          
          break;
          
        case REQUEST_TITLES:
          #ifdef DEBUG
          printf("Client asked for all %d titles\n", getnummovies());
          #endif
          getall(connfd, GET_TITLES, &timer_end);
          break;
        
        case REQUEST_PLOT:
          #ifdef DEBUG
          printf("Client asked for one plot: ");
          #endif
          /* Copy movie id to another string */
          id_str = (char *) malloc(sizeof(char) * (strlen(in_buffer) + 1));
          for (i = 2; i < strlen(in_buffer); i++)
            id_str[i-2] = in_buffer[i];
          id_str[strlen(in_buffer)] = '\0';
          
          /* String to Int */
          id = atoi(id_str);
          #ifdef DEBUG
          printf("%d\n", id);
          #endif
          
          getinfo(id, GET_PLOT);
          if (strlen(out_buffer) == 0)
            sprintf(out_buffer, "Nenhum resultado encontrado.\n\n");
          gettimeofday(&timer_end, NULL);
          sentbytes = send(connfd, out_buffer, strlen(out_buffer), 0);
          break;
          
        case REQUEST_RATE:
          #ifdef DEBUG
          printf("Client asked for one rate: ");
          #endif
          /* Copy movie id to another string */
          id_str = (char *) malloc(sizeof(char) * (strlen(in_buffer) + 1));
          for (i = 2; i < strlen(in_buffer); i++)
            id_str[i-2] = in_buffer[i];
          id_str[strlen(in_buffer)] = '\0';
          
          /* String to Int */
          id = atoi(id_str);
          #ifdef DEBUG
          printf("%d\n", id);
          #endif
          
          getinfo(id, GET_RATE);
          if (strlen(out_buffer) == 0)
            sprintf(out_buffer, "Nenhum resultado encontrado.\n\n");
          gettimeofday(&timer_end, NULL);
          sentbytes = send(connfd, out_buffer, strlen(out_buffer), 0);
          break;
          
        case REQUEST_VOTE:
          #ifdef DEBUG
          printf("Client asked to vote: ");
          #endif
          /* Copy movie id and rate to another string */
          id_str = (char *) malloc(sizeof(char) * (strlen(in_buffer) + 1));
          
          /* Reads movie id */
          for (i = 2; i < strlen(in_buffer); i++)
          {
            if(in_buffer[i] == ' ')
              break;
            id_str[i-2] = in_buffer[i];
          }
          id_str[i++ - 2] = '\0';
          /* String to Int */
          id = atoi(id_str);
          #ifdef DEBUG
          printf("ID=%d ", id);
          #endif
          
          /* Reads rate */
          j = 0;
          while (in_buffer[i] != '\0')
            id_str[j++] = in_buffer[i++];
          id_str[j] = '\0';
          nota = atoi(id_str);
          #ifdef DEBUG
          printf("RATE=%d\n", nota);
          #endif
          
          if (idexists(id))
            ratemovie(id, nota);
          else
            sprintf(out_buffer, "ID inexistente.\n");
          gettimeofday(&timer_end, NULL);
          sentbytes = send(connfd, out_buffer, strlen(out_buffer), 0);
          break;
          
        default:
          sprintf(out_buffer, "Opcao indefinida\n\n");
          gettimeofday(&timer_end, NULL);
          sentbytes = send(connfd, out_buffer, strlen(out_buffer), 0);
      }
      totaltime = (timer_end.tv_sec - timer_start.tv_sec) + (timer_end.tv_usec - timer_start.tv_usec)/1000000.0;
      cleanbuffer(out_buffer, 10*BUFFER_SIZE+1);
      sprintf(out_buffer, "\nSERVERTIME\t%.6lf\n", totaltime);
      sentbytes = send(connfd, out_buffer, strlen(out_buffer) + 1, 0);
      
      
      shutdown(connfd, 2);
      close(connfd);
      connfd = 0;
      
      if (id_str != NULL)
        free(id_str);
      exit(0);
    }
    else
      printf("child %d starts\n", pid);
  }

  return 0;
}
