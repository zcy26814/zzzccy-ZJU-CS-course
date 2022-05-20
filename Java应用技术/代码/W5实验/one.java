import java.util.Scanner;

class one {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int L = scan.nextInt();
        int M = scan.nextInt();
        int n, i, j, r, s, k;
        n = 2 * M;
        int[] a = new int[10001];
        int[] b = new int[10001];
        for(i = 0; i < n; i+=2){
            b[i] = scan.nextInt();
            b[i+1] = scan.nextInt();
        }
        for(i = 0; i <= L; i++){
            a[i] = i;
        }
        for(i = 0; i < n; i+=2){
            r = b[i];
            s = b[i+1];
            for(j = r; j <= s; j++){
                a[j] = -1;
            }
        }
        k = 0;
        for(i = 0; i <= L; i++){
            if(a[i] != -1){
                k++;
            }
        }
    System.out.printf("%d", k);
	}
}

/*
某校大门外长度为L的马路上有一排树，每两棵相邻的树之间的间隔都是1米。我们可以把马路看成一个数轴，马路的一端在数轴0的位置，另一端在L的位置。数轴上的每个整数点，即0、1、2、......、L，都种有一棵树。

由于马路上有一些区域要用来建车站。这些区域用它们在数轴上的起始点和终止点表示。已知任一区域的起始点和终止点的坐标都是整数，区域之间可能有重合的部分。现在要把这些区域中的树(包括区域端点处的两棵树)移走。你的任务是计算将这些树都移走后，马路上还有多少棵树。
输入格式:

输入的第一行是整数L（1< L < 10000），L代表马路的长度，单位是米。 第二行是整数M（0 < M < 100），M代表车站的数目。 接下来的M行，每行包含两个不同的整数，用一个空格隔开，表示一个车站所占区域的起始点和终止点的坐标。
输出格式:

一个整数，表示马路上剩余的树的数目。
输入样例:

500 
3
150 300
100 200
470 471

输出样例:

298
*/