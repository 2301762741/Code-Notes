package UDP;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

/****************************************
               循环发送数据
 ***************************************/

class ProesSendr {
    public static void main(String[] args) throws Exception{
        Dreceive receive = new Dreceive();  //创建接受的类对象线程
        Dsender sender = new Dsender();    //创建发送的类对象线程
        //开启线程
        receive.start();
        sender.start();
    }
}

/**
 * Receive Thread 接受线程
 */
class Dreceive extends Thread {
    @Override
    public void run() {
        try {
            try (//1.创建接受套接字
            DatagramSocket ds = new DatagramSocket(5001)) {
                //2.创建数据包
                byte[] buf= new byte[1024];
                DatagramPacket dp =new DatagramPacket(buf,buf.length);
                //3.接受数据
                while (true) {
                     ds.receive(dp);
                //4.打印数据
                String str = new String(dp.getData(),0,dp.getLength());
                String ip = dp.getAddress().getHostAddress();
                int port = dp.getPort();
                System.out.println(str+"from"+ip+"端口号:"+port);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }  
    }
}
/**
 * Sender Thread 发送线程
 */
class Dsender extends Thread {
    @Override
    public void run() {
        try {
            //1.创建发送套接字
            DatagramSocket ds =new DatagramSocket(5002);
            //2.创建数据包
            Scanner sc = new Scanner(System.in);
            System.out.println("请输入发送的数据:");
            while(true){
                String s =sc.nextLine();//获取键盘字符串
                byte[] buf = s.getBytes();
                if("quit".equals(s))  {
                    sc.close();
                    ds.close();
                    break;
                }
                DatagramPacket dp =new DatagramPacket(buf,buf.length,InetAddress.getByName("127.0.0.1"),5000);  //将处理的数据流打包
             //3.接受数据
                ds.send(dp);
             //4.打印数据
                String str = new String(dp.getData(),0,dp.getLength());
                String ip = dp.getAddress().getHostAddress();
                int port = dp.getPort();
                System.out.println(str+"from"+ip+"端口号:"+port);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }  
    }
}