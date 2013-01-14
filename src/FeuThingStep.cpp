/*
 * FeuThingStep.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#include "feu_all.h"
#include <tinyxml.h>

FeuThingStep::FeuThingStep(Feu *feu, TiXmlElement *ele, FeuThing *parent) : FeuThing(feu,ele,parent) {
    // Base class init goes here.
    // Set defaults for any missing attributes
    if (!mAttributes.count("condition")) {
        mAttributes["condition"] = "1";
    }
    if (!mAttributes.count("x")) {
        mAttributes["x"] = "0";
    }
    if (!mAttributes.count("y")) {
        mAttributes["y"] = "0";
    }
    if (!mAttributes.count("z")) {
        mAttributes["z"] = "0";
    }
    // Create calculables from attributes 
    // CLEAN: TODO: These don't really go here.  These should be
    // attached to the picture things.  We're just doing this here
    // for testing....
    mCondition = new FeuCalculable(feu,mAttributes["condition"],this);
    mX = new FeuCalculable(feu,mAttributes["x"],this);
    mY = new FeuCalculable(feu,mAttributes["y"],this);
    mZ = new FeuCalculable(feu,mAttributes["z"],this);
}

FeuThingStep::~FeuThingStep() {
    delete mZ;
    delete mY;
    delete mX;
    delete mCondition;
}


float FeuThingStep::getAttributeValue(std::string attr) {
    // Basic mode ; just use string from XML and convert
    if (mAttributes.count(attr))  {
        // Has it; convert to return 
        return floatof(mAttributes[attr]);
    }
    // Not found?!?!  Warn and return zero.
    FeuLog::w("FeuThingStep:: Attempt to access nonexistent attribute \"" + attr + "\".\n");
    return 0.0;
}

void FeuThingStep::setAttributeValue(std::string attr, float value) {
    // Check for attr to update
    if (0 == mAttributes.count(attr)) {
        FeuLog::w("FeuThingStep:: Attempt to set value of nonexistent attribute \"" + attr + "\".\n");
        return;
    }

    // Got it.  Change the string backing store
    mAttributes[attr] = stringof(value);

    return;
}
