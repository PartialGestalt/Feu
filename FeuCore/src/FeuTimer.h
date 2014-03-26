/*
 * FeuTimer.h
 *
 * FeuTimer is a class for timing information, primarily for
 * interval calculation.
 */

#ifndef _FEU_TIMER_H_
#define _FEU_TIMER_H_

#include <sys/time.h>

class FeuTimer {
public:
	FeuTimer();
//	virtual ~FeuTimer();

public:
    static double now(); // Get current time, in sec
    static double since(double when); // Get interval, in sec
};

#endif /* _FEU_TIMER_H_ */
