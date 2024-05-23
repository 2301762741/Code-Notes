package internet_learn;
import java.net.InetAddress;

/************InetAddress对象的使用*************/

public class _1 {
    public static void main(String[] args) throws Exception{
        //获取一个本地主机IP对象
        InetAddress loaclHost = InetAddress.getLocalHost();
        //获得一个远程主机IP对象
        InetAddress baidu=InetAddress.getByName("www.baidu.com");
        //通过本地主机IP对象获取本地ip地址
        System.out.println("ben di"+loaclHost.getHostAddress());
        //远程对象获取IP对象获取远程端ip
        System.out.println("baidu:"+baidu.getHostAddress());
        //判断可以多长时间到达百度
        System.out.println("3 second:"+baidu.isReachable(3000));
        //获取百度网站的主机名
        System.out.println("name"+baidu.getHostName());
    }
}

