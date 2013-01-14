/*
 * Feu.h
 *
 * Feu handles the loading of a ruleset file into
 * our specific objects.
 */

#ifndef FEU_H_
#define FEU_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include "tinyxml.h"

class Feu {
public:
	Feu(std::string filename);
	~Feu();

private:
    TiXmlDocument *mDoc;
    FeuThing *mRoot;

private:
    void parseRuleset();

public:
    static FeuThing *convertElement(TiXmlElement *ele);
};



#endif /* FEU_H_ */
