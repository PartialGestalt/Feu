/*
 * FeuThingClass.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#include <tinyxml.h>
#include "FeuThingClass.h"
#include "FeuLog.h"
#include "FeuThingScreen.h"
/*
 * Method table
 */
static double feu_class_create(FeuThing *, std::vector<double> *);

static feuMethod classMethods[] = { { "create", false, 0, feu_class_create }, };

FeuThingClass::FeuThingClass(Feu *feu, TiXmlElement *ele, FeuThing *parent) :
		FeuThing(feu, ele, parent) {
	int i;

	// Setup default attributes
	FEU_THING_DEFAULT_ATTR("source", "XBMC.pictures(Export)");
	FEU_THING_DEFAULT_ATTR("sequence", "natural");
	FEU_THING_DEFAULT_ATTR("max-count", "4");
	FEU_THING_DEFAULT_ATTR("path", "BasePath");

	// Setup method table
	for (i = 0; classMethods[i].func != NULL; i++) {
		mMethods[classMethods[i].name] = &classMethods[i];
	}

	mSeqNum = 0;

	// Setup default path
	mDefaultPath = (FeuThingPath *) FeuThing::findGlobalThing(mFeu,
			mAttributes["path"]);

	// Setup max count
	mActiveMax = intof(mAttributes["max-count"]);

	FeuLog::i(
			"Setup class \"" + mName + "\" with default path \""
					+ mAttributes["path"] + "\" and max active count "
					+ stringof(mActiveMax));

}

FeuThingClass::~FeuThingClass() {
}

static double feu_class_create(FeuThing *contextThing,
		std::vector<double> *argv) {
	FeuThingPic *pic;
	FeuThingClass *c = (FeuThingClass *) contextThing;
	std::string picName = std::string(c->mName) + "[" + stringof(c->mSeqNum)
			+ "]";

	FeuLog::i("In <Class>.create()\n");
	// Step 1: Create a pic
	pic = new FeuThingPic(c->mFeu, c, picName);

	// Step 2: Puth the pic on a path.
	if (!c->mDefaultPath) {
		c->mDefaultPath = (FeuThingPath *) FeuThing::findGlobalThing(c->mFeu,
				c->mAttributes["path"]);
	}
	pic->mPath = c->mDefaultPath;

	// Step 3: Fill in other new bits
	pic->mXpos = pic->mYpos = pic->mZpos = 0.0;
	pic->mXrot = pic->mYrot = pic->mZrot = 0.0;
	pic->mWidth = c->mFeu->mScreen->mWidth;
	pic->mHeight = c->mFeu->mScreen->mHeight;
	pic->mDepth = 0;
	pic->mAlpha = 1.0;
	pic->mOrdinal = c->mSeqNum;

	// Step 4: Add custom properties
	//    ...globals...
	pic->addProperties(c->mFeu->getRoot());
	//    .. class-specific...
	pic->addProperties(c);

	// Step 5: Register with class and core
	if (pic->mFeu)
		pic->mFeu->registerPic(pic);
	c->mPics.push_back(pic);

	// Step 6: Bump our ordinal sequence number
	c->mSeqNum++;

	// Step 7: Check for too many images
	if (c->mPics.size() > c->mActiveMax) {
		FeuThingPic *old = c->mPics.front();
		pic->mFeu->mDeadPics.push_back(old);
	}

	// Step 8: All methods return double.
	return 0.0;
}

double FeuThingClass::getAttributeValue(std::string attr) {
	// Basic mode ; just use string from XML and convert
	if (mAttributes.count(attr)) {
		// Has it; convert to return
		return doubleof(mAttributes[attr]);
	}
	// Not found?!?!  Warn and return zero.
	FeuLog::w(
			"FeuThingClass:: Attempt to access nonexistent attribute \"" + attr
					+ "\".\n");
	return 0.0;
}

void FeuThingClass::setAttributeValue(std::string attr, double value) {
	// Check for attr to update
	if (0 == mAttributes.count(attr)) {
		FeuLog::w(
				"FeuThingClass:: Attempt to set value of nonexistent attribute \""
						+ attr + "\".\n");
		return;
	}

	// Got it.  Change the string backing store
	mAttributes[attr] = stringof(value);

	return;
}

void FeuThingClass::harvestPic(FeuThingPic *pic) {
	// Remove from our internal list
	std::list<FeuThingPic *>::iterator i;
	for (i = mPics.begin(); i != mPics.end(); i++) {
		if (*i == pic) {
			mPics.erase(i);
			break;
		}
	}
	FeuLog::i("Harvesting pic \"" + pic->mName + "\"");
	delete pic;

}

void FeuThingClass::renderPic(FeuThingPic *pic) {
	// Update this image's visual representation onscreen, based on its position
	// and other properties
}
