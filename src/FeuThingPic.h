/*
 * FeuThingPic.h
 *
 * FeuThingPic is the fundamental thing that can be displayed.
 * It may or may not actually be a picture, but it will be 
 * displayable.
 */

#ifndef _FEU_THING_PIC_H_
#define _FEU_THING_PIC_H_

class FeuPicData;

class FeuThingPic : public FeuThing {
public:
    FeuThingPic(Feu *feu, FeuThingClass *parent, std::string name);
	~FeuThingPic();

public:
    //  Well-known properties
    //    Member        Property  Description
    //------------------------------------------
    float mXpos;     // "x"       X coordinate of center of gravity
    float mYpos;     // "y"       Y coordinate of center of gravity
    float mZpos;     // "z"       Z coordinate of center of gravity
    float mXrot;     // "rx"      Rotational offset about X axis
    float mYrot;     // "ry"      Rotational offset about Y axis
    float mZrot;     // "rz"      Rotational offset about Z axis
    float mWidth;    // "width"   Width of pic, in FEUs
    float mHeight;   // "height"  Height of pic, in FEUs
    float mDepth;    // "depth"   Depth of pic, in FEUs
    float mAlpha;    // "alpha"   Opacity of pic (0.0=invisible, 1.0=opaque)
    float mAge;      // "age"     Age of this pic, in frames
    float mOrdinal;  // "ordinal" Ordinal number of creation in class

    // Constructed properties
    float mLeft;     //  "left"    X coordinate of leftmost part of pic
    float mRight;    //  "right"   X coordinate of rightmost part of pic
    float mTop;      //  "top"     Y coordinate of topmost part of pic
    float mBottom;   //  "bottom"  Y coordinate of bottommost part of pic
    float mFront;    //  "front"   Z coordinate of frontmost part of pic
    float mBack;     //  "back"    Z coordinate of backmost part of pic

    FeuThingClass *mParent;  // Class from whence we came...
    FeuThingPath *mPath;     // The path we're currently on.
    FeuPicData *mData;       // Class-specific container

private:
    // Note that the base FeuThing object has a member called 'mProperties' that is
    // the list of XML "property" children elements.
    std::map<std::string, feuPropInfo *>mPropInfo; // Additional properties from ruleset

private:  // Step types.
    void dump();
    void doStep_move(FeuThingStep *step);
    void doStep_place(FeuThingStep *step);
    void doStep_path(FeuThingStep *step);

public:
    void runFrame();
    void addProperties(FeuThing *propThing);
    void addProperty(feuPropInfo *propInfo);

};



#endif /* _FEU_THING_PIC_H_ */
