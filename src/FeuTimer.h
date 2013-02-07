/*
 * FeuTimer.h
 *
 * FeuTimer is a class for timing information; 
 */

#ifndef _FEU_TIMER_H_
#define _FEU_TIMER_H_

class FeuTimer {
public:
	FeuTimer();
	virtual ~FeuTimer();

public:
    static float now(); // Get current time
};

#endif /* _FEU_TIMER_H_ */
