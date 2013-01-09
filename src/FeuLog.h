/*
 * FeuLog.h
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#ifndef FEULOG_H_
#define FEULOG_H_

#include <iostream>
#include <sstream>
using namespace std;

template <typename T> string stringof(T t) { ostringstream os; os << t; return os.str(); }

static float floatof(string s) {
    float fout;
    stringstream os;
    os << s;
    os >> fout; 
    return fout; 
}

static int intof(string s) {
    int iout;
    stringstream os;

    // Choose base from formatting.  I hate this.
    if (s[0] != '0') {
        os << s;
    } else {
        switch (s[1]) {
            case 'x':
            case 'X':
        }
    }
}

class FeuLog {
public:
	FeuLog();
	virtual ~FeuLog();

public:
    static void d(string); // Debug message; may or may not show
    static void d(string,string); 
    static void d(string,string,string); 
    static void i(string); // Informational string (stdout)
    static void i(string,string);
    static void i(string,string,string);
    static void w(string); // Warning notice (stderr)
    static void w(string,string); 
    static void w(string,string,string);
    static void e(string); // Error condition (stderr)
    static void e(string,string);
    static void e(string,string,string);

};

#endif /* FEULOG_H_ */
