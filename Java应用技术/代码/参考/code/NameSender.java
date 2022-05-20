//: NameSender.java
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

// An applet that sends an email address
// as a datagram, using Java 1.02.
import java.awt.*;
import java.applet.*;
import java.net.*;
import java.io.*;

public class NameSender extends Applet 
    implements Runnable {
  private Thread pl = null;
  private Button send = new Button(
    "Add email address to mailing list");
  private TextField t = new TextField(
    "type your email address here", 40);
  private String str = new String();
  private Label 
    l = new Label(), l2 = new Label();
  private DatagramSocket s; 
  private InetAddress hostAddress;
  private byte[] buf = 
    new byte[NameCollector.BUFFER_SIZE];
  private DatagramPacket dp =
    new DatagramPacket(buf, buf.length);
  private int vcount = 0;
  public void init() {
    setLayout(new BorderLayout());
    Panel p = new Panel();
    p.setLayout(new GridLayout(2, 1));
    p.add(t);
    p.add(send);
    add("North", p);
    Panel labels = new Panel();
    labels.setLayout(new GridLayout(2, 1));
    labels.add(l);
    labels.add(l2);
    add("Center", labels);
    try {
      // Auto-assign port number:
      s = new DatagramSocket();
      hostAddress = InetAddress.getByName(
        getCodeBase().getHost());
    } catch(UnknownHostException e) {
      l.setText("Cannot find host");
    } catch(SocketException e) {
      l.setText("Can't open socket");
    } 
    l.setText("Ready to send your email address");
  }
  public boolean action (Event evt, Object arg) {
    if(evt.target.equals(send)) {
      if(pl != null) {
        // pl.stop(); Deprecated in Java 1.2
        Thread remove = pl;
        pl = null;
        remove.interrupt();
      }
      l2.setText("");
      // Check for errors in email name:
      str = t.getText().toLowerCase().trim();
      if(str.indexOf(' ') != -1) {
        l.setText("Spaces not allowed in name");
        return true;
      }
      if(str.indexOf(',') != -1) {
        l.setText("Commas not allowed in name");
        return true;
      }
      if(str.indexOf('@') == -1) {
        l.setText("Name must include '@'");
        l2.setText("");
        return true;
      }
      if(str.indexOf('@') == 0) {
        l.setText("Name must preceed '@'");
        l2.setText("");
        return true;
      }
      String end = 
        str.substring(str.indexOf('@'));
      if(end.indexOf('.') == -1) {
        l.setText("Portion after '@' must " +
          "have an extension, such as '.com'");
        l2.setText("");
        return true;
      }
      // Everything's OK, so send the name. Get a
      // fresh buffer, so it's zeroed. For some 
      // reason you must use a fixed size rather
      // than calculating the size dynamically:
      byte[] sbuf = 
        new byte[NameCollector.BUFFER_SIZE];
      str.getBytes(0, str.length(), sbuf, 0);
      DatagramPacket toSend =
        new DatagramPacket(
          sbuf, 100, hostAddress,
          NameCollector.COLLECTOR_PORT);
      try {
        s.send(toSend);
      } catch(Exception e) {
        l.setText("Couldn't send datagram");
        return true;
      }
      l.setText("Sent: " + str);
      send.setLabel("Re-send");
      pl = new Thread(this);
      pl.start();
      l2.setText(
        "Waiting for verification " + ++vcount);
    }
    else return super.action(evt, arg);
    return true;
  }
  // The thread portion of the applet watches for
  // the reply to come back from the server:
  public void run() {
    try {
      s.receive(dp);
    } catch(Exception e) {
      l2.setText("Couldn't receive datagram");
      return;
    }
    l2.setText(new String(dp.getData(),
      0, 0, dp.getLength()));
  }
} ///:~