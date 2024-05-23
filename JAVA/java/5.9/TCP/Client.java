package TCP;

import java.io.InputStream;
import java.net.InetAddress;
import java.net.Socket;

public class Client {
    public static void main(String[] args) throws Exception {
        new TcpClient().connect();
    }
}

/**
 *  TcpClient
 */
class  TcpClient {   
    final int PORT=8888;
    public void connect() throws Exception{
        //创建连接端套接字
        Socket client = new Socket(InetAddress.getLocalHost(),PORT);
        //创建一个接收服务器的输入流
        InputStream in = client.getInputStream();
        //定义接受数据流的buf并打印
        byte[] buf = new byte[1024];
        int len = in.read(buf);
        System.out.println(new String(buf,0,len));
        //释放资源
        client.close();
    }
}