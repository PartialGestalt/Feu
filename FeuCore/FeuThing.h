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

#include <tinyxml.h>
#include <list>
#include <map>
#include <string>
#include <vector>

class FeuThingAction;
class FeuThingProperty;
class FeuSpecifier;

class FeuThing;

#include "Feu.h"

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
    double (*func)(FeuThing *contextThing, std::vector<double>*argv); // Implementor
};

class FeuThing {
public:
	FeuThing(Feu *f, std::string name);
    FeuThing(Feu *f, TiXmlElement *t, FeuThing *parent = NULL);
	virtual ~FeuThing();

public:
    Feu *mFeu;  // The main document
	FeuThing *mParent;
    std::string mType; // object class name (element type)
    std::map<std::string,std::string> mAttributes; // Raw string attributes from XML
    std::map<std::string,double *>mValues; // Fast-access values
    std::list<FeuThing *> mKids; // Child XML element things
    std::string mName; // My own special name
    std::map<std::string,std::list<FeuThingAction *> > mActions; // Actions, indexed by "what"
    std::map<std::string,struct feuMethod *> mMethods; // Methods supported by this FeuThing
    std::list<FeuThingProperty *>mProperties;  // List of child property objects

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
    void addProperty(FeuThingProperty *);
    bool hasAttribute(std::string);
    bool hasMethod(std::string);
    virtual double getAttributeValue(std::string);
    virtual void setAttributeValue(std::string,double value);
};



#endif /* _FEU_THING_H_ */
