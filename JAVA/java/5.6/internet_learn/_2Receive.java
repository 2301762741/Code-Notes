package internet_learn;
import java.net.DatagramPacket;
import java.net.DatagramSocket;


public class _2Receive {
    public static void main(String[] args) throws Exception{
        //创建buf数组用于数据缓冲区
        byte[] buf = new byte[1024];
        //创建一个socket监听套接字
        DatagramSocket ds = new DatagramSocket(6666);
        //发送buf这个数据
        DatagramPacket dp = new DatagramPacket(buf,buf.length);
        System.out.println("receiving----");
        ds.receive((dp));  //等待接受数据,如果没有数据则阻塞
        //打印接收的信息
        System.out.println(dp.getData()+"from"+dp.getAddress().getHostAddress()+dp.getPort());
        ds.close();
    }
}

