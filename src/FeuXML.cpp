/*
 * FeuXML.cpp
 *
 */

#include "feu.h"
#include <tinyxml.h>

FeuXML::FeuXML(std::string filename) {
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

FeuXML::~FeuXML() {
    delete mRoot;
    delete mDoc;
}

FeuThing *FeuXML::convertElement(TiXmlElement *ele) {
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
