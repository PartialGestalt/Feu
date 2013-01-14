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
class FeuThingPath;

class Feu {
public:
	Feu(std::string filename);
	~Feu();

public:
    std::string mFilename;

private:
    TiXmlDocument *mDoc;
    FeuThing *mRoot;
    FeuThingScreen *mScreen;
    //std::list<FeuThingClass *>mClasses; // Classes
    //std::list<FeuThingPath *>mPaths; // Toplevel paths
    //std::list<FeuThingParameter *>mParameters; // Toplevel parameters

public:
    // Utilities
    static FeuThing *convertElement(Feu *feu,TiXmlElement *ele, FeuThing *parent);
    FeuThing *getRoot();

public:
    // Action handlers
    void runEvent(std::string); // Handle an event
    void run(); // Run once
};



#endif /* FEU_H_ */
