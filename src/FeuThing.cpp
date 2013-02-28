/*
 * FeuThing.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#include "feu_all.h"
#include <tinyxml.h>

FeuThing::FeuThing(Feu *feu, TiXmlElement *ele, FeuThing *parent) {
    TiXmlAttribute *attr;
    TiXmlElement *kid;
    FeuThing *kidthing;
    std::string name,value;
    // Basic element(s)
    mFeu = feu;
    mType = ele->ValueStr();
    mName = "<unnamed>";
    // Walk Attribute list, importing as we go
    attr = ele->FirstAttribute();
    while (attr != NULL) {
        name = stringof(attr->Name());
        value = attr->ValueStr();
        FeuLog::i("   \"" + name + "\"  ==>  \"" + value + "\"\n");
        mAttributes[name] = value; // Store in our map
        if (name == "name") mName = value;


        attr = attr->Next();
    }

    // Walk child list, descending as we go
    kid = ele->FirstChildElement();
    while (kid != NULL) {
        kidthing = Feu::convertElement(feu,kid,this);
        if (kidthing != NULL) adopt(kidthing);
        kid = kid->NextSiblingElement();
    }
}

FeuThing::FeuThing(Feu *feu, std::string name) {
    mFeu = feu;
	mParent = NULL;
	mName = name;
}

FeuThing::~FeuThing() {
    std::list<FeuThing *>::iterator iter;
    //FeuLog::i("entering destructor for " + mName + "{" + mType + "}\n");
    for (iter = mKids.begin(); iter != mKids.end(); iter++)
    {
        delete *iter;
    }
}

void FeuThing::adopt(FeuThing *ft_kid) {
	// Mark ourselves as the kid's new parent;
	ft_kid->mParent = this;

	// Add kid to our child list
	mKids.push_back(ft_kid);
}

void FeuThing::adopt_front(FeuThing *ft_kid) {
	// Mark ourselves as the kid's new parent;
	ft_kid->mParent = this;

	// Add kid to our child list
	mKids.push_front(ft_kid);
}

void FeuThing::geneology() {
	// Recurse to all children
    std::list<FeuThing *>::iterator iter;
	for (iter = mKids.begin(); iter != mKids.end(); iter++) {
		(**iter).geneology();
	}

	// Tell ourselves.
    FeuLog::i(mName + "\n");

}

double FeuThing::getAttributeValue(std::string attr) {
    double *pVal;
    // Fast-access map?
    //     CLEAN: TODO: For attributes that don't exist, this actually
    //     creates a bogus entry....we're going to ignore this for now,
    //     because it shouldn't happen across a very wide range of values.
    //     When we're memory optimizing (later), come back to this.
    if (NULL != (pVal = mValues[attr])) return *pVal;

    // Basic mode ; just use string from XML and convert
    if (mAttributes.count(attr))  {
        // Has it; convert to return 
        return doubleof(mAttributes[attr]);
    }

    // Not found?!?!  Warn and return zero.
    FeuLog::w("FeuThing:: Attempt to access nonexistent attribute \"" + attr + "\".\n");
    return 0.0;
}

void FeuThing::setAttributeValue(std::string attr, double value) {
    double *pVal;
    // Does this exist in the fast map?
    if (NULL != (pVal = mValues[attr])) {
        *pVal = value;
        return;
    }

    // Slow path string map?
    if (0 != mAttributes.count(attr)) {
        // Got it.  Change the string backing store
        mAttributes[attr] = stringof(value);
        return;
    }

    // Not found.  Bummer.
    FeuLog::w("FeuThing:: Attempt to set value of nonexistent attribute \"" + mType + "." + attr + "\".\n");
    return;
}

std::list<FeuThing *>::iterator FeuThing::firstChild() {
    return mKids.begin();
}

std::list<FeuThing *>::iterator FeuThing::endChild() {
    return mKids.end();
}

FeuThing *FeuThing::findGlobalThing(Feu *feu, FeuSpecifier *spec) {
    // A "global" is a direct child of the root element.
    std::list<FeuThing *>::iterator i;

    // Check for initialization
    if (!feu->getRoot()) return NULL;

    // Search list
    for (i = feu->getRoot()->mKids.begin(); i != feu->getRoot()->mKids.end(); i++) {
        if ((*i)->mName == spec->mObject) return (*i);
    }
    return NULL;
}

FeuThing *FeuThing::findGlobalThing(Feu *feu, std::string objName) {
    // CLEAN: TODO: Should we switch to a global map registry?
    
    // A "global" is a direct child of the root element.
    std::list<FeuThing *>::iterator i;

    // Check for initialization
    if (!feu->getRoot()) return NULL;

    // Search list
    for (i = feu->getRoot()->mKids.begin(); i != feu->getRoot()->mKids.end(); i++) {
        if ((*i)->mName == objName) return (*i);
    }
    return NULL;
}

FeuThing *FeuThing::findThing(Feu *feu, FeuThing *context, FeuSpecifier *spec)
{
    // For now, things are either global or 'this'.
    if (spec->isSelf()) return context;

    // Look in global space....
    return findGlobalThing(feu,spec);

    // Walk up the chain?
}

void FeuThing::addAction(std::string when, FeuThingAction *action) {
    mActions[when].push_back(action);
}

void FeuThing::addProperty(FeuThingProperty *prop) {
    mProperties.push_back(prop);
}

bool FeuThing::hasAttribute(std::string attrName) {
    return (mAttributes.count(attrName) != 0 ||
            mValues.count(attrName) != 0);
}

bool FeuThing::hasMethod(std::string methName) {
    return (mMethods.count(methName) != 0);
}
