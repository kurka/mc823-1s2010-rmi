#include "common.h"

//DNS RESOLVER
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/select.h>


char out_buffer[BUFFER_SIZE + 1];
char in_buffer[10*BUFFER_SIZE + 1];


void cleanbuffer(char *b)
{
  int i = 0;
  
  for (i = 0; i <= BUFFER_SIZE; i++)
    b[i] = '\0';
}

void printmenu()
{
  printf("[%d] Listar todas as informacoes de todos os filmes\n", REQUEST_ALL);
  printf("[%d] Listar filme por id\n", REQUEST_ONE);
  printf("[%d] Listar todos os filmes por titulo\n", REQUEST_TITLES);
  printf("[%d] Obter sinopse pelo id\n", REQUEST_PLOT);
  printf("[%d] Dar nota para filme\n", REQUEST_VOTE);
  printf("[%d] Obter nota media e numero de clientes\n", REQUEST_RATE);
  printf("Qualquer outra opcao: sair do programa\n");
  printf("Digite a opcao desejada.\n");
}

int getint(char *msg)
{
  int r = -1;
  while (r <= 0)
  {
    printf("\n%s\n", msg);
    scanf(" %d", &r);
  }
  return r;
}

void dg_cli(FILE *fp, int ssock, const struct sockaddr *pservaddr, socklen_t servlen)
{
  int recvbytes = 0, n = 0, rv = 0;
  struct timeval tv;
  fd_set readfds;
  
  sendto(ssock, out_buffer, strlen(out_buffer)+1, 0, pservaddr, servlen);
  
  FD_ZERO(&readfds);
  FD_SET(ssock, &readfds);
  
  n = ssock+1;
  
  // wait until either socket has data ready to be recv()d (timeout 10.5 secs)
  tv.tv_sec = 10;
  tv.tv_usec = 500000;
  
  rv = select(n, &readfds, NULL, NULL, &tv);
  if (rv == -1)
    fprintf(stderr, "error in select");
  else if (rv == 0)
    printf("\nSERVERTIME TIMEOUT\n");
  else
  {
    if (FD_ISSET(ssock, &readfds)) {
      while ( (recvbytes = recv(ssock, in_buffer, 10*BUFFER_SIZE, 0)) > 0)
      {
        in_buffer[recvbytes] = 0;
        fputs(in_buffer, stdout);
        if (in_buffer[recvbytes-1] == 0)
          break;
      }
    }
  
  }
  /*
  while ( (recvbytes = recvfrom(ssock, in_buffer, 10*BUFFER_SIZE, 0, NULL, NULL)) > 0)
  {
    in_buffer[recvbytes] = 0;
    fputs(in_buffer, stdout);
    if (in_buffer[recvbytes-1] == 0)
      break;
  }*/
}

int main(int argc, char** argv)
{
  int sockfd;
  struct sockaddr_in ssock;
  
  /* buffer para guardar a opcao selecionada */
  char opcao[2] = {'\0', '\0'};
  /* variaveis para guardar a nota e id do filme */
  int nota = -1, id = 0;
  
  /* variaveis para controle do tempo */
  double totaltime = 0.0f;
  struct timeval timer_start, timer_end;
  
  /* variaveis para resolucao de nomes e conexao com o servidor */
  struct hostent* dns_resolver;
  
  if (argc < 2 || argc > 5)
  {
    fprintf(stderr, "Modo de usar: ./client IP/endereco [opcao] [id] [nota]\n");
    exit(1);
  }
  
  cleanbuffer(out_buffer);
  
  /* Obter argumentos da linha de comando */
  if (argc > 2)
    opcao[0] = argv[2][0];
  if (argc > 3)
    id = atol(argv[3]);
  if (argc > 4)
    nota = atol(argv[4]);
  
  dns_resolver = gethostbyname(argv[1]);
  
  bzero(&ssock, sizeof(ssock));
  ssock.sin_family = AF_INET;
  ssock.sin_port = htons(PORT);
  ssock.sin_addr = *((struct in_addr *) dns_resolver->h_addr);
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  
  if (opcao[0] == '\0')
  {
    printmenu();
    
    opcao[0] = getchar();
    while(getchar() != '\n');
  }
  
  switch(atol(opcao))
  {
    case REQUEST_ALL:
      sprintf(out_buffer, "%d", REQUEST_ALL);
      break;
    case REQUEST_ONE:
      if (id == 0)
        id = getint("Digite o ID do filme:");
      sprintf(out_buffer, "%d %d", REQUEST_ONE, id);
      break;
    case REQUEST_TITLES:
      sprintf(out_buffer, "%d", REQUEST_TITLES);
      break;
    case REQUEST_PLOT:
      if (id == 0)
        id = getint("Digite o ID do filme:");
      sprintf(out_buffer, "%d %d", REQUEST_PLOT, id);
      break;
    case REQUEST_VOTE:
      if (id == 0)
        id = getint("Digite o ID do filme:");
      if (nota == -1)
        while ((nota = getint("Digite uma nota de 0 a 10:")) > 10);
        sprintf(out_buffer, "%d %d %d", REQUEST_VOTE, id, nota);
      break;
    case REQUEST_RATE:
      if (id == 0)
        id = getint("Digite o ID do filme:");
      sprintf(out_buffer, "%d %d", REQUEST_RATE, id);
      break;
    default:
      return 0;
      break;
  }
  
  /* Marca tempo antes da mensagem ser enviada */
  gettimeofday(&timer_start, NULL);
  
  dg_cli(stdin, sockfd, (struct sockaddr *) &ssock, sizeof(ssock));
  
  /* Marca tempo apos receber resposta */
  gettimeofday(&timer_end, NULL);
  
  totaltime = (timer_end.tv_sec - timer_start.tv_sec) + (timer_end.tv_usec - timer_start.tv_usec)/1000000.0;
  printf("TOTALTIME\t%.6lf\n", totaltime);
  
  return(0);
}
