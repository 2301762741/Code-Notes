import java.sql.Connection;
import java.sql.DriverManager;

public class JDCcufils {
    public static Connection getConnection() throws Exception {
        //注册数据库驱动
        Class.forName("com.mysql.jdbc.Driver");
        //链接数据库
        Connection con = (java.sql.Connection) DriverManager.getConnection("jdbc:mysql://localhost:3306/student", "root", "root");
        
        return con;
    }
    public static void main(String[] args) throws Exception {
        Connection con = getConnection();
        System.out.println(con);
    }
}
