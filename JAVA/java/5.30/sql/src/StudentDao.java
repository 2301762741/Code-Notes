import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class StudentDao{
    //数据查询
    public void searchStudent() throws Exception{
        //装学生的集合对象
        List<Student> list = new ArrayList<Student>();
        //获取链接对象
        Connection con = JDCcufils.getConnection();
        //根据链接对象创造操作数据库的对象
        Statement stmt = conn.createStatement();
        String sql = "select * from student";
        //根据操作数生成结果集
        ResultSet rs = stmt.executeQuery(sql);
        //循环
        while(rs.next())
        {
            Student s = new Student();
            s.setSid(rs.getInt("sid"));
            s.setSname(rs.getString("sname"));
            s.setSage(rs.getInt("sage"));
            s.setSsex(rs.getString("ssex"));
            list.add(s);
        }

        //遍历集合
        for(Student s:list)
        {
            System.out.println(s.getSid()+" "+s.getSname()+" "+s.getSage()+" "+s.getSsex());
        }

    }

    //数据增加
    public Boolean insertStudent(Student s) throws Exception{
        //创建链接对象
        Connection con = JDCcufils.getConnection();
        //创建操作数据库对象
        String sql = "insert into student values(?,?,?,?)";
        PreparedStatement ps = con.prepareStatement(sql);
        ps.setInt(1,s.getSid());
        ps.setString(2,s.getSname());
        ps.setString(3,s.getSsex());
        ps.setInt(4,s.getSage());
        int i = ps.executeUpdate();
        if(i>0)
        {
            System.out.println("数据添加成功");
            return true;
        }else
        {
            System.out.println("数据添加失败");
            return false;
        }
    }



    //数据删除
    public Boolean delete(Student student) throws Exception{
         //创建链接对象
         Connection con = JDCcufils.getConnection();
         //创建操作数据库对象
         String sql = "delete from student where sid = ?";
         PreparedStatement ps = con.prepareStatement(sql);
         ps.setString(1,student.getSname());//设置名字
         int i = ps.executeUpdate();
         if(i>0){
             System.out.println("数据删除成功");
             return true;
         }else{
             System.out.println("数据删除失败");
             return false;
         }
    }

    //数据修改
    public Boolean update(Student s) throws Exception{
        //数据库连接
        Connection conn = JDCcufils.getConnection();
        String sql = "update student set sname=?,ssex=?,sage=? where sid=?";  //sql语句 通过sid修改 姓名性别年龄
        PreparedStatement pst = conn.prepareStatement(sql);
        pst.setString(1, "小陈");
        pst.setString(2, "男");
        pst.setInt(3, 18);
        if(pst.executeUpdate()>0)
        {
            return true;
        }else
        {
            return false;
        }
    }
    
}
