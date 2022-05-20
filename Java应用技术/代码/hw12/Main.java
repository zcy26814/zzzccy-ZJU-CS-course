import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        ArrayList<String[]> lst = new ArrayList<String[]>();
        while ( in.hasNextLine() ) {
            String line = in.nextLine();
            lst.add(line.split(" "));
        }
        Set<String> ret = lst.stream()
            .filter(x->x[0].equal)
            .map(x->x[x.length-1] )
            .collect(Collectors.toset() );
        ArrayList<String> r = new ArrayList<String>(ret);
        Collections.sort(r);
        for ( String s: r ) {
            System.out.println(s);
        }
        in.close();
    }
}