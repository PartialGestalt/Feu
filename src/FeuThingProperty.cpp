/*
 * FeuThingProperty.cpp
 */

#include "feu_all.h"
#include <tinyxml.h>

FeuThingProperty::FeuThingProperty(Feu *feu, TiXmlElement *ele, FeuThing *parent) : FeuThing(feu,ele,parent) {
    // Properties _MUST_ define both a "name" attribute, and it must not contain a dot.
    if (!mAttributes.count("name") || !mAttributes.count("value")) {
        FeuLog::w("(" + feu->mFilename + ":" + stringof(ele->Row()) + "): Property declared with missing \"name\" or \"value\" attributes.\n");
        throw (new FeuException("Syntax Error","property definition"));
    }
    // Create specials from attributes 
    mPropCalc = new FeuCalculable(feu,mAttributes["value"],this);

    // Attach ourselves to the parent property map
    parent->addProperty(this);
}

FeuThingProperty::~FeuThingProperty() {
    delete mPropCalc;
}


struct feuPropInfo *FeuThingProperty::getPropInfo(FeuThing *contextThing) {
    // A feuPropInfo struct is our simple collapsed instance
    struct feuPropInfo *retInfo = new feuPropInfo();

    if (!retInfo) return NULL;

    // Setup name from our attribute
    retInfo->propName = &(mAttributes["name"]);

    // Run the calculable to get a starting value
    retInfo->propValue = mPropCalc->proc(contextThing);

    return retInfo;
}

void FeuThingProperty::releasePropInfo(struct feuPropInfo *pInfo) {
    // This may need to be more complex later, but for now it's
    // pretty simple.
    delete pInfo;
}
