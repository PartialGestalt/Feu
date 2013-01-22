/*
 * FeuThingPicPic.cpp
 *
 */

#include "feu_all.h"

FeuThingPic::FeuThingPic(Feu *feu, FeuThingClass *parent, std::string name) : FeuThing(feu, name) {
    // Init some of our basics; anything not here is the responsibility of the path or class
    // to initialize (e.g. position and size)
    mFeu = feu;
    mAge = 0.0;
    mAlpha = 1.0;
    mParent = parent;
    mPath = NULL;  // Must be set by parent FeuThingClass.
    mType = "displayable";

    // After creation, the parent FeuThingClass must:
    //   1. Append any class-specific properties (using addProperty())
    //   2. Put the pic onto a path (using setPath())
    //   3. Register the pic with the core.

}

FeuThingPic::~FeuThingPic() {
    // Deregister 
    mFeu->unregisterPic(this);
}

float FeuThingPic::getAttributeValue(std::string attr) {
    // Step 1: One of our well-known shortcut values?
    // Use a switch on first char for 
    
    // Step 2: One of our class-defined parameters?

    // Basic mode ; just use string from XML and convert
    if (mAttributes.count(attr))  {
        // Has it; convert to return 
        return floatof(mAttributes[attr]);
    }
    // Not found?!?!  Warn and return zero.
    FeuLog::w("FeuThingPic:: Attempt to access nonexistent attribute \"" + attr + "\".\n");
    return 0.0;
}

void FeuThingPic::setAttributeValue(std::string attr, float value) {
    // Check for attr to update
    if (0 == mAttributes.count(attr)) {
        FeuLog::w("FeuThingPic:: Attempt to set value of nonexistent attribute \"" + attr + "\".\n");
        return;
    }

    // Got it.  Change the string backing store
    mAttributes[attr] = stringof(value);

    return;
}

void FeuThingPic::runFrame() {
    bool done = false;

    // Step 1: If we're not on a path, there's nothing to do.
    if (!mPath) return;

    // Step 2: Cycle through all the steps in our current path
}
