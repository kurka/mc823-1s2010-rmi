#include "common.h"
#include <mysql.h>


/* Informacoes para o banco de dados MySql */
//char *server = "mysql.tolstenko.net";  /* Server IP/address */
//char *user = "rodrigo_yasuda";      /* MySql username */
//char *password = "teste123";     /* MySql password */
//char *database = "rodrigo_yasuda";  /* MySql database name */
char *server = "localhost";  /* Server IP/address */
char *user = "rodrigo";      /* MySql username */
char *password = "test";     /* MySql password */
char *database = "rodrigo";  /* MySql database name */

int idexists(int id, char *out_buffer)
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

void getinfo(int id, int tipo, char *out_buffer)
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
  case GET_ALL:  /* Query por todas informacoes */
    sprintf(query, "SELECT * FROM movies WHERE id=%d", id);
    break;
  case GET_PLOT:  /* Query por apenas id, titulo e sinopse */
    sprintf(query, "SELECT id, title, plot FROM movies WHERE id=%d", id);
    break;
  case GET_RATE:  /* Query por id, titulo, numero de votos e soma de votos */
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
  
  if ((row = mysql_fetch_row(res)) != NULL)  /* Le a proxima linha do resultado */
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

void getall(int connfd, int tipo, struct timeval *timer_end, char *out_buffer, struct sockaddr *pcliaddr, socklen_t len)
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
        sendto(connfd, out_buffer, strlen(out_buffer), 0, pcliaddr, len);
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
        sendto(connfd, out_buffer, strlen(out_buffer), 0, pcliaddr, len);
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

void ratemovie(int id, int nota, char *out_buffer)
{
  /* MySql variables */
  MYSQL *conn;
  
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
