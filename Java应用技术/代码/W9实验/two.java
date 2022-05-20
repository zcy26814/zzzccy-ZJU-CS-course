import java.util.Scanner;

/*这里放置你的答案，即PrintTask类的代码*/
class PrintTask implements Runnable{
	private int n;
	public PrintTask(int n){
		this.n = n;
	}
	public void run(){
		for(int i=0; i<n; i++){
			System.out.println(i);
		}
		System.out.println(Thread.currentThread().getName());
	}
}

public class two {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        PrintTask task = new PrintTask(Integer.parseInt(sc.next()));
        Thread t1 = new Thread(task);
        t1.start();
        sc.close();
    }
}