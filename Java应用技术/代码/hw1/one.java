import java.util.Scanner;

public class one{
    public static void main(String[] args){
        String a;
        int i = 0;
        Scanner b = new Scanner(System.in);
        while(true){
            a = b.nextLine();
            if(a.equals("double")){
                double[] s = new double[3];
                while(i<3){
                    s[i] = b.nextDouble();
                    i++;
                }
                System.out.printf("choice=%s\n",a);
                System.out.printf("%-5.2f,%5.2f,%.2f\n", s[0], s[1], s[2]);
                b.nextLine();
            }
            else if(a.equals("int")){
                int sum = 0;
                i = 0;
                while(i<3){
                    sum += b.nextInt();
                    i++;
                }
                System.out.printf("choice=%s\n", a);
                System.out.printf("%d\n", sum);
                b.nextLine();
            }
            else if(a.equals("str")){
                String str;
                str = b.next();
                str = b.next() + str;
                str = b.next() + str;
                System.out.printf("choice=%s\n",a);
                System.out.printf("%s\n", str);
                b.nextLine();
            }
            else if(a.equals("line")){
                String line;
                line = b.nextLine();
                line = line.toUpperCase();
                System.out.printf("choice=%s\n",a);
                System.out.printf("%s\n", line);
            }
            else{
                System.out.printf("choice=%s\n",a);
                System.out.println("other");
            }
        }
    }
}