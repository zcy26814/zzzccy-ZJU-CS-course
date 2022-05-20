import java.util.Scanner;

class one{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Resource resource = null;
        try{
            resource = new Resource();
            resource.open(sc.nextLine());
             /*这里放置你的答案*/
            System.out.println("resource open success");
        } catch(Exception e){
            System.out.println(e);
        }
        try {
            resource.close(sc.nextLine());
            System.out.println("resource release success");
        } catch (RuntimeException e) {
            System.out.println(e);
        }
           sc.close();
    
    }
}
