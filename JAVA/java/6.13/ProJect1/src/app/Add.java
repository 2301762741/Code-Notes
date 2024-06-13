package app;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import dao.StudentDao;
import domain.Student;

public class Add extends JFrame{
	public Add() {
		setSize(350, 300);
		setLocation(400, 400);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new FlowLayout());
		JLabel label1 = new JLabel("增加信息");
		JLabel label2 = new JLabel("学号");
		JLabel label3 = new JLabel("姓名");
		JLabel label4 = new JLabel("性别");
		JLabel label5 = new JLabel("成绩");
		//设置增加信息几个字的x,y，长和宽
		
		JTextField field1 = new JTextField(12);
		JTextField field2 = new JTextField(12);
		JTextField field3 = new JTextField(12);
		JTextField field4 = new JTextField(12);
		//添加控件到窗口
		add(label1);
		add(label2);
		add(field1);
		add(label3);
		add(field2);
		add(field4);
		add(label4);
		add(field3);
		add(label5);
		add(field4);
		JButton btn1 = new JButton("增加");
		JButton btn2 = new JButton("返回");
		add(btn1);
		add(btn2);
		//增加事件
		btn1.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				int id = Integer.parseInt(field1.getText());
				String name = field2.getText();
				String sex = field3.getText();
				int score = Integer.parseInt(field4.getText());
				//获取文本框中的数据，并封装到对象中
				Student stu = new Student(id, name, sex, score);
				try {
					//将所有的数据查出来
					List<Student> list = StudentDao.finaAll();
					for(Student li:list) {//遍历集合
						if(li.getSid() == id) {//判断该账号是否在集合中存在
							//显示提示框
							JOptionPane.showMessageDialog(null, "该账号存在");
							return;
						}
					}
					//增加学生
					new StudentDao().add(stu);
					JOptionPane.showMessageDialog(null, "添加成功");
					Show.show();//返回开始界面
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				
			}
		});
		//返回事件
	    btn2.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					Show.show();//返回开始界面
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		
	}
// 	public static void main(String[] args) {
// 		Add add = new Add();
// 	}
}
