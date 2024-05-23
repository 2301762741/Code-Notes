package internet_learn;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class _2Sender {
    public static void main(String[] args) throws Exception{
        //创建一个发送的网络套接字
        DatagramSocket ds = new DatagramSocket(5000);
        //准备数据集
        String str="hello worl00d";
        byte[] buf = str.getBytes(); //转成数组流
        //发送给对象数据
/*核心*/DatagramPacket dp = new DatagramPacket(buf,buf.length,InetAddress.getByName("127.0.0.1"),6666);
        System.out.println("sending----");
        ds.send(dp);    //发送数据
        ds.close();   //释放资源
    }
}

