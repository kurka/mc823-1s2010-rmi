package client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.*;
import compute.Compute;

public class ComputePi {
    public static void main(String args[]) {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            String name = "Compute";
            Registry registry = LocateRegistry.getRegistry(args[0]);
            Compute comp = (Compute) registry.lookup(name);
            Pi task = new Pi(Integer.parseInt(args[1]), Integer.parseInt(args[2]), Integer.parseInt(args[3]));

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
