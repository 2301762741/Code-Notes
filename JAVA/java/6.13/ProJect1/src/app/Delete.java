package app;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

import dao.StudentDao;
import domain.Student;

public class Delete extends JFrame {

	public Delete(int id) throws Exception {
		setSize(350, 300);
		setLocation(400, 400);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new FlowLayout());
		JLabel label1 = new JLabel("删除信息");
		JLabel label2 = new JLabel("学号");
		JLabel label3 = new JLabel("姓名");
		JLabel label4 = new JLabel("性别");
		JLabel label5 = new JLabel("成绩");
		//设置增加信息几个字的x,y，长和宽
		
		JTextField field1 = new JTextField(12);
		JTextField field2 = new JTextField(12);
		JTextField field3 = new JTextField(12);
		JTextField field4 = new JTextField(12);
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
		//获取数据
		List<Student> list = StudentDao.finaAll();
		for(Student stu:list) {
			//找到该学号的学生
			if(stu.getSid() == id) {
				//将它们填入文本框中
				field1.setText(String.valueOf(stu.getSid()));
				field2.setText(stu.getSname());
				field3.setText(stu.getSsex());
				field4.setText(String.valueOf(stu.getScore()));
			}
		}
		JButton btn1 = new JButton("删除");
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
				Student stu = new Student(id, name, sex, score);
				try {
					//添加进去
					new StudentDao().dele(stu);
					Show.show();//展示出来
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
					Show.show();//展示出来
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
	}
	}
	

