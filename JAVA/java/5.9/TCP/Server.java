package TCP;

import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;



public class Server {
public static void main(String[] args) throws Exception {
        new TcpServer().listen();
    }
}

/**
 * TcpServer
 */
class TcpServer {
    final int PORT=8888;   //定义服务器端口
    public  void listen() throws Exception{
        //定义服务器端监听套接字
        ServerSocket serverSocket = new ServerSocket(PORT);  //接受服务器不需要IP
        //定义接受套接字
        Socket client = serverSocket.accept();
        //创建一个发送的客户端的输出流
        OutputStream os = client.getOutputStream();
        System.out.println("开始与客户端交互");
        //连接服务器并向发送数据
          os.write("hello".getBytes());
        //模拟其他线程占用时间
        Thread.sleep(2000);
        System.out.println("结束与客户端交互");
        //释放资源
        client.close();
        serverSocket.close();
    }  
}
