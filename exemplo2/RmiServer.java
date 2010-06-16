import java.rmi.*;
import java.rmi.registry.*;
import java.rmi.server.*;
import java.net.*;

 

public class RmiServer extends java.rmi.server.UnicastRemoteObject

implements ReceiveMessageInterface

{
    int      thisPort = 50000;
    String   thisAddress;
    Registry registry;    // rmi registry for lookup the remote objects.

 

    // This method is called from the remote client by the RMI.

    // This is the implementation of the “ReceiveMessageInterface”.

    public String receiveMessage(int opcao, int id, int nota) throws RemoteException
    {
        System.out.println(opcao);
        return "teste";
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
            registry.rebind("rmiServer", this);
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