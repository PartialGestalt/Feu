/*
 * FeuThingPic.h
 *
 * FeuThingPic is the fundamental thing that can be displayed.
 * It may or may not actually be a picture, but it will be
 * displayable.
 */

#ifndef _FEU_THING_PIC_H_
#define _FEU_THING_PIC_H_

#include <map>
#include <string>

#include "FeuThingProperty.h"

class FeuThingClass;
class FeuThingPath;
class FeuThingStep;

class FeuThingPic : public FeuThing {
public:
    FeuThingPic(Feu *feu, FeuThingClass *parent, std::string name);
	~FeuThingPic();

public:
    //  Well-known properties
    //    Member        Property  Description
    //------------------------------------------
    double mXpos;     // "x"       X coordinate of center of gravity
    double mYpos;     // "y"       Y coordinate of center of gravity
    double mZpos;     // "z"       Z coordinate of center of gravity
    double mXrot;     // "rx"      Rotational offset about X axis
    double mYrot;     // "ry"      Rotational offset about Y axis
    double mZrot;     // "rz"      Rotational offset about Z axis
    double mWidth;    // "width"   Width of pic, in FEUs
    double mHeight;   // "height"  Height of pic, in FEUs
    double mDepth;    // "depth"   Depth of pic, in FEUs
    double mAlpha;    // "alpha"   Opacity of pic (0.0=invisible, 1.0=opaque)
    double mAge;      // "age"     Age of this pic, in frames
    double mOrdinal;  // "ordinal" Ordinal number of creation in class

    // Constructed properties
    double mLeft;     //  "left"    X coordinate of leftmost part of pic
    double mRight;    //  "right"   X coordinate of rightmost part of pic
    double mTop;      //  "top"     Y coordinate of topmost part of pic
    double mBottom;   //  "bottom"  Y coordinate of bottommost part of pic
    double mFront;    //  "front"   Z coordinate of frontmost part of pic
    double mBack;     //  "back"    Z coordinate of backmost part of pic

    FeuThingClass *mParent;  // Class from whence we came...
    FeuThingPath *mPath;     // The path we're currently on.
    //FeuPicData *mData;       // Class-specific container

private:
    // Note that the base FeuThing object has a member called 'mProperties' that is
    // the list of XML "property" children elements; this is our container for fast-access
    // properties at runtime.
    std::map<std::string, feuPropInfo *>mPropInfo; // Additional properties from ruleset

private:  // Step types.
    void dump();
    void doStep_move(FeuThingStep *step);
    void doStep_place(FeuThingStep *step);
    void doStep_path(FeuThingStep *step);
    void doStep_action(FeuThingStep *step);

public:
    void runFrame();
    void addProperties(FeuThing *propThing);
    void addProperty(feuPropInfo *propInfo);

};



#endif /* _FEU_THING_PIC_H_ */
