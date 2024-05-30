

public class Text {
    public static  void main(String[] args) throws Exception {
        //查询学生
            StudentDao Dao = new StudentDao();
            Dao.searchStudent();
        //插入数据
        //     Student student1 = new Student(1,"张三","男",20);
        //     Boolean pan = Dao.insertStudent(student1); //插入数据返回值
        //     //判断是否成功
        //     if(pan){
        //         System.out.println("插入成功");
        //     }else{
        //         System.out.println("插入失败");
        //     }
        // //删除数据
        //     Student student2 = new Student();
        //     student2.setSid(1);
        //     Boolean pan2 = Dao.delete(student2);
        //     if(pan2){
        //         System.out.println("删除成功");
        //     }else{
        //         System.out.println("删除失败");
        //     }
        // //修改数据
        //     Student student3 = new Student();
        //     student3.setSid(1);
        //     student3.setSname("张三");
        //     student3.setSsex("男");
        //     student3.setSage(20);
        //     Boolean pan3 = Dao.update(student3);
        //     if(pan3){
        //         System.out.println("修改成功");
        //     }else{
        //         System.out.println("修改失败");
        //     }
    }  
}
