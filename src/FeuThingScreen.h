/*
 * FeuThingScreen.h
 *
 * FeuThingScreen is a class for the <step> XML element
 */

#ifndef _FEU_THING_SCREEN_H_
#define _FEU_THING_SCREEN_H_

#include "FeuThing.h"

class FeuThingScreen : public FeuThing {
public:
    FeuThingScreen(Feu *,int,int);
    ~FeuThingScreen();

public:
    float mWidth;
    float mHeight;
    float mLeft;
    float mRight;
    float mTop;
    float mBottom;

public:
    void setWidth(int width);
    void setHeight(int height);
};



#endif /* _FEU_THING_SCREEN_H_ */
