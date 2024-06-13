package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import app.Show;
import jframe.JDCcufils;

public class UserDao {
    public static void check(String username, char[] password) throws Exception{
        String sql = "select * from user where username = ? and password = ?";
        Connection con = JDCcufils.getConnection();  // 获取连接
        PreparedStatement prep = con.prepareStatement(sql); // 预编译sql语句
        prep.setString(1, username);  // 设置参数
        prep.setString(2, String.valueOf(password));
        //执行查询后，生成结果集
        ResultSet rs = prep.executeQuery();
       
        if(rs.next()){  // 如果结果集有数据，则登录成功
            Show.show();
        }
    }
}
