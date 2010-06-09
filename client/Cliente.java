package client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.*;
import compute.Compute;
import java.sql.*;

import com.mysql.jdbc.Driver;

public class Cliente {
    public static void main(String args[]) {
		/* variaveis de controle de envio e recebimento de dados e do socket */
		int sentbytes = 0, recvbytes = 0, connfd = 0;
		/* buffers de entrada e saida */
		String in_buffer, out_buffer;
		/* buffer para guardar a opcao selecionada */
		char[] opcao = {'\0', '\0'}
		/* variaveis para guardar a nota e id do filme */
		int nota = -1, id = 0;
		/* variaveis para controle do tempo */
  
		/* variaveis para resolucao de nomes e conexao com o servidor */
		//struct hostent* dns_resolver;
		//struct sockaddr_in ssock;

		String name = "Compute";
		Registry registry = LocateRegistry.getRegistry(args[0]);
		Compute comp = (Compute) registry.lookup(name);
  
		if (args.length < 2 || args.length > 4)
		{
			fprintf(stderr, "Modo de usar: ./client [opcao] [id] [nota]\n");
			exit(1);
		}
  
		/* Obter argumentos da linha de comando */
		if (args.lenght > 1)
			opcao[0] = args[1][0];
		if (args.lenght > 2)
			id = Integer.parseInt(args[2]);
		if (args.lenght > 3)
			nota = Integer.parseInt(args[3]);
  
		/* Limpar buffers */
		//cleanbuffer(in_buffer);
		//cleanbuffer(out_buffer);
  
  
		if (opcao[0] == '\0')
		{
			printmenu();

			//opcao[0] = getchar();
			//while(getchar() != '\n');
		}
  
		/*switch(atol(opcao))*/
		/*{*/
			/*case REQUEST_ALL:*/
				/*sprintf(out_buffer, "%d", REQUEST_ALL);*/
				/*break;*/
			/*case REQUEST_ONE:*/
				/*if (id == 0)*/
					/*id = getint("Digite o ID do filme:");*/
				/*sprintf(out_buffer, "%d %d", REQUEST_ONE, id);*/
				/*break;*/
			/*case REQUEST_TITLES:*/
				/*sprintf(out_buffer, "%d", REQUEST_TITLES);*/
				/*break;*/
			/*case REQUEST_PLOT:*/
				/*if (id == 0)*/
					/*id = getint("Digite o ID do filme:");*/
				/*sprintf(out_buffer, "%d %d", REQUEST_PLOT, id);*/
				/*break;*/
			/*case REQUEST_VOTE:*/
				/*if (id == 0)*/
					/*id = getint("Digite o ID do filme:");*/
				/*if (nota == -1)*/
					/*while ((nota = getint("Digite uma nota de 0 a 10:")) > 10);*/
				/*sprintf(out_buffer, "%d %d %d", REQUEST_VOTE, id, nota);*/
				/*break;*/
			/*case REQUEST_RATE:*/
				/*if (id == 0)*/
					/*id = getint("Digite o ID do filme:");*/
				/*sprintf(out_buffer, "%d %d", REQUEST_RATE, id);*/
				/*break;*/
			/*default:*/
				/*return 0;*/
				/*break;*/
		/*}*/
  
        String ret = comp.executeTask(task);
  
		return(0);
	}    
}
