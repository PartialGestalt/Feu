/*
 * FeuThingStep.h
 *
 * FeuThingStep is a class for the <step> XML element
 */

#ifndef FEUTHINGSTEP_H_
#define FEUTHINGSTEP_H_

class FeuThingStep : public FeuThing {
public:
    FeuThingStep(Feu *feu, TiXmlElement *, FeuThing *parent = NULL);
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



#endif /* FEUTHINGSTEP_H_ */
