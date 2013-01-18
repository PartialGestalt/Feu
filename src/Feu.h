/*
 * Feu.h
 *
 * Feu handles the loading of a ruleset file into
 * our specific objects.
 */

#ifndef _FEU_H_
#define _FEU_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include "tinyxml.h"

class FeuThing;
class FeuThingScreen;
class FeuThingRandom;
class FeuThingPath;
class FeuCalculable;
class FeuThingPic;

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
    FeuThingRandom *mRandom;
    std::list<FeuCalculable *>mCalculables; // For deferred resolution
    std::list<FeuThingPic *>mPics; // The list of live displayables

public:
    // Utilities
    static FeuThing *convertElement(Feu *feu,TiXmlElement *ele, FeuThing *parent);
    FeuThing *getRoot();
    void registerCalculable(FeuCalculable *);
    int registerPic(FeuThingPic *);
    int unregisterPic(FeuThingPic *);

public:
    // Action handlers
    void runEvent(std::string); // Handle an event
    void run(); // Run once
};



#endif /* _FEU_H_ */
