import java.util.Scanner;

class two {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n, k;
		n = scan.nextInt();
		k = scan.nextInt();
		int[] len = new int[10000];
		int[] cnt = new int[10000];
		int sum = 0, max = 0;
		for(int i=0; i<n; i++) {
			len[i] = scan.nextInt();
			sum += len[i];
		}
		int s = sum / k;
		while(f(s, len, n, cnt) < k) {
			s = u(len, cnt, n);
		}
		System.out.print(s);
	}
	private static int f(int s, int[] len, int n, int[] cnt) {
		int total = 0;
		for(int i=0; i<n; i++) {
			cnt[i] = len[i] / s;
			total += cnt[i];
		}
		return total;
	}
	private static int u(int[] len, int[] cnt, int n) {
		int max = 0;
		for(int i=0; i<n; i++) {
			max = Math.max(max, len[i]/(cnt[i]+1));
		}
		return max;
	}

}