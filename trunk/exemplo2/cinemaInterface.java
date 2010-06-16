import java.rmi.*;

public interface cinemaInterface extends Remote
{
	String consulta(int opcao, int id, int nota) throws RemoteException;
}
