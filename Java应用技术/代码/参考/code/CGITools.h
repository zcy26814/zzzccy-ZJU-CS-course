//: CGITools.h
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

// Automatically extracts and decodes data
// from CGI GETs and POSTs. Tested with GNU C++ 
// (available for most server machines).
#include <string.h>
#include <vector> // STL vector
using namespace std;

// A class to hold a single name-value pair from
// a CGI query. CGI_vector holds Pair objects and
// returns them from its operator[].
class Pair {
  char* nm;
  char* val;
public:
  Pair() { nm = val = 0; }
  Pair(char* name, char* value) {
    // Creates new memory:
    nm = decodeURLString(name);
    val = decodeURLString(value);
  }
  const char* name() const { return nm; }
  const char* value() const { return val; }
  // Test for "emptiness"
  bool empty() const {
    return (nm == 0) || (val == 0);
  }
  // Automatic type conversion for boolean test:
  operator bool() const {
    return (nm != 0) && (val != 0);
  }
  // The following constructors & destructor are
  // necessary for bookkeeping in C++.
  // Copy-constructor:
  Pair(const Pair& p) {
    if(p.nm == 0 || p.val == 0) {
      nm = val = 0;
    } else {
      // Create storage & copy rhs values:
      nm = new char[strlen(p.nm) + 1];
      strcpy(nm, p.nm);
      val = new char[strlen(p.val) + 1];
      strcpy(val, p.val);
    }
  }
  // Assignment operator:
  Pair& operator=(const Pair& p) {
    // Clean up old lvalues:
    delete nm;
    delete val;
    if(p.nm == 0 || p.val == 0) {
      nm = val = 0;
    } else {
      // Create storage & copy rhs values:
      nm = new char[strlen(p.nm) + 1];
      strcpy(nm, p.nm);
      val = new char[strlen(p.val) + 1];
      strcpy(val, p.val);
    }
    return *this;
  } 
  ~Pair() { // Destructor
    delete nm; // 0 value OK
    delete val;
  }
  // If you use this method outide this class, 
  // you're responsible for calling 'delete' on
  // the pointer that's returned:
  static char* 
  decodeURLString(const char* URLstr) {
    int len = strlen(URLstr);
    char* result = new char[len + 1];
    memset(result, len + 1, 0);
    for(int i = 0, j = 0; i <= len; i++, j++) {
      if(URLstr[i] == '+')
        result[j] = ' ';
      else if(URLstr[i] == '%') {
        result[j] =
          translateHex(URLstr[i + 1]) * 16 +
          translateHex(URLstr[i + 2]);
        i += 2; // Move past hex code
      } else // An ordinary character
        result[j] = URLstr[i];
    }
    return result;
  }
  // Translate a single hex character; used by
  // decodeURLString():
  static char translateHex(char hex) {
    if(hex >= 'A')
      return (hex & 0xdf) - 'A' + 10;
    else
      return hex - '0';
  }
};

// Parses any CGI query and turns it
// into an STL vector of Pair objects:
class CGI_vector : public vector<Pair> {
  char* qry;
  const char* start; // Save starting position
  // Prevent assignment and copy-construction:
  void operator=(CGI_vector&);
  CGI_vector(CGI_vector&);
public:
  // const fields must be initialized in the C++
  // "Constructor initializer list":
  CGI_vector(char* query) :
      start(new char[strlen(query) + 1]) {
    qry = (char*)start; // Cast to non-const
    strcpy(qry, query);
    Pair p;
    while((p = nextPair()) != 0)
      push_back(p);
  }
  // Destructor:
  ~CGI_vector() { delete start; }
private:
  // Produces name-value pairs from the query 
  // string. Returns an empty Pair when there's 
  // no more query string left:
  Pair nextPair() {
    char* name = qry;
    if(name == 0 || *name == '\0')
      return Pair(); // End, return null Pair
    char* value = strchr(name, '=');
    if(value == 0)
      return Pair(); // Error, return null Pair
    // Null-terminate name, move value to start
    // of its set of characters:
    *value = '\0';
    value++;
    // Look for end of value, marked by '&':
    qry = strchr(value, '&');
    if(qry == 0) qry = ""; // Last pair found
    else {
      *qry = '\0'; // Terminate value string
      qry++; // Move to next pair
    }
    return Pair(name, value);
  }
}; ///:~