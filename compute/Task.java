package compute;

import java.sql.*;
import com.mysql.jdbc.Driver;

public interface Task<T> {
    T execute();
}
