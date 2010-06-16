import java.rmi.*;
import java.rmi.registry.*;
import java.net.*;

public class RmiClient
{
    static public void main(String args[])
    {
       cinemaInterface rmiServer;
       Registry registry;
       String serverAddress=args[0];
       String serverPort=args[1];
       String text=args[2];
       System.out.println("sending "+text+" to "+serverAddress+":"+serverPort);
       try{
           // get the “registry”
           registry=LocateRegistry.getRegistry(
               serverAddress,
               (new Integer(serverPort)).intValue()
           );
           // look up the remote object
           rmiServer=
              (cinemaInterface)(registry.lookup("Servidor"));
           // call the remote method
           System.out.println(rmiServer.consulta(1, 2, 3));
       }
       catch(RemoteException e){
           e.printStackTrace();
       }
       catch(NotBoundException e){
           e.printStackTrace();
       }
    }
}