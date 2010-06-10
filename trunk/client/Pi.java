package client;

import compute.Task;
import java.util.Formatter;
import java.io.Serializable;
import java.sql.*;

public class Pi implements Task<String>, Serializable {
  private static final long serialVersionUID = 227L;

  private final int opcao, id, nota;

  /* Variaveis com dados para conexao MySQL */
  private static final String userName = "rodrigo_yasuda";
  private static final String password = "teste123";
  private static final String url = "jdbc:mysql://mysql.tolstenko.net:3306/rodrigo_yasuda?useUnicode=yes&characterEncoding=UTF-8&user=" + userName + "&password=" + password;

  public Pi(int opcao, int id, int nota) {
    this.opcao = opcao;
    this.id = id;
    this.nota = nota;
  }

  public String execute() {
    return computePi(opcao, id, nota);
  }

  public static String computePi(int opcao, int id, int nota) {
    /* Inicio do tempo do servidor aqui */
    long start = System.nanoTime();
    /* Processar pedido aqui */
    String resultado = new String();
    System.out.println("Server received: " + opcao + " " + id + " " + nota);
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
    /* Termino do tempo do servidor aqui */
    long end = System.nanoTime();
    double dif = (end - start)/1000000000F;
    resultado = resultado + "SERVERTIME\t" + dif;
    System.out.println(resultado);
    return resultado;
  }
}
