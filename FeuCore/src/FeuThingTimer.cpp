/*
 * FeuThingTimer.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: akephart
 */

#include "FeuThingTimer.h"

#include <map>

// Method handlers
static double feu_timer_start(FeuThing *,std::vector<double> *);
static double feu_timer_stop(FeuThing *, std::vector<double> *);

// Method table
static feuMethod timerMethods[] = {
    // Name, returnval?, #args, handler
    { "start", false, 0, feu_timer_start },
    { "stop", false, 0, feu_timer_stop },

};

FeuThingTimer::FeuThingTimer(Feu *feu, TiXmlElement *ele, FeuThing *parent) : FeuThing(feu,ele,parent) {
    int i;
    unsigned int period = (unsigned int)intof(mAttributes["period"]);

    // Setup method table
    for (i=0;timerMethods[i].func != NULL; i++) {
        mMethods[timerMethods[i].name] = &timerMethods[i];
    }
    mTimer = new FeuTimer(period);
}


FeuThingTimer::~FeuThingTimer() {
}

/**
 * Implementation of the 'start' method.
 */
static double feu_timer_start(FeuThing *contextThing, std::vector<double> *argv) {
    FeuThingTimer *timerThing = (FeuThingTimer *contextThing);
    FeuLog::i("Starting timer " + timerThing->mName + "...");
    timerThing->mTimer->start();
    return 0.0;
}

static double feu_timer_stop(FeuThing *contextThing, std::vector<double> *argv) {
    FeuThingTimer *timerThing = (FeuThingTimer *contextThing);
    FeuLog::i("Stopping timer " + timerThing->mName + "...");
    timerThing->mTimer->stop();
    return 0.0;
}
