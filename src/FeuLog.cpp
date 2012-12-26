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

void FeuLog::d(string msg) {
#ifdef FEU_DEBUG
    cout << "[FEU DEBUG]: " << msg;
#endif
}

void FeuLog::w(string msg) {
    cerr << "[FEU Warning]: " << msg;
}

void FeuLog::e(string msg) {
    cerr << "[FEU !ERROR!]: " << msg;
}
