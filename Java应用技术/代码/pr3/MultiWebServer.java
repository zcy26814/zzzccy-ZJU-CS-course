//: MultiJabberServer.java
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

// A server that uses multithreading to handle 
// any number of clients.
package Web;
import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;

class ServeOneClient extends Thread {
	private MainWebServer mainWebServer;
	private Socket socket;
	private BufferedReader in;
	private PrintWriter out;
	public ServeOneClient(Socket s, MainWebServer mws) throws IOException {
		socket = s;
		mainWebServer = mws;
		in = new BufferedReader(
				new InputStreamReader(
					socket.getInputStream()));
    // Enable auto-flush:
		out = new PrintWriter(
				new BufferedWriter(
					new OutputStreamWriter(
						socket.getOutputStream())), true);
		mainWebServer.listWriter.add(out);
    // If any of the above calls throw an 
    // exception, the caller is responsible for
    // closing the socket. Otherwise the thread
    // will close it.
		start(); // Calls run()
	}
  	public void run() {
  		try {
  			while (true) {  
  				String str = in.readLine();
  				if (str.endsWith("END")) {
  					out.println("END");
  					System.out.println(str);
  					break;
  				}
  				System.out.println("Echoing: " + str);
  				for(PrintWriter w : mainWebServer.listWriter) {
  					w.println(str);
  				}
  			}
  			System.out.println("closing...");
  		} catch (IOException e) {
		  
  		} finally {
  			try {
  				socket.close();
  				mainWebServer.listWriter.remove(out);
  			} catch(IOException e) {
  				
  			}
  		}
  	}
}

class MainWebServer {
	
	public List<PrintWriter> listWriter;
	
	public MainWebServer() {
		super();
		listWriter = new ArrayList<PrintWriter>();
	}
	
}

public class MultiWebServer {  

	static final int PORT = 8080;
	public static void main(String[] args)
		throws IOException {
		ServerSocket s = new ServerSocket(PORT);
		MainWebServer mainWebServer = new MainWebServer();
		System.out.println("Server Started");
	    try {
	    	while(true) {
	        // Blocks until a connection occurs:
	    		Socket socket = s.accept();
	    		try {
	    			new ServeOneClient(socket, mainWebServer);
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