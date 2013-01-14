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

class FeuThing;
class FeuThingScreen;

class Feu {
public:
	Feu(std::string filename);
	~Feu();

private:
    TiXmlDocument *mDoc;
    FeuThing *mRoot;
    FeuThingScreen *mScreen;

public:
    // Utilities
    static FeuThing *convertElement(Feu *feu,TiXmlElement *ele);
    FeuThing *getRoot();

public:
    // Action handlers
    void onLoad();
    void onActivate();
    void onFrame();
};



#endif /* FEU_H_ */
