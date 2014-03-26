/*
 * FeuThingPath.h
 *
 * FeuThingPath is a class for the <path> XML element, and
 * is really just a container for steps.
 */

#ifndef _FEU_THING_PATH_H_
#define _FEU_THING_PATH_H_

#include "FeuThing.h"

class FeuThingPath : public FeuThing {
public:
    FeuThingPath(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingPath();

private:

public:
};



#endif /* _FEU_THING_PATH_H_ */
