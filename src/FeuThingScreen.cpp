/*
 * FeuThingScreen.cpp
 *
 * Global FeuThing representing the Screen superglobal.
 */

#include "feu_all.h"
#include <tinyxml.h>

FeuThingScreen::FeuThingScreen(int width, int height) : FeuThing((std::string)"Screen") {
    // Add our attributes to the generic map
    mAttributes["width"] = stringof(width);
    mAttributes["height"] = stringof(height);
    return;
}

FeuThingScreen::~FeuThingScreen() {
}
