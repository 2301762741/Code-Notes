package Process_learn;

/*********************票务售卖程序 ********************/

public class _2Ticket {
    public static void main(String[] args) {
        //创建票对象进程
        Ticket ticket = new Ticket();
        //开三个窗口进行售卖
        Thread win1=new Thread(ticket,"win1");
        Thread win2=new Thread(ticket,"win2");
        Thread win3=new Thread(ticket,"win3");
        //线程启动
        win1.start();
        win2.start();
        win3.start();
    }
}

class Ticket implements Runnable{
    private int tickets=10;    //总票数
    Object object= new Object();  //创建任意对象，用于同步代码块锁

    public void run(){
        while(true) {
            synchronized (object){
                try {
                    Thread.sleep(10);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                
                if(tickets>0)
                    System.out.println(Thread.currentThread().getName()+"sale"+tickets--);
                else
                    break;
            }
        }
    }
}