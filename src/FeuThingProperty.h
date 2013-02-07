/*
 * FeuThingProperty.h
 *
 * FeuThingProperty is a class for the <action> XML element
 */

#ifndef _FEU_THING_PROPERTY_H_
#define _FEU_THING_PROPERTY_H_

#include "FeuThing.h"

class FeuThingProperty;

/* Structure used in pic addenda */
struct feuPropInfo {
    FeuThingProperty *propHost; // From whence we came
    std::string *propName;      // Simple name
    float        propValue;       // Collapsed value
};

class FeuThingProperty : public FeuThing {
public:
    FeuThingProperty(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingProperty();

private:
    FeuCalculable *mPropCalc; // From the "value" attribute, the initial value

public:
    struct feuPropInfo *getPropInfo(FeuThing *contextThing);
    static void     releasePropInfo(struct feuPropInfo *);


};



#endif /* _FEU_THING_PROPERTY_H_ */
