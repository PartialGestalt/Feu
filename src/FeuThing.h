/*
 * FeuThing.h
 *
 * FeuThing is a base class for most of our other objects, and
 * is a codewise representation of an XML element.  It can have
 * generic attributes in the attributes map, and can have
 * a list of children.
 *
 * Subclasses will have precalc or shortcut members.
 */

#ifndef _FEU_THING_H_
#define _FEU_THING_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include <tinyxml.h>
#include "Feu.h"
#include "FeuSpecifier.h"

class FeuThingAction;
class FeuThing;


#define FEU_THING_DEFAULT_ATTR(__name,__value) \
do { \
    if (!mAttributes.count(__name)) { \
        mAttributes[__name] = __value; \
    } \
} while (0)

struct feuMethod {
    std::string name;  // Name of the method
    bool isReturning;  // Does method return a value?
    int argCount;      // Expected # of args
    float (*func)(FeuThing *contextThing, std::vector<float>*argv); // Implementor
};

class FeuThing {
public:
	FeuThing(Feu *, std::string name);
    FeuThing(Feu *, TiXmlElement *, FeuThing *parent = NULL);
	virtual ~FeuThing();

public:
    Feu *mFeu;  // The main document
	FeuThing *mParent;
    std::string mType; // object class name (element type)
    std::map<std::string,std::string> mAttributes; // Raw attributes from XML
    std::list<FeuThing *> mKids; // Child XML element things
    std::string mName; // My own special name
    std::map<std::string,std::list<FeuThingAction *> > mActions; // Actions, indexed by "what"
    std::map<std::string,struct feuMethod *> mMethods; // Methods supported by this FeuThing

public:
	void adopt(FeuThing *ft_kid);
	void adopt_front(FeuThing *ft_kid);
	void geneology();
    std::list<FeuThing *>::iterator firstChild();
    std::list<FeuThing *>::iterator endChild();

public:
    static FeuThing *findThing(Feu *, FeuThing *context, FeuSpecifier *objectSpecifier);
    static FeuThing *findGlobalThing(Feu *, FeuSpecifier *objectSpecifier);
    static FeuThing *findGlobalThing(Feu *, std::string objectName);
    void addAction(std::string, FeuThingAction *);
    bool hasAttribute(std::string);
    bool hasMethod(std::string);
    virtual float getAttributeValue(std::string);
    virtual void setAttributeValue(std::string,float value);
};



#endif /* _FEU_THING_H_ */
