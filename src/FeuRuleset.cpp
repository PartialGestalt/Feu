/*
 * FeuRuleset.cpp
 *
 * The FeuRuleset is the toplevel object for a Feu ruleset.
 */

#include "feu.h"
#include <tinyxml.h>

FeuRuleset *lastRuleset = NULL;


FeuRuleset::FeuRuleset(std::string filename) {
    // Just load/verify file
    mDoc = new TiXmlDocument(filename);
    if (mDoc != NULL) {
        mDoc->LoadFile();
        if (mDoc->Error()) {
            // CLEAN: TODO: Throw an exception here.
            FeuLog::e("Document Load error (" + filename + ":" + stringof(mDoc->ErrorRow()) + "): ",stringof(mDoc->ErrorDesc()),"\n");
            return;
        }
    }
    if (mDoc && mDoc->RootElement()) {
        mRoot = convertElement(mDoc->RootElement());
    }
}

FeuRuleset::~FeuRuleset() {
    delete mRoot;
    delete mDoc;
}

FeuThing *FeuRuleset::convertElement(TiXmlElement *ele) {
    std::string eletype = ele->ValueStr();
    // Try to create a FeuThing from the XML element
    FeuLog::i("convertElement of type: \"" + eletype + "\"\n");
    // Choose class from name
    if (eletype == "step") {
        return new FeuThingStep(ele);
    } else {
        // Anything unknown gets a plain FeuThing
        return new FeuThing(ele);
    }
}
