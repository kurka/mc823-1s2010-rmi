import java.rmi.*;
import java.rmi.registry.*;
import java.rmi.server.*;
import java.net.*;
import java.util.Formatter;
import java.io.Serializable;
import java.sql.*;

public class RmiServer extends java.rmi.server.UnicastRemoteObject
implements cinemaInterface
{
    int      thisPort = 50000;
    String   thisAddress;
    Registry registry;    // rmi registry for lookup the remote objects.
    // This method is called from the remote client by the RMI.
    // This is the implementation of the “ReceiveMessageInterface”.
    private static final String userName = "rodrigo_yasuda";
    private static final String password = "teste123";
    private static final String url = "jdbc:mysql://mysql.tolstenko.net:3306/rodrigo_yasuda?useUnicode=yes&characterEncoding=UTF-8&user=" + userName + "&password=" + password;
    
    public String TodosDados()
    {
      Connection conn = null;
      try {
        /* Conexao com servidor MySQL */
        Class.forName ("com.mysql.jdbc.Driver").newInstance();
        conn = DriverManager.getConnection(url);
        //System.out.println("Connected to the database");
        conn.close();
        //System.out.println("Disconnected from database");
      }
      catch (Exception e) {
        e.printStackTrace();
        System.err.println ("Cannot connect to database server");
      }
      finally {
        if (conn != null)
        {
          try {
            conn.close ();
            //System.out.println ("Database connection terminated");
          } catch (Exception e) { /* ignore close errors */ }
        }
      }
      return "bodega";
    }

    public String consulta(int opcao, int id, int nota) throws RemoteException
    {
      /* Inicio do tempo do servidor aqui */
      long start = System.nanoTime();
      /* Processar pedido aqui */
      String resposta = new String();
      System.out.println("Server received: " + opcao + " " + id + " " + nota);
    

      switch(opcao)
      {
        case 1:
          resposta = TodosDados();
          resposta = "Todos filmes" + "\n";
          break;
        default:
          resposta = "Opcao incorreta";
          break;
      }
      System.out.println(opcao);

      /* Termino do tempo do servidor aqui */
      long end = System.nanoTime();
      double dif = (end - start)/1000000000F;
      resposta = resposta + "SERVERTIME\t" + dif + "\n";
      System.out.println(resposta);
    
      return resposta;
    }
 
    public RmiServer() throws RemoteException
    {
        try{
            // get the address of this host.
            thisAddress= (InetAddress.getLocalHost()).toString();
        }
        catch(Exception e){
            throw new RemoteException("can't get inet address.");
        }

        System.out.println("this address="+thisAddress+",port="+thisPort);
        try{
        // create the registry and bind the name and object.
        registry = LocateRegistry.createRegistry( thisPort );
            registry.rebind("Servidor", this);
        }
        catch(RemoteException e){
        throw e;
        }
    }
   
    static public void main(String args[])
    {
        try{
        RmiServer s=new RmiServer();
    }
    catch (Exception e) {
           e.printStackTrace();
           System.exit(1);
    }
     }
}