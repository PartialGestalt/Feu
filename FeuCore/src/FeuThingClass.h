/*
 * FeuThingClass.h
 *
 * FeuThingClass is a class for the <step> XML element
 */

#ifndef _FEU_THING_CLASS_H_
#define _FEU_THING_CLASS_H_

#include "FeuThing.h"
#include "FeuThingPic.h"

class FeuThingPath;


class FeuThingClass : public FeuThing {
public:
    FeuThingClass(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingClass();

public:
    FeuThingPath *mDefaultPath;
    int mSeqNum;  // Sequence ordinal.

public:
    void harvestPic(FeuThingPic *pic);
    void renderPic(FeuThingPic *pic);
    virtual double getAttributeValue(std::string);
    virtual void  setAttributeValue(std::string,double);
};



#endif /* _FEU_THING_CLASS_H_ */
