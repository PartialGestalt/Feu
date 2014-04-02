/*
 * FeuTimer.h
 *
 * FeuTimer is a class for timing information, primarily for
 * interval calculation.  This is only for data storage; no
 * interrupts or other processing is included here.
 */

#ifndef _FEU_TIMER_H_
#define _FEU_TIMER_H_

#include <sys/time.h>

class FeuTimer {
private:
	double       mOrigin; // Time timer was started.
	double       mExpiry; // When the timer expires.
	unsigned int mPeriod; // Length of time to time, in msec
	bool         mIsRunning; // If the timer is running.

public:
	FeuTimer();
	FeuTimer(unsigned int periodMsecs);
//	virtual ~FeuTimer();

public:
    static double now(); // Get current time, in sec
    static double since(double when); // Get interval, in sec
    static double add(double origin, double period); // Add times
    static double addMsecs(double origin, unsigned int msecs); // Add msecs
    bool isRunning();
    bool isExpired();
    unsigned int setPeriod(int period);
    void stop(); // Stop the timer
    void start(); // Start the timer.

private:
    void initialize(unsigned int periodMsecs);

};

#endif /* _FEU_TIMER_H_ */
