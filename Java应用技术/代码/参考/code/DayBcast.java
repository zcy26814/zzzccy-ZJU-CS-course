import java.net*;
import java.util.*;

public class DayBcast {
    DatagramSocket ds;
    DatagramPacket dp;
    InetAddress addr;
    
    public static final int DATTIME_PORT = 1313;
    
    public static void main(String[] args) throws Exception {
        DayBcast db = new DayBcast(args[0]);
        db.go();
    }
    
    public DatBcast(String target) throws Exception {
        addr = InetAddress.getByName(target);
        ds = new DatagramSocket();
    }
    
    public void go() throws Exception {
        byte[] buff;
        for (;;) {
            Thread.sleep(1000);
            System.out.println("Sending");
            String s = (new Date()).toString();
            buff = s.getBytes();
            dp = new DatagramPacket(buff,buff.length,addr,DATTIME_PORT);
            ds.send(dp);
        }
    }
}