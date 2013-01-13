/*
 * FeuRuleset.h
 *
 * FeuRuleset handles the loading of a ruleset file into
 * our specific objects.
 */

#ifndef FEURULESET_H_
#define FEURULESET_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include "tinyxml.h"

class FeuRuleset {
public:
	FeuRuleset(std::string filename);
	~FeuRuleset();

private:
    TiXmlDocument *mDoc;
    FeuThing *mRoot;

private:
    void parseRuleset();

public:
    static FeuThing *convertElement(TiXmlElement *ele);
};



#endif /* FEURULESET_H_ */
