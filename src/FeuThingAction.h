/*
 * FeuThingAction.h
 *
 * FeuThingAction is a class for the <action> XML element
 */

#ifndef FEUTHINGACTION_H_
#define FEUTHINGACTION_H_

#include "FeuThing.h"

class FeuThingAction : public FeuThing {
public:
    FeuThingAction(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingAction();

private:
    FeuCalculable *mWhat; // From the "what" attribute

public:
    virtual float getAttributeValue(std::string);
    virtual void  setAttributeValue(std::string,float);

};



#endif /* FEUTHINGACTION_H_ */
