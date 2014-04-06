/*
 * Feu.h
 *
 * Feu handles the loading of a ruleset file into
 * our specific objects.
 */

#ifndef _FEU_H_
#define _FEU_H_

#include <tinyxml.h>
#include <list>
#include <string>


class FeuThing;
class FeuThingScreen;

class FeuThingRandom;
class FeuCalculable;
class FeuThingPic;
class FeuThingProperty;
class FeuThingSettings;

class Feu {
public:
	Feu(std::string filename);
	~Feu();

private:
	FeuThing *mRoot;
	TiXmlDocument *mDoc;
    std::list<FeuCalculable *>mCalculables; // For deferred resolution
    std::list<FeuThingPic *>mPics; // The list of live displayables
    std::list<FeuThingProperty *>mProperties; // Global per-pic properties

public:
    std::string mFilename;
    std::list<FeuThingPic *>mDeadPics; // Pics that are self-destructing
    FeuThingRandom *mRandom;
    FeuThingScreen *mScreen;
    FeuThingSettings *mSettings;


public:
    // Utilities
    static FeuThing *convertElement(Feu *feu,TiXmlElement *ele, FeuThing *parent);
    FeuThing *getRoot();
    void registerCalculable(FeuCalculable *);
    int registerPic(FeuThingPic *);
    int unregisterPic(FeuThingPic *);
    void setSetting(std::string,double);

public:
    // Action handlers
    void runTimers(); // Check for and run any timers that have expired
    void runEvent(std::string); // Handle an event
    void run(); // Run one frame
};



#endif /* _FEU_H_ */
