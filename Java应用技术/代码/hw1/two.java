import java.util.Scanner;

public class two{
    public static void main(String[] args){
        String s;
        Scanner a = new Scanner(System.in);
        s = a.nextLine();
        String s1 = a.next();
        String s2 = a.next();
        String ss[] = s.split(" ");
        int i;
        for(i = 0; i<ss.length; i++){
            if(ss[i].equals(s1)){
                ss[i] = s2;
            }
        }
        System.out.printf("%s", ss[0]);
        for(i=1; i<ss.length; i++){
            System.out.printf(" %s", ss[i]);
        }
    }
}