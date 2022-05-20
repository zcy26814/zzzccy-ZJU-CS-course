//: NameSender2.java
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
// via a CGI GET, using Java 1.02.
import java.awt.*;
import java.applet.*;
import java.net.*;
import java.io.*;

public class NameSender2 extends Applet {
  final String CGIProgram = "Listmgr2.exe";
  Button send = new Button(
    "Add email address to mailing list");
  TextField name = new TextField(
    "type your name here", 40),
    email = new TextField(
    "type your email address here", 40);
  String str = new String();
  Label l = new Label(), l2 = new Label();
  int vcount = 0;
  public void init() {
    setLayout(new BorderLayout());
    Panel p = new Panel();
    p.setLayout(new GridLayout(3, 1));
    p.add(name);
    p.add(email);
    p.add(send);
    add("North", p);
    Panel labels = new Panel();
    labels.setLayout(new GridLayout(2, 1));
    labels.add(l);
    labels.add(l2);
    add("Center", labels);
    l.setText("Ready to send email address");
  }
  public boolean action (Event evt, Object arg) {
    if(evt.target.equals(send)) {
      l2.setText("");
      // Check for errors in data:
      if(name.getText().trim()
         .indexOf(' ') == -1) {
        l.setText(
          "Please give first and last name");
        l2.setText("");
        return true;
      }
      str = email.getText().trim();
      if(str.indexOf(' ') != -1) {
        l.setText(
          "Spaces not allowed in email name");
        l2.setText("");
        return true;
      }
      if(str.indexOf(',') != -1) {
        l.setText(
          "Commas not allowed in email name");
        return true;
      }
      if(str.indexOf('@') == -1) {
        l.setText("Email name must include '@'");
        l2.setText("");
        return true;
      }
      if(str.indexOf('@') == 0) {
        l.setText(
          "Name must preceed '@' in email name");
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
      // Build and encode the email data:
      String emailData = 
        "name=" + URLEncoder.encode(
          name.getText().trim()) +
        "&email=" + URLEncoder.encode(
          email.getText().trim().toLowerCase()) +
        "&submit=Submit";
      // Send the name using CGI's GET process:
      try {
        l.setText("Sending...");
        URL u = new URL(
          getDocumentBase(), "cgi-bin/" +
          CGIProgram + "?" + emailData);
        l.setText("Sent: " + email.getText());
        send.setLabel("Re-send");
        l2.setText(
          "Waiting for reply " + ++vcount);
        DataInputStream server =
          new DataInputStream(u.openStream());
        String line;
        while((line = server.readLine()) != null)
          l2.setText(line);
      } catch(MalformedURLException e) {
        l.setText("Bad URl");
      } catch(IOException e) {
        l.setText("IO Exception");
      } 
    }
    else return super.action(evt, arg);
    return true;
  }
} ///:~