/*
 * FeuThingClass.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#include "feu_all.h"
#include <tinyxml.h>

/*
 * Method table
 */
static float feu_class_create(FeuThing *,std::vector<float> *);

static feuMethod classMethods[] = {
    { "create", false, 0, feu_class_create },
};

FeuThingClass::FeuThingClass(Feu *feu, TiXmlElement *ele, FeuThing *parent) : FeuThing(feu,ele,parent) {
    int i;

    // Setup default attributes
    FEU_THING_DEFAULT_ATTR("source","XBMC.pictures(Export)");
    FEU_THING_DEFAULT_ATTR("sequence","natural");
    FEU_THING_DEFAULT_ATTR("max-count","1");
    FEU_THING_DEFAULT_ATTR("path","BasePath");

    // Setup method table
    for (i=0;classMethods[i].func != NULL; i++) {
        mMethods[classMethods[i].name] = &classMethods[i];
    }

    mSeqNum = 0;

    // Setup default path
    mDefaultPath = (FeuThingPath *)FeuThing::findGlobalThing(mFeu,mAttributes["path"]);

}

FeuThingClass::~FeuThingClass() {
}

static float feu_class_create(FeuThing *contextThing,std::vector<float> *argv) {
    FeuThingPic *pic;
    FeuThingClass *c = (FeuThingClass *)contextThing;
    std::string picName=std::string(c->mName) + stringof(c->mSeqNum++);

    FeuLog::i("In <Class>.create()\n");
    // Step 1: Create a pic 
    pic = new FeuThingPic(c->mFeu,c,picName);

    // Step 2: Puth the pic on a path.
    if (!c->mDefaultPath) {
        c->mDefaultPath = (FeuThingPath *)FeuThing::findGlobalThing(c->mFeu,c->mAttributes["path"]);
    }
    pic->mPath = c->mDefaultPath;

    // Step 3: Register with core
    if (pic && pic->mFeu) pic->mFeu->registerPic(pic);
}

float FeuThingClass::getAttributeValue(std::string attr) {
    // Basic mode ; just use string from XML and convert
    if (mAttributes.count(attr))  {
        // Has it; convert to return 
        return floatof(mAttributes[attr]);
    }
    // Not found?!?!  Warn and return zero.
    FeuLog::w("FeuThingClass:: Attempt to access nonexistent attribute \"" + attr + "\".\n");
    return 0.0;
}

void FeuThingClass::setAttributeValue(std::string attr, float value) {
    // Check for attr to update
    if (0 == mAttributes.count(attr)) {
        FeuLog::w("FeuThingClass:: Attempt to set value of nonexistent attribute \"" + attr + "\".\n");
        return;
    }

    // Got it.  Change the string backing store
    mAttributes[attr] = stringof(value);

    return;
}
