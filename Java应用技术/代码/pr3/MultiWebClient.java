//: MultiJabberClient.java
//////////////////////////////////////////////////
// Copyright (c) Bruce Eckel, 1998
// Source code file from the book "Thinking in Java"
// All rights reserved EXCEPT as allowed by the
// following statements: You can freely use this file
// for your own work (personal or commercial),
// including modifications and distribution in
// executable form only. Permission is granted to use
// this file in classroom situations, including its
// use in presentation materials, as long as the book
// "Thinking in Java" is cited as the source. 
// Except in classroom situations, you cannot copy
// and distribute this code; instead, the sole
// distribution point is http://www.BruceEckel.com 
// (and official mirror sites) where it is
// freely available. You cannot remove this
// copyright and notice. You cannot distribute
// modified versions of the source code in this
// package. You cannot use this file in printed
// media without the express permission of the
// author. Bruce Eckel makes no representation about
// the suitability of this software for any purpose.
// It is provided "as is" without express or implied
// warranty of any kind, including any implied
// warranty of merchantability, fitness for a
// particular purpose or non-infringement. The entire
// risk as to the quality and performance of the
// software is with you. Bruce Eckel and the
// publisher shall not be liable for any damages
// suffered by you or any third party as a result of
// using or distributing software. In no event will
// Bruce Eckel or the publisher be liable for any
// lost revenue, profit, or data, or for direct,
// indirect, special, consequential, incidental, or
// punitive damages, however caused and regardless of
// the theory of liability, arising out of the use of
// or inability to use software, even if Bruce Eckel
// and the publisher have been advised of the
// possibility of such damages. Should the software
// prove defective, you assume the cost of all
// necessary servicing, repair, or correction. If you
// think you've found an error, please email all
// modified files with clearly commented changes to:
// Bruce@EckelObjects.com. (Please use the same
// address for non-code errors found in the book.)
/////////////////////////////////////////////////

// Client that tests the MultiJabberServer
// by starting up multiple clients.
package Web;
import java.net.*;
import java.io.*;

class WebClientThread {
	private Socket socket;
	private BufferedReader in;
	private PrintWriter out;
	private static int counter = 0;
	private int id = counter++;
	private static int threadcount = 0;
	
	public static int threadCount() { 
		return threadcount; 
	}
	
	public WebClientThread(InetAddress addr) {
		class WebClientSendThread extends Thread {
			public WebClientSendThread() {
				start();
			}
			public void run() {
				try {
					BufferedReader sin = 
							new BufferedReader(
									new InputStreamReader(
										System.in));
					String str;
					while(true) {
						str = sin.readLine();
						out.println("Client " + id + ": " + str);
						if(str == "END") break;
					}
				} catch(IOException e) {
		    	
				}
			}
		}
		class WebClientReceiveThread extends Thread {
			public WebClientReceiveThread() {
				start();
			}
			public void run() {
				try {
					String str;
					while(true) {
						str = in.readLine();
						if(str.equals("END")) break;
						System.out.println(str);
					}
				} catch(IOException e) {
		    	
				} finally {
					try {
						socket.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
					threadcount--;
				}
			}
		}
		
		System.out.println("Making client " + id);
		threadcount++;
		try {
			socket = new Socket(addr, MultiWebServer.PORT);
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
			new WebClientSendThread();
			new WebClientReceiveThread();
			
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



public class MultiWebClient {
	static final int MAX_THREADS = 40;
	public static void main(String[] args) 
		throws IOException, InterruptedException {
		InetAddress addr = InetAddress.getByName(null);
		while(true) {
			if(WebClientThread.threadCount() < MAX_THREADS)
				new WebClientThread(addr);
			Thread.sleep(100);
		}
	}
} ///:~