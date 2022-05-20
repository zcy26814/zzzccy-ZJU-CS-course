import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		int a = scan.nextInt();
		int b = scan.nextInt();
		int c = scan.nextInt();
		
		StringBuilder s = new StringBuilder();
		for(int i = 0; i <= n; i++) {
			s.append(i);
		}
		System.out.print(s.length() + " ");
		
		String t = s.substring(a, b + 1);
		int index = 0, cnt = 0;
		while(true) {
			index = t.indexOf(String.valueOf(c), index) + 1;
			if(index == 0) break;
			cnt++;
		}
		System.out.print(cnt);
	}
}