/*
 * FeuThingScreen.h
 *
 * FeuThingScreen is a class for the <step> XML element
 */

#ifndef FEUTHINGSCREEN_H_
#define FEUTHINGSCREEN_H_

#include "FeuThing.h"

class FeuThingScreen : public FeuThing {
public:
    FeuThingScreen(Feu *,int,int);
    ~FeuThingScreen();
};



#endif /* FEUTHINGSCREEN_H_ */
