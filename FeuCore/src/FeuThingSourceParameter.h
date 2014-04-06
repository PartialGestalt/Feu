/*
 * FeuThingSourceParameter.h
 *
 * FeuThingSourceParameter is a class for the <source-parameter> XML element,
 * and defines a parameter to be given to an image loader.  This may control
 * sequencing, location, etc.
 */

#ifndef _FEU_THING_SOURCE_PARAMETER_H_
#define _FEU_THING_SOURCE_PARAMETER_H_

#include "FeuThing.h"

class FeuThingSourceParameter : public FeuThing {
public:
    FeuThingSourceParameter(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingSourceParameter();

public:
};



#endif /* _FEU_THING_SOURCE_PARAMETER_H_ */
