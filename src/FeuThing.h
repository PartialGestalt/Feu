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
#include <tinyxml.h>

using namespace std;

class FeuThing {
public:
	FeuThing(string name);
    FeuThing(TiXmlElement *, FeuThing *parent = NULL);
	virtual ~FeuThing();

protected:
	FeuThing *mParent;
	string mType; // object class name (element type)
	map<string,string> mAttributes; // Raw attributes from XML
	list<FeuThing *> mKids; // Child XML element things

public:
	string mName; // My own special name

public:
	void adopt(FeuThing *ft_kid);
	void geneology();

};



#endif /* FEUTHING_H_ */
