package domain;

public class Student {  // 学生类
    private int sid;
    private String sname;
    private String ssex;
    private int score;

    //构造无参构造函数
    public Student() {
    }
    //构造上面变量的传入函数
    public Student(int sid, String sname, String ssex, int score) {
        this.sid = sid;
        this.sname = sname;
        this.ssex = ssex;
        this.score = score;
    }

    //分开设置和获取这些变量
    public int getSid() {
        return sid;
    }

    public void setSid(int sid) {
        this.sid = sid;
    }

    public String getSname() {
        return sname;
    }

    public void setSname(String sname) {
        this.sname = sname;
    }

    public String getSsex() {
        return ssex;
    }

        public void setSsex(String ssex) {
        this.ssex = ssex;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }
}
