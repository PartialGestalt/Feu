/*
 * FeuThingTimer.h
 *
 *  Created on: Mar 31, 2014
 *      Author: akephart
 */

#ifndef FEUTHINGTIMER_H_
#define FEUTHINGTIMER_H_

#include "FeuThing.h"

class FeuThingTimer: public FeuThing {
public:
	FeuThingTimer(Feu *feu, TiXmlElement *ele, FeuThing *parent);
	virtual ~FeuThingTimer();

private:
	FeuTimer *mTimer; // Actual timer object
};

#endif /* FEUTHINGTIMER_H_ */
