package app;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import java.awt.FlowLayout;

import dao.UserDao;

public class Login {
    public static void main(String[] args) throws Exception {
        JFrame jf = new JFrame("登录窗口");
        jf.setSize(350, 300); // 设置窗口大小
        jf.setLocation(400, 300); // 设置窗口位置
        jf.setVisible(true); // 设置窗口可见
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 设置窗口关闭方式
        jf.setLayout(new FlowLayout());

        //标签
        JLabel juser = new JLabel("用户名：");
        //文本框
        JTextField jTextField = new JTextField(8);
        //标签
        JLabel jPass = new JLabel("密  码：");
        //文本框
        JPasswordField jPassField = new JPasswordField(8);
        //按钮
        JButton jButton = new JButton("登录");
        //添加组件
        jf.add(juser);  // 添加标签
        jf.add(jTextField);
        jf.add(jPass);
        jf.add(jPassField);
        jf.add(jButton);
        //单击按钮时
        jButton.addActionListener(e->{
            //获取用户输入账号和密码
            String username = jTextField.getText();
            char[] password = jPassField.getPassword();
            try {
                UserDao.check(username, password);
                
            } catch (Exception e1) {
                e1.printStackTrace();
            }
        });
        
    }
}
