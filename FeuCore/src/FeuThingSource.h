/*
 * FeuThingSource.h
 *
 * FeuThingSource is a class for the <source> XML element, and
 * is the specification for a particular image loader.
 */

#ifndef _FEU_THING_SOURCE_H_
#define _FEU_THING_SOURCE_H_

#include "FeuThing.h"

class FeuThingSource : public FeuThing {
public:
    FeuThingSource(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingSource();

private:

public:
};



#endif /* _FEU_THING_SOURCE_H_ */
