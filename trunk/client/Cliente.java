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
		/* variaveis para guardar a nota e id do filme */
		int nota = -1, id = 0, opcao = -1;
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));  
		
		String name = "Compute";
		Registry registry = LocateRegistry.getRegistry(args[0]);
		Compute comp = (Compute) registry.lookup(name);
  
		if (args.length < 2 || args.length > 4)
		{
			System.err.println("Modo de usar: ./client [opcao] [id] [nota]");
			exit(1);
		}
  
		/* Obter argumentos da linha de comando */
		if (args.lenght > 1)
			opcao = Integer.parseInt(args[1])
		if (args.lenght > 2)
			id = Integer.parseInt(args[2]);
		if (args.lenght > 3)
			nota = Integer.parseInt(args[3]);
  
  
		if (opcao[0] == -1)
		{
			printmenu();

			String input = reader.readLine();  
			opcao = Integer.parseInt(input);  
		}
  
		switch(opcao)
		{
			case REQUEST_ALL:
				out_buffer = "" + REQUEST_ALL;
				break;
			case REQUEST_ONE:
				if (id == 0)
					id = getint("Digite o ID do filme:");
				out_buffer = REQUEST_ONE + " " + id;
				break;
			case REQUEST_TITLES:
				out_buffer = "" + REQUEST_TITLES;
				break;
			case REQUEST_PLOT:
				if (id == 0)
					id = getint("Digite o ID do filme:");
				out_buffer = REQUEST_PLOT + " " + id;
				break;
			case REQUEST_VOTE:
				if (id == 0)
					id = getint("Digite o ID do filme:");
				if (nota == -1)
					while ((nota = getint("Digite uma nota de 0 a 10:")) > 10);
				out_buffer = REQUEST_PLOT + " " + id + " " + nota;
				break;
			case REQUEST_RATE:
				if (id == 0)
					id = getint("Digite o ID do filme:");
				out_buffer = REQUEST_RATE + " " + id;
				break;
			default:
				return;
				break;
		}
 
		//criar o task!
        String ret = comp.executeTask(task);
  
		return(0);
	}    

	
	private void printmenu()
	{
		System.out.println("[%d] Listar todas as informacoes de todos os filmes", REQUEST_ALL);
		System.out.println("[%d] Listar filme por id", REQUEST_ONE);
		System.out.println("[%d] Listar todos os filmes por titulo", REQUEST_TITLES);
		System.out.println("[%d] Obter sinopse pelo id", REQUEST_PLOT);
		System.out.println("[%d] Dar nota para filme", REQUEST_VOTE);
		System.out.println("[%d] Obter nota media e numero de clientes", REQUEST_RATE);
		System.out.println("Qualquer outra opcao: sair do programa");
		System.out.println("Digite a opcao desejada.");
	}
	
	private int getint(String msg)
	{
		int r = -1;
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));  
		
		while (r <= 0)
		{
			String input = reader.readLine();  
			r = Integer.parseInt(input);  
			System.out.println(msg);
		}
		return r;
	}

}
