/*
 * FeuTimer.cpp
 */

#include "feu_all.h"
static double tv_to_double(struct timeval *tvp);

FeuTimer::FeuTimer() {
}

#if 0
FeuTimer::~FeuTimer() {
    FeuRefCounted *frc;

    while (!empty()) {
        FeuLog::i("Timer not empty in destructor\n");
        frc = pop();
        if (!frc->ref_count()) delete frc;
    }
}
#endif

static inline double tv_to_double(struct timeval *tvp) {
    return ((double)(tv.tv_sec) + ((double)(tv.tv_usec))/1000000;
}

double FeuTimer::now(void) {
    struct timeval tv;
    double retval;

    gettimeofday(&tv,NULL);
    return tv_to_double(&tv);
}

double FeuTimer::since(double when) {
    double nowval;
    gettimeofday(&nowval,NULL);
    return tv_to_double(&nowval) - when;
}
