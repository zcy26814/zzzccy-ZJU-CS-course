import java.net*;

public class DayWatch {
    private DatagramSocket ds;
    private DatagramPacket dp;
    
    public static void main(String[] ars) throws Exception {
        DatWatch d = new DatWatch();
        d.go();
    }
    
    public void go() throws Exception {
        byte[] buff = new byte[64];
        String s;
        ds = new DatagramSocket(DayBcast.DAYTIME_POR);
        dp = new DatagramPacket(buff,buff.length);
        for (;;) {
            ds.receive(dp);
            s = new String(dp.getData());
            System.out.println("Time signal received from "+dp.getAddress()+" Time is: "+s);
        }
    }
}