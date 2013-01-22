/*
 * FeuThingScreen.cpp
 *
 * Global FeuThing representing the Screen superglobal.
 */

#include "feu_all.h"
#include <tinyxml.h>

FeuThingScreen::FeuThingScreen(Feu *feu, int width, int height) : FeuThing(feu, (std::string)"Screen") {
    // Add our attributes to the generic map
    mAttributes["width"] = stringof(width);
    mAttributes["height"] = stringof(height);
    // Other custom bits
    mType="internal";
    return;
}

FeuThingScreen::~FeuThingScreen() {
}
