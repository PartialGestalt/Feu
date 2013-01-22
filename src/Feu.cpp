/*
 * Feu.cpp
 *
 * The Feu is the toplevel object for a Feu ruleset.
 */

#include "feu_all.h"
#include <tinyxml.h>

Feu *lastRuleset = NULL;


Feu::Feu(std::string filename) : mRoot(NULL),mFilename(filename) {
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
        mRoot = convertElement(this,mDoc->RootElement(),NULL);
    }
    // Create superglobals (at the front of the list)
    mScreen = new FeuThingScreen(this,1280,1024);
    mRoot->adopt_front(mScreen);
    mRandom = new FeuThingRandom(this,(int)time(NULL));
    mRoot->adopt_front(mRandom);

    // Finally, do deferred calculable resolution and preprocessing
    {
        std::list<FeuCalculable *>::iterator i;
        for (i=mCalculables.begin(); i != mCalculables.end(); i++) {
            (*i)->rpn();
        }
    }
}

Feu::~Feu() {
    FeuThingPic *pic;

    // Delete any pics left around
    while (!mPics.empty()) {
        pic = mPics.front();
        mPics.pop_front();
        delete pic;
    }

    delete mRoot; // Also deletes all superglobals
    delete mDoc;

}


FeuThing *Feu::getRoot() {
    return mRoot;
}

FeuThing *Feu::convertElement(Feu *feu, TiXmlElement *ele, FeuThing *parent) {
    std::string eletype = ele->ValueStr();
    // Try to create a FeuThing from the XML element
    FeuLog::i("convertElement of type: \"" + eletype + "\"\n");
    // Choose class from name
    if (eletype == "step") {
        return new FeuThingStep(feu, ele, parent);
    } else if (eletype == "action") {
        return new FeuThingAction(feu,ele,parent);
    } else if (eletype == "class") {
        return new FeuThingClass(feu,ele,parent);
    } else if (eletype == "path") {
        return new FeuThingPath(feu,ele,parent);
    } else {
        // Anything unknown gets a plain FeuThing
        return new FeuThing(feu, ele, parent );
    }
}

void Feu::runEvent(std::string eventName) {
    std::list<FeuThingAction *>::iterator i;
    FeuLog::i("Running \"" + eventName + "\" handlers.\n");

    for (i=mRoot->mActions[eventName].begin(); 
         i != mRoot->mActions[eventName].end(); 
         i++) {
       FeuThingAction *thing = *i;
       FeuLog::i("\t Handler: \"" + thing->mAttributes["what"] + "\"\n");
       thing->proc();
    }

}

void Feu::run() {
    FeuLog::i("[FEU]: Running a single frame.\n");
}

void Feu::registerCalculable(FeuCalculable *feucalc) {
    mCalculables.push_back(feucalc);
}

int Feu::registerPic(FeuThingPic *pic) {
    if (!pic) return 0;
    mPics.push_back(pic);
    return 1;  // Return # of elements added
}

int Feu::unregisterPic(FeuThingPic *pic) {
    std::list<FeuThingPic *>::iterator i;
    // Scan list for picture 
    for (i = mPics.begin(); i != mPics.end(); i++) {
        if (*i == pic) {
            mPics.erase(i);
            return 1; // Return # erased
        }
    }

    return 0;
}

