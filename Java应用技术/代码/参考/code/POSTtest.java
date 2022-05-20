//: POSTtest.java
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

// An applet that sends its data via a CGI POST
import java.awt.*;
import java.applet.*;
import java.net.*;
import java.io.*;

public class POSTtest extends Applet {
  final static int SIZE = 10;
  Button submit = new Button("Submit");
  TextField[] t = new TextField[SIZE];
  String query = "";
  Label l = new Label();
  TextArea ta = new TextArea(15, 60);
  public void init() {
    Panel p = new Panel();
    p.setLayout(new GridLayout(t.length + 2, 2));
    for(int i = 0; i < t.length; i++) {
      p.add(new Label(
        "Field " + i + "  ", Label.RIGHT));
      p.add(t[i] = new TextField(30));
    }
    p.add(l);
    p.add(submit);
    add("North", p);
    add("South", ta);
  }
  public boolean action (Event evt, Object arg) {
    if(evt.target.equals(submit)) {
      query = "";
      ta.setText("");
      // Encode the query from the field data:
      for(int i = 0; i < t.length; i++)
         query += "Field" + i + "=" +
           URLEncoder.encode(
             t[i].getText().trim()) +
           "&";
      query += "submit=Submit";
      // Send the name using CGI's POST process:
      try {
        URL u = new URL(
          getDocumentBase(), "cgi-bin/POSTtest");
        URLConnection urlc = u.openConnection();
        urlc.setDoOutput(true);
        urlc.setDoInput(true);
        urlc.setAllowUserInteraction(false);
        DataOutputStream server = 
          new DataOutputStream(
            urlc.getOutputStream());
        // Send the data
        server.writeBytes(query);
        server.close();
        // Read and display the response. You
        // cannot use 
        // getAppletContext().showDocument(u);
        // to display the results as a Web page!
        DataInputStream in = 
          new DataInputStream(
            urlc.getInputStream());
        String s;
        while((s = in.readLine()) != null) {
          ta.appendText(s + "\n");
        }
        in.close();
      }
      catch (Exception e) {
        l.setText(e.toString());
      }
    }
    else return super.action(evt, arg);
    return true;
  }
} ///:~