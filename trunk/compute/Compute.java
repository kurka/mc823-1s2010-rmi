package compute;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.sql.*;

public interface Compute extends Remote {
    <T> T executeTask(Task<T> t) throws RemoteException;
}
