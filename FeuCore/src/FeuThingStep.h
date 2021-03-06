/*
 * FeuThingStep.h
 *
 * FeuThingStep is a class for the <step> XML element
 */

#ifndef _FEU_THING_STEP_H_
#define _FEU_THING_STEP_H_

#include "FeuThing.h"

class Feu;
class FeuCalculable;
class FeuThingPath;
class TiXmlElement;


enum FEU_STEP_TYPE {
    FEU_STEP_TYPE_MOVE = 0, // Relative motion
    FEU_STEP_TYPE_PLACE,    // Absolute positioning
    FEU_STEP_TYPE_ROTATE,   // Relative rotation
    FEU_STEP_TYPE_ORIENT,   // Absolution rotational setting
    FEU_STEP_TYPE_SIZE,     // Resize the object
    FEU_STEP_TYPE_SCALE,    // Scale the object
    FEU_STEP_TYPE_SETPATH,  // Change the object's path
    FEU_STEP_TYPE_ACTION,   // Execute a named action
    FEU_STEP_TYPE_DESTROY,  // Destroy ourselves
    FEU_STEP_TYPE_MAX  // Mark the end of the list
};


class FeuThingStep : public FeuThing {
public:
    FeuThingStep(Feu *feu, TiXmlElement *, FeuThing *parent);
	~FeuThingStep();

public:
    // Type
    int            mStepType;  // What kind of step are we?
    // Common values
    bool         hasCondition; // User specified a condition?
    FeuCalculable *mCondition; // From the "condition" attribute
    bool         hasX; // User specify an "X" attribute?
    FeuCalculable *mX;
    bool         hasY; // User specify an "X" attribute?
    FeuCalculable *mY;
    bool         hasZ; // User specify an "X" attribute?
    FeuCalculable *mZ;
    // Specials
    FeuThingPath  *mPath; // If we're a "setpath" type.
    FeuThingAction *mAction; // If we're an "action" type.
};



#endif /* _FEU_THING_STEP_H_ */
