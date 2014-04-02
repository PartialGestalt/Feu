/*
 * FeuTimer.cpp
 */

#include "FeuTimer.h"

#include <stddef.h>

static double tv_to_double(struct timeval *tvp);

FeuTimer::FeuTimer() {
    initialize(0);
}

FeuTimer::FeuTimer(unsigned int periodMsecs) {
    initialize(periodMsecs);
}

void FeuTimer::initialize(unsigned int period) {
    mPeriod = period;
    mOrigin = 0.0;
    mExpiry = 0.0;
    mIsRunning = false;
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
    return (((double)(tvp->tv_sec)) + ((double)(tvp->tv_usec)) / 1000000);
}

double FeuTimer::now(void) {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv_to_double(&tv);
}

double FeuTimer::since(double when) {
    struct timeval nowval;
    gettimeofday(&nowval, NULL);
    return tv_to_double(&nowval) - when;
}

double FeuTimer::add(double base, double addend) {
    return base + addend;
}

double FeuTimer::addMsecs(double base, unsigned int msecs) {
    double addend = ((double)msecs) / ((double)(1000.0));
    return add(base, addend);
}

bool FeuTimer::isExpired() {
    if ((true == mIsRunning) && (mExpiry > now())) {
        return true;
    }
    return false;
}

bool FeuTimer::isRunning() {
    return mIsRunning;
}

/**
 * Simply mark timer as stopped.
 */
void FeuTimer::stop() {
    mIsRunning = false;
    return;
}

/**
 * (Re)start a timer; set expiry to now() plus period and mark as running
 */
void FeuTimer::start() {
    mOrigin = now();
    mExpiry = addMsecs(mOrigin,mPeriod);
    mIsRunning = true;
}
