/*
 * FeuThingRandom.h
 *
 * FeuThingRandom is a class for the <step> XML element
 */

#ifndef _FEU_THING_RANDOM_H_
#define _FEU_THING_RANDOM_H_

#include "FeuThing.h"

class FeuThingRandom : public FeuThing {
public:
    FeuThingRandom(Feu *,int);
    ~FeuThingRandom();
};



#endif /* _FEU_THING_RANDOM_H_ */
