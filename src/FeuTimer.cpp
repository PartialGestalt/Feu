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
    return (((double)(tvp->tv_sec)) + ((double)(tvp->tv_usec))/1000000);
}

double FeuTimer::now(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return tv_to_double(&tv);
}

double FeuTimer::since(double when) {
    struct timeval nowval;
    gettimeofday(&nowval,NULL);
    return tv_to_double(&nowval) - when;
}
