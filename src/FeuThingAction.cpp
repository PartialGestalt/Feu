/*
 * FeuThingAction.cpp
 */

#include "feu_all.h"
#include <tinyxml.h>

FeuThingAction::FeuThingAction(Feu *feu, TiXmlElement *ele, FeuThing *parent) : FeuThing(feu,ele,parent) {
    // Actions _MUST_ define both a "when" and a "what" attribute.
    if (!mAttributes.count("when") || !(mAttributes.count("what"))) {
        FeuLog::w("(" + feu->mFilename + ":" + stringof(ele->Row()) + "): Action declared with missing \"when\" or \"what\" attributes.\n");
    }
    // Create calculables from attributes 
    mWhat = new FeuCalculable(feu,mAttributes["what"],this);

    // Attach ourselves to the parent action map for the "when" event
    parent->addAction(mAttributes["when"],this);
}

FeuThingAction::~FeuThingAction() {
    delete mWhat;
}


float FeuThingAction::getAttributeValue(std::string attr) {
    // Basic mode ; just use string from XML and convert
    if (mAttributes.count(attr))  {
        // Has it; convert to return 
        return floatof(mAttributes[attr]);
    }
    // Not found?!?!  Warn and return zero.
    FeuLog::w("FeuThingAction:: Attempt to access nonexistent attribute \"" + attr + "\".\n");
    return 0.0;
}

void FeuThingAction::setAttributeValue(std::string attr, float value) {
    // Check for attr to update
    if (0 == mAttributes.count(attr)) {
        FeuLog::w("FeuThingAction:: Attempt to set value of nonexistent attribute \"" + attr + "\".\n");
        return;
    }

    // Got it.  Change the string backing store
    mAttributes[attr] = stringof(value);

    return;
}
