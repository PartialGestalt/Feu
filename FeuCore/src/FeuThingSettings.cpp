/*
 * FeuThingSettings.cpp
 *
 *  Created on: Apr 5, 2014
 *      Author: akephart
 */

#include "FeuThingSettings.h"

FeuThingSettings::FeuThingSettings(Feu *feu, int seed) :
		FeuThing(feu, (std::string) "Settings") {

	// Other bits
	mType = "internal";
	return;

}

FeuThingSettings::~FeuThingSettings() {
	// TODO Auto-generated destructor stub
}

void FeuThingSettings::setSetting(std::string name, double value) {
	// Simply write into our values map
	mValues[name] = value;
}

