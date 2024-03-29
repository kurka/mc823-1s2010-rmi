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
      String resposta = "";
      Connection conn = null;
      try {
        /* Conexao com servidor MySQL */
        Class.forName ("com.mysql.jdbc.Driver").newInstance();
        conn = DriverManager.getConnection(url);
        
        Statement stmt;
        ResultSet rs;
        stmt = conn.createStatement();
        try
        {
          rs = stmt.executeQuery("SELECT * from movies");
          while(rs.next()){
            resposta += "\n\n********** FILME ID " + rs.getString("id") + " *********";
            resposta += "\nTitulo: " + rs.getString("title");
            resposta += "\nSinopse: " + rs.getString("plot");
            resposta += "\nDiretor: " + rs.getString("director");
            resposta += "\nEscritor: " + rs.getString("writer");
            resposta += "\nData de Estreia: " + rs.getString("releasedate");
            resposta += "\nData de Estreia no Brasil: " + rs.getString("releasedatebr");
            resposta += "\nDuracao: " + rs.getString("runtime") + " minutos";
            resposta += "\nVotos: " + rs.getString("ratevotes");
            if (rs.getInt("ratevotes") > 0)
            {
              double media = rs.getInt("ratesum") / (double)rs.getInt("ratevotes");
              resposta += "\nNota media: " + media;
            }
            else
              resposta += "\nNota media: 0.0";
            resposta += "\nSessoes: " + rs.getString("session");
          }//end while loop

        }catch(Exception e)
        {
          e.printStackTrace();
        }
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
      return resposta + "\n";
    }

    private static String UmFilme(int id)
    {
      String resposta = "";
      Connection conn = null;
      try {
        /* Conexao com servidor MySQL */
        Class.forName ("com.mysql.jdbc.Driver").newInstance();
        conn = DriverManager.getConnection(url);
        
        Statement stmt;
        ResultSet rs;
        stmt = conn.createStatement();
        try
        {
          rs = stmt.executeQuery("SELECT * from movies WHERE id=" + id);
          if(rs.next()){
            resposta += "\n\n********** FILME ID " + rs.getString("id") + " *********";
            resposta += "\nTitulo: " + rs.getString("title");
            resposta += "\nSinopse: " + rs.getString("plot");
            resposta += "\nDiretor: " + rs.getString("director");
            resposta += "\nEscritor: " + rs.getString("writer");
            resposta += "\nData de Estreia: " + rs.getString("releasedate");
            resposta += "\nData de Estreia no Brasil: " + rs.getString("releasedatebr");
            resposta += "\nDuracao: " + rs.getString("runtime") + " minutos";
            resposta += "\nVotos: " + rs.getString("ratevotes");
            if (rs.getInt("ratevotes") > 0)
            {
              double media = rs.getInt("ratesum") / (double)rs.getInt("ratevotes");
              resposta += "\nNota media: " + media;
            }
            else
              resposta += "\nNota media: 0.0";
            resposta += "\nSessoes: " + rs.getString("session");
          }//end while loop

        }catch(Exception e)
        {
          e.printStackTrace();
        }
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
      return resposta + "\n";
    }

    private static String TodosTitulos()
    {
      String resposta = "";
      Connection conn = null;
      try {
        /* Conexao com servidor MySQL */
        Class.forName ("com.mysql.jdbc.Driver").newInstance();
        conn = DriverManager.getConnection(url);
        
        Statement stmt;
        ResultSet rs;
        stmt = conn.createStatement();
        try
        {
          rs = stmt.executeQuery("SELECT * from movies");
          while(rs.next()){
            resposta += "\n\n********** FILME ID " + rs.getString("id") + " *********";
            resposta += "\nTitulo: " + rs.getString("title");
          }//end while loop

        }catch(Exception e)
        {
          e.printStackTrace();
        }
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
      return resposta + "\n";
    }

    private static String UmaSinopse(int id)
    {
      String resposta = "";
      Connection conn = null;
      try {
        /* Conexao com servidor MySQL */
        Class.forName ("com.mysql.jdbc.Driver").newInstance();
        conn = DriverManager.getConnection(url);
        
        Statement stmt;
        ResultSet rs;
        stmt = conn.createStatement();
        try
        {
          rs = stmt.executeQuery("SELECT * from movies WHERE id=" + id);
          if(rs.next()){
            resposta += "\n\n********** FILME ID " + rs.getString("id") + " *********";
            resposta += "\nTitulo: " + rs.getString("title");
            resposta += "\nSinopse: " + rs.getString("plot");
          }//end while loop

        }catch(Exception e)
        {
          e.printStackTrace();
        }
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
      return resposta + "\n";
    }

    private static String DarNota(int id, int nota)
    {
      String resposta = "";
      Connection conn = null;
      try {
        /* Conexao com servidor MySQL */
        Class.forName ("com.mysql.jdbc.Driver").newInstance();
        conn = DriverManager.getConnection(url);
        
        Statement stmt;
        stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE);
        try
        {
          stmt.executeUpdate("UPDATE movies SET ratevotes=ratevotes+1, ratesum=ratesum+" + nota + " WHERE id=" + id);
          resposta = "\nNota computada.";
        }catch(Exception e)
        {
          e.printStackTrace();
        }
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
      return resposta + "\n";
    }


    private static String NotaMedia(int id)
    {
      String resposta = "";
      Connection conn = null;
      try {
        /* Conexao com servidor MySQL */
        Class.forName ("com.mysql.jdbc.Driver").newInstance();
        conn = DriverManager.getConnection(url);
        
        Statement stmt;
        ResultSet rs;
        stmt = conn.createStatement();
        try
        {
          rs = stmt.executeQuery("SELECT * from movies WHERE id=" + id);
          if(rs.next()){
            resposta += "\n\n********** FILME ID " + rs.getString("id") + " *********";
            resposta += "\nTitulo: " + rs.getString("title");
            resposta += "\nVotos: " + rs.getString("ratevotes");
            if (rs.getInt("ratevotes") > 0)
            {
              double media = rs.getInt("ratesum") / (double)rs.getInt("ratevotes");
              resposta += "\nNota media: " + media;
            }
            else
              resposta += "\nNota media: 0.0";
          }//end while loop

        }catch(Exception e)
        {
          e.printStackTrace();
        }
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
      return resposta + "\n";
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
          break;
        case 2:
          resposta = UmFilme(id);
          break;
        case 3:
          resposta = TodosTitulos();
          break;
        case 4:
          resposta = UmaSinopse(id);
          break;
        case 5:
          resposta = DarNota(id, nota);
          break;
        case 6:
          resposta = NotaMedia(id);
          break;
        default:
          resposta = "\nOpcao incorreta\n";
          break;
      }
      System.out.println(opcao);

      /* Termino do tempo do servidor aqui */
      long end = System.nanoTime();
      double dif = (end - start)/1000000000F;
      resposta += "\nSERVERTIME\t" + dif + "\n";
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