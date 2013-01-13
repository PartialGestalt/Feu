/*
 * FeuThing.h
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 *
 * FeuThing is a base class for most of our other objects, and
 * is a codewise representation of an XML element.  It can have
 * generic attributes in the attributes map, and can have
 * a list of children.
 *
 * Subclasses will have precalc or shortcut members.
 */

#ifndef FEUTHING_H_
#define FEUTHING_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include <tinyxml.h>
#include "FeuSpecifier.h"
#include "FeuThing.h"

class FeuThing {
public:
	FeuThing(std::string name);
    FeuThing(TiXmlElement *, FeuThing *parent = NULL);
	virtual ~FeuThing();

protected:
	FeuThing *mParent;
    std::string mType; // object class name (element type)
    std::map<std::string,std::string> mAttributes; // Raw attributes from XML
    std::list<FeuThing *> mKids; // Child XML element things

public:
    std::string mName; // My own special name

public:
	void adopt(FeuThing *ft_kid);
	void geneology();

public:
    static FeuThing *findThing(FeuThing *context, FeuSpecifier *objectSpecifier);
    static FeuThing *findGlobalThing(FeuThing *context, FeuSpecifier *objectSpecifier);
    virtual float getAttributeValue(std::string);
    virtual void setAttributeValue(std::string,float value);

};



#endif /* FEUTHING_H_ */
