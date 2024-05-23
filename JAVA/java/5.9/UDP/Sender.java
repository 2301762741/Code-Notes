package UDP;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class Sender {
    public static void main(String[] args) throws Exception{
        //创建发送套接字
        DatagramSocket ds = new DatagramSocket(3000);
        //处理发送字符流
        String str = "hello world";
        byte[] buf =str.getBytes();
        DatagramPacket dp= new DatagramPacket(buf,buf.length,InetAddress.getByName("127.0.0.1"),5000);
        //发送数据
        System.out.println("开始发送数据---");
        ds.send(dp); //发送数据
        ds.close();
    }
}
