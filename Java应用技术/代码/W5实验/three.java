import java.util.Scanner;

class three {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		int[] cnt = new int[1000];
		for(int i=0; i<n; i++) {
			cnt[scan.nextInt()]++;
		}
		int pre = 0, temp;
		for(int i=0; i < 1000-2; i++) {
			temp = Math.min(Math.min(cnt[i], cnt[i+1]), cnt[i+2]);
			cnt[i] -= temp; cnt[i+1] -= temp; cnt[i+2] -= temp;
			pre += temp;
		}
		System.out.print(pre);
	}

}