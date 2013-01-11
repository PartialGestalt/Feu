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
    string name,value;
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

FeuThing::FeuThing(string name) {
	mParent = NULL;
	mName = name;
    FeuLog::i("CONSTRUCT: FeuThing()\n");
}

FeuThing::~FeuThing() {
    list<FeuThing *>::iterator iter;
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
	list<FeuThing *>::iterator iter;
	for (iter = mKids.begin(); iter != mKids.end(); iter++) {
		(**iter).geneology();
	}

	// Tell ourselves.
    FeuLog::i(mName + "\n");

}
