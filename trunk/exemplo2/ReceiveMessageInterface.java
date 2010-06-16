import java.rmi.*;

public interface ReceiveMessageInterface extends Remote

{
	String receiveMessage(int opcao, int id, int nota) throws RemoteException;
}
