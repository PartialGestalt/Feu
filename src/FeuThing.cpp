/*
 * FeuThing.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#include "feu.h"

FeuThing::FeuThing(string name) {
	// TODO Auto-generated constructor stub
	mParent = NULL;
	mName = name;
    FeuLog::i("CONSTRUCT: FeuThing()\n");
}

FeuThing::~FeuThing() {
    // Destroy all children
    list<FeuThing *>::iterator iter;
    FeuLog::i("entering destructor for " + mName + "\n");
    for (iter = mKids.begin(); iter != mKids.end(); iter++)
    {
        delete *iter;
    }

    // Destroy ourselves!
    FeuLog::i("destroying myself: " + mName + "\n");

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
