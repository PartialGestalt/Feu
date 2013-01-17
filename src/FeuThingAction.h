/*
 * FeuThingAction.h
 *
 * FeuThingAction is a class for the <action> XML element
 */

#ifndef _FEU_THING_ACTION_H_
#define _FEU_THING_ACTION_H_

#include "FeuThing.h"

class FeuThingAction : public FeuThing {
public:
    FeuThingAction(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingAction();

private:
    FeuCalculable *mWhat; // From the "what" attribute

public:
    float proc(FeuThing *contextThing = NULL); // Run the action handler
    virtual float getAttributeValue(std::string);
    virtual void  setAttributeValue(std::string,float);

};



#endif /* _FEU_THING_ACTION_H_ */
