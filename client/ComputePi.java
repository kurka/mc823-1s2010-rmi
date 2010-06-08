package client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.*;
import compute.Compute;
import java.sql.*;

import com.mysql.jdbc.Driver;

public class ComputePi {
    public static void main(String args[]) {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            String name = "Compute";
            Registry registry = LocateRegistry.getRegistry(args[0]);
            Compute comp = (Compute) registry.lookup(name);
            int opcao = -1, id = -1, nota = -1;
            if (args.length >= 2)
              opcao = Integer.parseInt(args[1]);
            if (args.length >= 3)
              id = Integer.parseInt(args[2]);
            if (args.length >= 4)
              nota = Integer.parseInt(args[3]);
            Pi task = new Pi(opcao, id, nota);

            /* Marca inicio do tempo do cliente aqui */
            long start = System.nanoTime(); 
            String pi = comp.executeTask(task);
            /* Terminar tempo do cliente aqui */
            long end = System.nanoTime();
            /* Imprime resultado */
            System.out.println(pi);
            /* Imprime tempo do cliente */
            System.out.format("TOTALTIME\t%.6f\n", (end-start)/1000000000F);

        } catch (Exception e) {
            System.err.println("ComputePi exception:");
            e.printStackTrace();
        }
    }    
}
