//: Listmgr2.cpp
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

// CGI version of Listmgr.c in C++, which 
// extracts its input via the GET submission 
// from the associated applet. Also works as
// an ordinary CGI program with HTML forms.
#include <stdio.h>
#include "CGITools.h"
const char* dataFile = "list2.txt";
const char* notify = "Bruce@EckelObjects.com";
#undef DEBUG

// Similar code as before, except that it looks
// for the email name inside of '<>':
int inList(FILE* list, const char* emailName) {
  const int BSIZE = 255;
  char lbuf[BSIZE];
  char emname[BSIZE];
  // Put the email name in '<>' so there's no
  // possibility of a match within another name:
  sprintf(emname, "<%s>", emailName);
  // Go to the beginning of the list:
  fseek(list, 0, SEEK_SET);
  // Read each line in the list:
  while(fgets(lbuf, BSIZE, list)) {
    // Strip off the newline: 
    char * newline = strchr(lbuf, '\n');
    if(newline != 0) 
      *newline = '\0';
    if(strstr(lbuf, emname) != 0)
      return 1;
  }
  return 0;
}

void main() {
  // You MUST print this out, otherwise the 
  // server will not send the response:
  printf("Content-type: text/plain\n\n");
  FILE* list = fopen(dataFile, "a+t");
  if(list == 0) {
    printf("error: could not open database. ");
    printf("Notify %s", notify);
    return;
  }
  // For a CGI "GET," the server puts the data
  // in the environment variable QUERY_STRING:
  CGI_vector query(getenv("QUERY_STRING"));
  #if defined(DEBUG)
  // Test: dump all names and values
  for(int i = 0; i < query.size(); i++) {
    printf("query[%d].name() = [%s], ", 
      i, query[i].name());
    printf("query[%d].value() = [%s]\n", 
      i, query[i].value());
  }
  #endif(DEBUG)
  Pair name = query[0];
  Pair email = query[1];
  if(name.empty() || email.empty()) {
    printf("error: null name or email");
    return;
  } 
  if(inList(list, email.value())) {
    printf("Already in list: %s", email.value());
    return;
  }
  // It's not in the list, add it:
  fseek(list, 0, SEEK_END);
  fprintf(list, "%s <%s>;\n", 
    name.value(), email.value());
  fflush(list);
  fclose(list);
  printf("%s <%s> added to list\n", 
    name.value(), email.value());
} ///:~