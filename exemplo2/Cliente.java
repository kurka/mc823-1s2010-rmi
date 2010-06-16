import java.io.*;
import java.rmi.*;
import java.rmi.registry.*;
import java.net.*;


public class Cliente {
    
	private static final int PORTA = 50000;
	private static final int REQUEST_ALL = 1;
	private static final int REQUEST_ONE = 2;
	private static final int REQUEST_TITLES = 3;
	private static final int REQUEST_PLOT = 4;
	private static final int REQUEST_VOTE = 5;
	private static final int REQUEST_RATE = 6;


	
	public static void main(String args[]) {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
			int nota = -1, id = 0, opcao = -1;
			cinemaInterface servidor;
			Registry registry;
			String serverAddress;
			int serverPort= PORTA;
			String retorno = "";

			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));  

			if (args.length < 2 || args.length > 4)
			{
				System.err.println("Modo de usar: java cliente <endereco-servidor> [opcao] [id] [nota]");
				System.exit(1);
			}

			/* Obter argumentos da linha de comando */
			serverAddress = args[0];
			if (args.length > 1)
				opcao = Integer.parseInt(args[1]);
			if (args.length > 2)
				id = Integer.parseInt(args[2]);
			if (args.length > 3)
				nota = Integer.parseInt(args[3]);


			if (opcao == -1)
			{
				printmenu();
				String input = reader.readLine();  
				opcao = Integer.parseInt(input);  
			}

			switch(opcao)
			{
				case REQUEST_ALL:
					break;
				case REQUEST_ONE:
					if (id == 0)
						id = getint("Digite o ID do filme:");
					break;
				case REQUEST_TITLES:
					break;
				case REQUEST_PLOT:
					if (id == 0)
						id = getint("Digite o ID do filme:");
					break;
				case REQUEST_VOTE:
					if (id == 0)
						id = getint("Digite o ID do filme:");
					if (nota == -1)
						while ((nota = getint("Digite uma nota de 0 a 10:")) > 10);
					break;
				case REQUEST_RATE:
					if (id == 0)
						id = getint("Digite o ID do filme:");
					break;
				default:
					return;
			}


			// pega o “registry”
			registry=LocateRegistry.getRegistry(
					serverAddress, serverPort
					);
			// encontra o objeto remoto
			servidor=
				(cinemaInterface)(registry.lookup("Servidor"));

			/* Marca inicio do tempo do cliente aqui*/
			long start = System.nanoTime(); 

			// envia e processa requisicao
			retorno = servidor.consulta(opcao, id, nota);

			/* Terminar tempo do cliente aqui (apos receber resposta da requisicao)*/
			long end = System.nanoTime();
				

			System.out.println("Recebi: " + retorno);
        
			
			/* Imprime tempo do cliente */
			double dif = (end-start)/1000000000F;
			System.out.println("TOTALTIME\t" + dif);
		
		} catch (Exception e) {
            System.err.println("Cliente exception:");
            e.printStackTrace();
        }
		  
	}    

	
	private static void printmenu()
	{
		System.out.println("["+ REQUEST_ALL +"] Listar todas as informacoes de todos os filmes");
		System.out.println("["+ REQUEST_ONE +"] Listar filme por id");
		System.out.println("["+ REQUEST_TITLES +"] Listar todos os filmes por titulo");
		System.out.println("["+ REQUEST_PLOT +"] Obter sinopse pelo id");
		System.out.println("["+ REQUEST_VOTE +"] Dar nota para filme");
		System.out.println("["+ REQUEST_RATE +"] Obter nota media e numero de clientes");
		System.out.println("Qualquer outra opcao: sair do programa");
		System.out.println("Digite a opcao desejada.");
	}
	
	private static int getint(String msg)
	{
		int r = -1;
		try{
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));  

			while (r <= 0)
			{
				String input = reader.readLine();  
				r = Integer.parseInt(input);  
				System.out.println(msg);
			}
		} catch(Exception e){
			System.err.println("Getint exception:");
			e.printStackTrace();
		}
		return r;
	}

}
