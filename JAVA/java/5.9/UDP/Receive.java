package UDP;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class Receive {
    public static void main(String[] args) throws Exception{
        //创建接受套接字
        DatagramSocket ds = new DatagramSocket(5000);
        //创建存储数组
        byte[] buf = new byte[1024];
        //接受数据
        DatagramPacket dp =new DatagramPacket(buf,buf.length);
        //获取接受数据
         System.out.println("等待接受数据---");
         ds.receive(dp);
        //打印接受信息
        byte[] data = dp.getData();   //将数据储存到buf中
        int length = dp.getLength();  //获取buf长度
        String ip = dp.getAddress().getHostAddress();  //发送方ip地址
        int port = dp.getPort();   //发送方端口号
        System.out.println(new String(data,0,length)+"from"+ip+"端口号:"+port);
        //释放资源
        ds.close(); 
    }
}
