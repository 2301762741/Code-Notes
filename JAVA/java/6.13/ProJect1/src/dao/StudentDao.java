package dao;


import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import domain.Student;
import jframe.JDCcufils;

public class StudentDao {
    public static List<Student> finaAll() throws Exception{
        //创建查询语句
        String sql = "select * from student";
        //获取连接对象
        Connection con = JDCcufils.getConnection();
        //生成操作数据库的prep对象
        PreparedStatement prep = con.prepareStatement(sql);
        //执行查询的动作,生成一个结果集对象
        ResultSet rs = prep.executeQuery();
        //创建一个空的集合,装的是学生类
        ArrayList<Student> list = new ArrayList<Student>();
        //遍历结果集
        while(rs.next()){
            int id = rs.getInt("sid");
            String name = rs.getString("sname");
            String sex = rs.getString("ssex");
            int score = rs.getInt("score");
            //将查到的信息构建个学生对象
            Student stu = new Student(id,name,sex,score);
            list.add(stu);
        }
        return list;
    }
    //增加
	public boolean add(Student stu) throws Exception {
		Connection con = JDCcufils.getConnection();
		String sql="insert into student(sid,sname,ssex,score) values(?,?,?,?)";
		PreparedStatement prep = con.prepareStatement(sql);
		prep.setInt(1, stu.getSid());
		prep.setString(2, stu.getSname());
		prep.setString(3, stu.getSsex());
		prep.setInt(4, stu.getScore());
		int update = prep.executeUpdate();
		if(update>0) {
			return true;
		}else {
			return false;
		}
        
	}
	//删除
	public boolean dele(Student stu) throws Exception {
		Connection con = JDCcufils.getConnection();
		String sql="delete from student where sid=?";
		PreparedStatement prep = con.prepareStatement(sql);
		prep.setInt(1, stu.getSid());
		int dele = prep.executeUpdate();
		if(dele>0) {
			return true;
		}else {
			return false;
		}
		
	}
	//修改
	public boolean modify(Student stu) throws Exception {
		
		Connection con = JDCcufils.getConnection();
		String sql="update student set sname=?,ssex=?,score=? where sid=?";
		PreparedStatement prep = con.prepareStatement(sql);
		prep.setString(1, stu.getSname());
		prep.setString(2, stu.getSsex());
		prep.setInt(3, stu.getScore());
		prep.setInt(4,stu.getSid());
		int modify = prep.executeUpdate();
		if(modify>0) {
			return true;
		}else {
			return false;
		}
		
	}

}
