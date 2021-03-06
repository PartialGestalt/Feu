/*
 * FeuThingSettings.h
 *
 *  Created on: Apr 5, 2014
 *      Author: akephart
 */

#ifndef FEUTHINGSETTINGS_H_
#define FEUTHINGSETTINGS_H_

#include "FeuThing.h"

class FeuThingSettings: public FeuThing {
public:
	FeuThingSettings(Feu *,int);
	virtual ~FeuThingSettings();
private:
	std::map<std::string,double> mCache;  // Cache of settings values.

public:
	void setSetting(std::string,double);
};

#endif /* FEUTHINGSETTINGS_H_ */
