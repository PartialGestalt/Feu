/*
 * FeuLog.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#include "feu.h"

FeuLog::FeuLog() {
}

FeuLog::~FeuLog() {
}

void FeuLog::i(string msg) {
    cout << "[FEU Info]: " << msg;
}

void FeuLog::i(string msg1, string msg2) {
    cout << "[FEU Info]: " << msg1 << msg2;
}

void FeuLog::i(string msg1, string msg2, string msg3) {
    cout << "[FEU Info]: " << msg1 << msg2 << msg3;
}

void FeuLog::d(string msg) {
#ifdef FEU_DEBUG
    cout << "[FEU DEBUG]: " << msg;
#endif
}

void FeuLog::d(string msg1, string msg2) {
#ifdef FEU_DEBUG
    cout << "[FEU DEBUG]: " << msg1 << msg2;
#endif
}

void FeuLog::d(string msg1, string msg2, string msg3) {
#ifdef FEU_DEBUG
    cout << "[FEU DEBUG]: " << msg1 << msg2 << msg3;
#endif
}


void FeuLog::w(string msg) {
    cerr << "[FEU Warning]: " << msg;
}

void FeuLog::w(string msg1, string msg2) {
    cout << "[FEU Warning]: " << msg1 << msg2;
}

void FeuLog::w(string msg1, string msg2, string msg3) {
    cout << "[FEU Warning]: " << msg1 << msg2 << msg3;
}

void FeuLog::e(string msg) {
    cerr << "[FEU !ERROR!]: " << msg;
}

void FeuLog::e(string msg1, string msg2) {
    cerr << "[FEU !ERROR!]: " << msg1 << msg2;
}

void FeuLog::e(string msg1, string msg2, string msg3) {
    cerr << "[FEU !ERROR!]: " << msg1 << msg2 << msg3;
}
