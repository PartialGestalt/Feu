/*
 * Feu.cpp
 *
 * The Feu is the toplevel object for a Feu ruleset.
 */

#include "feu_all.h"
#include <tinyxml.h>

Feu *lastRuleset = NULL;


Feu::Feu(std::string filename) {
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
        mRoot = convertElement(this,mDoc->RootElement());
    }
}

Feu::~Feu() {
    delete mRoot;
    delete mDoc;
}

FeuThing *Feu::convertElement(Feu *feu, TiXmlElement *ele) {
    std::string eletype = ele->ValueStr();
    // Try to create a FeuThing from the XML element
    FeuLog::i("convertElement of type: \"" + eletype + "\"\n");
    // Choose class from name
    if (eletype == "step") {
        return new FeuThingStep(feu, ele);
    } else {
        // Anything unknown gets a plain FeuThing
        return new FeuThing(feu, ele);
    }
}
