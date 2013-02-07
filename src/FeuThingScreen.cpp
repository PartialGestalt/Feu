/*
 * FeuThingScreen.cpp
 *
 * Global FeuThing representing the Screen superglobal.
 */

#include "feu_all.h"
#include <tinyxml.h>

FeuThingScreen::FeuThingScreen(Feu *feu, int width, int height) : FeuThing(feu, (std::string)"Screen") {
    // Set our internals
    //    (The method calls allow for derivative calculations)
    setWidth(width);
    setHeight(height);

    // Add our basic attributes to the fast values map
    mValues["width"] = &mWidth;
    mValues["left"] = &mLeft;
    mValues["right"] = &mRight;

    mValues["height"] = &mHeight;
    mValues["top"] = &mTop;
    mValues["bottom"] = &mBottom;

    // Faked up XML element type
    mType="internal";
    return;
}

FeuThingScreen::~FeuThingScreen() {
}

void FeuThingScreen::setWidth(int width) {
    mWidth = (float)width;
    mLeft = -mWidth/2;
    mRight = mLeft + mWidth;
    return;
}

void FeuThingScreen::setHeight(int height) {
    mHeight = (float)height;
    mTop = -mHeight/2;
    mBottom = mTop + mHeight;
}
