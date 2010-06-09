package client;

import compute.Task;
import java.util.Formatter;
import java.io.Serializable;
import java.sql.*;
//import com.mysql.jdbc.Driver;

public class Pi implements Task<String>, Serializable {

    private static final long serialVersionUID = 227L;

    /** digits of precision after the decimal point */
    private final int opcao, id, nota;    
    /**
     * Construct a task to calculate pi to the specified
     * precision.
     */
    public Pi(int opcao, int id, int nota) {
        this.opcao = opcao;
        this.id = id;
        this.nota = nota;
    }

    /**
     * Calculate pi.
     */
    public String execute() {
        return computePi(opcao, id, nota);
    }

    public static String computePi(int opcao, int id, int nota) {
        /* Inicio do tempo do servidor aqui */
        long start = System.nanoTime();

        /* Processar pedido aqui */
        String resultado = new String();

           Connection conn = null;

           try
           {
                String userName = "rodrigo_yasuda";
   		String password = "teste123";
   		String url = "jdbc:mysql://mysql.tolstenko.net:3306/rodrigo_yasuda?useUnicode=yes&characterEncoding=UTF-8&user=" + userName + "&password=" + password;
                System.out.println("aqui");
   		Class.forName ("com.mysql.jdbc.Driver").newInstance();
                System.out.println("aqui2");
   		//conn = DriverManager.getConnection("jdbc:mysql://localhost/rodrigo_yasuda", "rodrigo_yasuda", "teste123");
                conn = DriverManager.getConnection(url);
                System.out.println("aqui3");
                System.out.println("Connected to the database");
                conn.close();
                System.out.println("Disconnected from database");



               //System.out.println ("Database connection established");
           }
           catch (Exception e)
           {
               e.printStackTrace();
               System.err.println ("Cannot connect to database server");
           }
           finally
           {
               if (conn != null)
               {
                   try
                   {
                       conn.close ();
                       System.out.println ("Database connection terminated");
                   }
                   catch (Exception e) { /* ignore close errors */ }
               }
           }



        /* Termino do tempo do servidor aqui */
        long end = System.nanoTime();
        double dif = (end - start)/1000000000F;
        resultado = resultado + "SERVERTIME\t" + dif;
        System.out.println(resultado);
        return resultado;
    }
}
