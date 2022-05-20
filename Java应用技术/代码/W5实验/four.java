import java.util.Scanner;
import java.util.concurrent.ConcurrentLinkedQueue;

class four {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int[] a = new int [10001];
        int b = 0;
        for(int i = 0; i < n; i++){
            a[i] = scan.nextInt();
        }
        for(int j = 0; j < n-1; j++){
            for(int k = j+1; k < n; k++){
                if(a[j] !=  a[k]) continue;
                else{
                    b = 1;
                    break;
                }
            }
        }
        if(b == 0) System.out.println("NO");
        else System.out.println("YES");
    }
}