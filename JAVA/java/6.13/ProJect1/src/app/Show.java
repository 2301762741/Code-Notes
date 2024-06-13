package app;

import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import java.awt.FlowLayout;


import dao.StudentDao;
import domain.Student;

public class Show {
    public static void show( ) throws Exception{
        JFrame jf = new JFrame("登录窗口");  // 创建窗口
        jf.setSize(400, 300);  // 设置窗口大小
        jf.setLocation(350, 300); // 设置窗口位置
        jf.setVisible(true);  // 设置窗口可见
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 设置窗口关闭方式   
        // 获取 JFrame 的内容窗格并在其上设置布局
        // Container contentPane = jf.getContentPane();
        // contentPane.setLayout(new FlowLayout());
        jf.setLayout(new FlowLayout());
        JButton add = new JButton("增加学生");
        JButton del = new JButton("删除学生");
        JButton modi = new JButton("修改学生");
        JButton find = new JButton("查询学生");
        jf.add(add);
        jf.add(del);
        jf.add(modi);
        jf.add(find);
        //将所有学生查询出来
        List<Student> list = StudentDao.finaAll();  //进入StudentDao中去查询数据
        //定义表格显示的字段名
        String[] title = {"学号","姓名","性别"," 成绩"};
        //数据显示为几行4列
        Object[][] data = new Object[list.size()][4];
        for(int i = 0;i<list.size();i++){
            //获取集合中某一行的数据
            Student stu = list.get(i);
            //将数据放入二维数组中
            Object[] s = {stu.getSid(),stu.getSname(),stu.getSsex(),stu.getScore()};
            data[i] = s; //将数据放入二维数组中
        }
        //绘制表格
        JTable table = new JTable(data,title);
        
        //查询学生
        find.addActionListener(e -> {
            //设置表格可见
            table.setVisible(true);
            //将表格添加到面板中显示
            JScrollPane jsp = new JScrollPane(table);
            jf.add(jsp);
        });

        //添加学生
        add.addActionListener(e -> {
            try {
                new Add();
            }catch (Exception e1) {
                e1.printStackTrace();
            }
        });

        //删除学生
        del.addActionListener(e -> {
            try {
                new Delete(1);
            }catch (Exception e1) {
                e1.printStackTrace();
            }
        });

        //修改学生
        modi.addActionListener(e -> {
            try {
                new Modify(1);
            }catch (Exception e1) {
                e1.printStackTrace();
            }
        });
    }
}
