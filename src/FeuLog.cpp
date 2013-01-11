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

void FeuLog::i(std::string msg) {
    std::cout << "[FEU Info]: " << msg;
}

void FeuLog::i(std::string msg1, std::string msg2) {
    std::cout << "[FEU Info]: " << msg1 << msg2;
}

void FeuLog::i(std::string msg1, std::string msg2, std::string msg3) {
    std::cout << "[FEU Info]: " << msg1 << msg2 << msg3;
}

void FeuLog::d(std::string msg) {
#ifdef FEU_DEBUG
    std::cout << "[FEU DEBUG]: " << msg;
#endif
}

void FeuLog::d(std::string msg1, std::string msg2) {
#ifdef FEU_DEBUG
    std::cout << "[FEU DEBUG]: " << msg1 << msg2;
#endif
}

void FeuLog::d(std::string msg1, std::string msg2, std::string msg3) {
#ifdef FEU_DEBUG
    std::cout << "[FEU DEBUG]: " << msg1 << msg2 << msg3;
#endif
}


void FeuLog::w(std::string msg) {
    std::cerr << "[FEU Warning]: " << msg;
}

void FeuLog::w(std::string msg1, std::string msg2) {
    std::cout << "[FEU Warning]: " << msg1 << msg2;
}

void FeuLog::w(std::string msg1, std::string msg2, std::string msg3) {
    std::cout << "[FEU Warning]: " << msg1 << msg2 << msg3;
}

void FeuLog::e(std::string msg) {
    std::cerr << "[FEU !ERROR!]: " << msg;
}

void FeuLog::e(std::string msg1, std::string msg2) {
    std::cerr << "[FEU !ERROR!]: " << msg1 << msg2;
}

void FeuLog::e(std::string msg1, std::string msg2, std::string msg3) {
    std::cerr << "[FEU !ERROR!]: " << msg1 << msg2 << msg3;
}
