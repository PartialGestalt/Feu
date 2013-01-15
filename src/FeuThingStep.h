/*
 * FeuThingStep.h
 *
 * FeuThingStep is a class for the <step> XML element
 */

#ifndef _FEU_THING_STEP_H_
#define _FEU_THING_STEP_H_

class FeuThingStep : public FeuThing {
public:
    FeuThingStep(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingStep();

private:
    FeuCalculable *mCondition; // From the "condition" attribute
    FeuCalculable *mX;
    FeuCalculable *mY;
    FeuCalculable *mZ;

public:
    virtual float getAttributeValue(std::string);
    virtual void  setAttributeValue(std::string,float);

};



#endif /* _FEU_THING_STEP_H_ */
