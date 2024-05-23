import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.ResultSet;

/***********sql代码借鉴JAVA目录下MySQL_Notes**********/

public class _1sql{
    public static void main(String[] args) throws Exception {
        //1.注册数据库驱动
        Class.forName("com.mysql.jdbc.Driver");
        //2.通过DriverManager获取数据库连接
        String url = "jdbc:mysql://localhost:3306/student?characterEncoding="+"utf8&useSSL=true";
        //3.使用Connection获取Statement对象
        Connection con = (Connection) DriverManager.getConnection(url, "root", "root");
        System.out.println(con);
        //4.使用Statement执行SQL语句操作结果集
        /*ResultSet rs = con.createStatement().executeQuery(sql); //其中sql为sql语句 */

            //插入表数据
            String sql1 = "insert into student values(4,'小芳','女',21)";
            int pan = con.createStatement().executeUpdate(sql1);
            if(pan>0)
                System.out.println("增加成功");
            

            // //删除表数据
            // String sql2 = "delete from student where sid = 4";
            // con.createStatement().executeUpdate(sql2);
            // System.out.println("删除数据成功");

            // //修改表数据
            // String sql3 = "update student set sname = '小明' where sid = 1";
            // System.out.println(con.createStatement().executeUpdate(sql3));
            // System.out.println("修改数据成功");

            //查所有student表中的信息 
            String sql = "select * from student";
            /**/ResultSet rs = con.createStatement().executeQuery(sql);
            while(rs.next()){
                int sid = rs.getInt("sid"); //学号
                String sname = rs.getString("sname");
                String ssex = rs.getString("ssex");
                //打印所有信息
                System.out.println(sid+" "+sname+" "+ssex);
            }
        //5.回收资源
        rs.close();
        con.close();
    }
}
