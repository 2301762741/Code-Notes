package Process_learn;

/******************yield线程让步****************/

public class _1yield {
    public static void main(String[] args) {
        // process = new PROCESS();
        Thread pro1 = new PROCESS();
        pro1.start();
    }
}

class PROCESS extends Thread {
    //public PROCESS(string name){
    //    super(name);
    //}

    public void run(){
        for (int i = 0; i < 6; i++) {
            System.out.println("拍球次数"+i);
            
            if(i==3){
                System.out.println("线程止步");
        /*核心*/Thread.yield();   //sleep阻塞线程，yield线程进入绪态队列
            }
        }
    }
}    