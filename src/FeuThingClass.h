/*
 * FeuThingClass.h
 *
 * FeuThingClass is a class for the <step> XML element
 */

#ifndef _FEU_THING_CLASS_H_
#define _FEU_THING_CLASS_H_

class FeuThing;

class FeuThingClass : public FeuThing {
public:
    FeuThingClass(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingClass();

public:
    FeuThingPath *mDefaultPath;
    int mSeqNum;  // Seuquence ordinal.

public:
    void harvestPic(FeuThingPic *pic);
    void renderPic(FeuThingPic *pic);
    virtual float getAttributeValue(std::string);
    virtual void  setAttributeValue(std::string,float);
};



#endif /* _FEU_THING_CLASS_H_ */
