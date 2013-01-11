/*
 * FeuXML.h
 *
 * FeuXML handles the loading of a ruleset file into
 * our specific objects.
 */

#ifndef FEUXML_H_
#define FEUXML_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include "tinyxml.h"

using namespace std;

class FeuXML {
public:
	FeuXML(string filename);
	~FeuXML();

private:
    TiXmlDocument *mDoc;
    FeuThing *mRoot;

private:
    void parseRuleset();

public:
    static FeuThing *convertElement(TiXmlElement *ele);
};



#endif /* FEUXML_H_ */
