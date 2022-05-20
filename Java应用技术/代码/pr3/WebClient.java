package Web;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

class ClientThread {
	public static final int MAX_THREADS = 40;
	private Socket socket;
	private BufferedReader in;
	private PrintWriter out;
	private int id = -1; //用户id初始化为-1
	
	public ClientThread(InetAddress addr) {
		
		class ClientSendThread extends Thread { //用户发送线程（内部类
			public ClientSendThread() {
				start();
			}
			public void run() {
				while(id == -1) { 
					try {
						sleep(10); //等待receive线程更新id
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
				try {
					BufferedReader sin = 
						new BufferedReader(
							new InputStreamReader(
								System.in));
					String str;
					while(true) { //等待用户输入，把用户输入发送给服务器
						str = sin.readLine();
						out.println("Client " + id + ": " + str);
						if(str.equals("END")) break; //输入END则结束
					}
				} catch(IOException e) {
		    	
				}
			}
		}
		
		class ClientReceiveThread extends Thread { //用户接收线程
			public ClientReceiveThread() {
				start();
			}
			public void run() {
				try {
					id = Integer.parseInt(in.readLine()); //从服务器获取id
					System.out.println("Making client " + id);
					String str;
					while(true) { //接受服务器输入
						str = in.readLine();
						if(str.equals("END")) { //遇到END说明对话结束
							System.out.println("closing...");
							break;
						} else {
							System.out.println(str); //否则输出服务器发送内容
						}
					}
				} catch(IOException e) {
		    	
				} finally {
					try {
						socket.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		}
		
		try {
			socket = new Socket(addr, WebServer.PORT);
		} catch (IOException e) {
			
		}
		try {
			in = new BufferedReader(
					new InputStreamReader(
						socket.getInputStream()));
				// Enable auto-flush:
			out = new PrintWriter(
					new BufferedWriter(
						new OutputStreamWriter(
							socket.getOutputStream())), true);
			new ClientSendThread();
			new ClientReceiveThread();
			
		} catch(IOException e) {
		      // The socket should be closed on any 
		      // failures other than the socket 
		      // constructor:
			try {
				socket.close();
			} catch(IOException e2) {}
		}
		    // Otherwise the socket will be closed by
		    // the run() method of the thread.
	}
	
}



public class WebClient {
	
	public static void main(String[] args) throws IOException, InterruptedException {
		InetAddress addr = InetAddress.getByName(null);
		new ClientThread(addr);
	}
	
} ///:~