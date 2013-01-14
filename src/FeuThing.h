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
#include "Feu.h"
#include "FeuSpecifier.h"

class FeuThing {
public:
	FeuThing(Feu *, std::string name);
    FeuThing(Feu *, TiXmlElement *, FeuThing *parent = NULL);
	virtual ~FeuThing();

protected:
    Feu *mFeu;  // The main document
	FeuThing *mParent;
    std::string mType; // object class name (element type)
    std::map<std::string,std::string> mAttributes; // Raw attributes from XML
    std::list<FeuThing *> mKids; // Child XML element things

public:
    std::string mName; // My own special name

public:
	void adopt(FeuThing *ft_kid);
	void adopt_front(FeuThing *ft_kid);
	void geneology();
    std::list<FeuThing *>::iterator firstChild();
    std::list<FeuThing *>::iterator endChild();

public:
    static FeuThing *findThing(Feu *, FeuThing *context, FeuSpecifier *objectSpecifier);
    static FeuThing *findGlobalThing(Feu *, FeuSpecifier *objectSpecifier);
    virtual float getAttributeValue(std::string);
    virtual void setAttributeValue(std::string,float value);

};



#endif /* FEUTHING_H_ */
