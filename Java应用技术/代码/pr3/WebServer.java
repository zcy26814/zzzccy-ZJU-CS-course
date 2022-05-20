package Web;
import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;

class OneClientServer extends Thread {
	private static int threadcount = 0;
	private MainServer mainServer;
	private Socket socket;
	private BufferedReader in;
	private PrintWriter out;
	private static int counter = 0;
	private int id = counter++;
	
	public static int threadcount() { //记录服务器当前连接的客户端数量
		return threadcount;
	}
	
	public OneClientServer(Socket s, MainServer ms) throws IOException { 
		socket = s;
		mainServer = ms;
		in = new BufferedReader(
				new InputStreamReader(
					socket.getInputStream()));
    // Enable auto-flush:
		out = new PrintWriter(
				new BufferedWriter(
					new OutputStreamWriter(
						socket.getOutputStream())), true);
		mainServer.listWriter.add(out);
    // If any of the above calls throw an 
    // exception, the caller is responsible for
    // closing the socket. Otherwise the thread
    // will close it.
		threadcount++;
		start(); // Calls run()
	}
  	public void run() {
  		try { 
  			out.println("" + id); //向客户端发送id号
  			while (true) {  
  				String str = in.readLine(); //接收信息
  				if (str.endsWith("END")) {
  					out.println("END");
  					System.out.println(str);
  					break;
  				}
  				System.out.println("Echoing: " + str); 
  				for(PrintWriter w : mainServer.listWriter) { //给当前已连接的所有客户端发送信息
  					w.println(str);
  				}
  			}
  			System.out.println("closing...");
  		} catch (IOException e) {
		  
  		} finally {
  			try {
  				socket.close();
  				threadcount--;
  				mainServer.listWriter.remove(out);
  			} catch(IOException e) {
  				
  			}
  		}
  	}
}

class MainServer { //保存服务器到所有客户的输出端口
	
	public List<PrintWriter> listWriter;
	
	public MainServer() {
		super();
		listWriter = new ArrayList<PrintWriter>();
	}
	
}

public class WebServer {  
	public static final int MAX_THREADS = 40; //服务器支持的最大线程数
	static final int PORT = 8080;
	public static void main(String[] args)
		throws IOException {
		ServerSocket s = new ServerSocket(PORT); 
		MainServer mainServer = new MainServer();
		System.out.println("Server Started");
	    try {
	    	while(true) {
	        // Blocks until a connection occurs:
	    		Socket socket = s.accept();
	    		try {
	    			if(OneClientServer.threadcount() < MAX_THREADS)
	    				new OneClientServer(socket, mainServer);
	    		} catch(IOException e) {
	          // If it fails, close the socket,
	          // otherwise the thread will close it:
	    			socket.close();
	    		}
	    	}
	    } finally {
	      s.close();
	    }
	} 
} ///:~