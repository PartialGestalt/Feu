/*
 * FeuLog.h
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#ifndef FEULOG_H_
#define FEULOG_H_

#include <iostream>
using namespace std;

class FeuLog {
public:
	FeuLog();
	virtual ~FeuLog();

public:
    static void d(string); // Debug message; may or may not show
    static void i(string); // Informational string (stdout)
    static void w(string); // Warning notice (stderr)
    static void e(string); // Error condition (stderr)

};

#endif /* FEULOG_H_ */
