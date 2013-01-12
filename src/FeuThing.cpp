/*
 * FeuThing.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#include "feu.h"
#include <tinyxml.h>

FeuThing::FeuThing(TiXmlElement *ele, FeuThing *parent) {
    TiXmlAttribute *attr;
    TiXmlElement *kid;
    FeuThing *kidthing;
    std::string name,value;
    // Basic element(s)
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
        kidthing = FeuXML::convertElement(kid);
        if (kidthing != NULL) adopt(kidthing);
        kid = kid->NextSiblingElement();
    }
}

FeuThing::FeuThing(std::string name) {
	mParent = NULL;
	mName = name;
}

FeuThing::~FeuThing() {
    std::list<FeuThing *>::iterator iter;
    FeuLog::i("entering destructor for " + mName + "{" + mType + "}\n");
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

void FeuThing::geneology() {
	// Recurse to all children
    std::list<FeuThing *>::iterator iter;
	for (iter = mKids.begin(); iter != mKids.end(); iter++) {
		(**iter).geneology();
	}

	// Tell ourselves.
    FeuLog::i(mName + "\n");

}

float FeuThing::getAttributeValue(std::string attr) {
    // Basic mode ; just use string from XML and convert
    if (mAttributes.count(attr))  {
        // Has it; convert to return 
        return floatof(mAttributes[attr]);
    }
    // Not found?!?!  Warn and return zero.
    FeuLog::w("FeuThing:: Attempt to access nonexistent attribute \"" + attr + "\".\n");
    return 0.0;
}

void FeuThing::setAttributeValue(std::string attr, float value) {
    // Check for attr to update
    if (0 == mAttributes.count(attr)) {
        FeuLog::w("FeuThing:: Attempt to set value of nonexistent attribute \"" + attr + "\".\n");
        return;
    }

    // Got it.  Change the string backing store
    mAttributes[attr] = stringof(value);

    return;
}

FeuThing *FeuThing::findThing(FeuThing *context, FeuSpecifier *spec)
{
    
}

