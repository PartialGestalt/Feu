/*
 * FeuThingPicPic.cpp
 *
 */

#include "feu_all.h"

FeuThingPic::FeuThingPic(Feu *feu, FeuThingClass *parent, std::string name) : FeuThing(feu, name) {
    // Init some of our basics; anything not here is the responsibility of the path or class
    // to initialize (e.g. position and size)
    mFeu = feu;
    mAge = 0.0;
    mAlpha = 1.0;
    mParent = parent;
    mPath = NULL;  // Must be set by parent FeuThingClass.
    mType = "displayable";

    // Setup our fast access map
    mValues["x"] = &mXpos;
    mValues["y"] = &mYpos;
    mValues["z"] = &mZpos;
    mValues["rx"] = &mXrot;
    mValues["ry"] = &mYrot;
    mValues["rz"] = &mZrot;
    mValues["width"] = &mWidth;
    mValues["height"] = &mHeight;
    mValues["depth"] = &mDepth;
    mValues["alpha"] = &mAlpha;
    mValues["ordinal"] = &mOrdinal;
    mValues["age"] = &mAge;


    // After creation, the parent FeuThingClass must:
    //   1. Append any class-specific properties (using addProperty())
    //   2. Put the pic onto a path (using setPath())
    //   3. Register the pic with the core.

}

FeuThingPic::~FeuThingPic() {
    // Deregister 
    mFeu->unregisterPic(this);
}

void FeuThingPic::runFrame() {
    bool done = false;
    std::list<FeuThing *>::iterator kid;
    FeuThingStep *step;

    // Step 1: If we're not on a path, there's nothing to do.
    if (!mPath) return;

    // Step 2: Cycle through all the steps in our current path
    for (kid = mPath->mKids.begin(); kid != mPath->mKids.end() && !done; kid++) {
        step = (FeuThingStep *)*kid;
        // CLEAN: TODO: Validate steps on adoption so we don't have to do this....
        if (step->mType != "step") continue;
        // If the condition evaluates to false, skip it 
        if (step->hasCondition && (step->mCondition->proc(this) == 0.0)) continue;
        // Select based on type 
        switch (step->mStepType) {
            case FEU_STEP_TYPE_MOVE:  doStep_move(step); break;
            case FEU_STEP_TYPE_PLACE: doStep_place(step); break;
            case FEU_STEP_TYPE_PATH:  doStep_path(step); done=true; break;
            default:
                // This should never happen, since it's checked on creation ...
                FeuLog::e("Unknown step type, \"" + step->mAttributes["type"] + "\".\n");
                break;
        }
    }

    // Step 3: update non-step values
    mAge++;

    // Debug: dump the pic
    dump();
}

void FeuThingPic::doStep_path(FeuThingStep *step) {
    FeuThing *newPath;

    // Step 1: lookup new path
    newPath = findGlobalThing(mFeu,step->mAttributes["option"]);
    if (!newPath) {
        throw (new FeuException("Step error","Invalid path name \"" + step->mAttributes["option"] + "\"\n"));
    } else {
        FeuLog::i("Switched displayable \"" + mName + "\" to new path \"" + step->mAttributes["option"] + "\".\n");
    }
    
    // Step 2: Set it up
    mPath = (FeuThingPath *)newPath;
    return;
}

void FeuThingPic::doStep_move(FeuThingStep *step) {
    float calc;
    // For move, simply additively apply any calculables
    // (and derived values!)
    if (step->hasX) {
        calc = step->mX->proc(this);
        mXpos += calc;
        mLeft += calc;
        mRight += calc;
    }
    if (step->hasY) {
        calc = step->mY->proc(this);
        mYpos += calc;
        mBottom += calc;
        mTop += calc;
    }
    if (step->hasZ) {
        calc = step->mZ->proc(this);
        mZpos += calc;
        mFront += calc;
        mBack += calc;
    }
    return;
}

void FeuThingPic::doStep_place(FeuThingStep *step) {
    // For explicit place, just set positions
    if (step->hasX) {
        mXpos = step->mX->proc(this);
        mLeft = mXpos - mWidth/2;
        mRight = mLeft + mWidth;
    }
    if (step->hasY) {
        mYpos = step->mY->proc(this);
        mTop = mYpos - mHeight/2;
        mBottom = mTop + mHeight;
    }
    if (step->hasZ) {
        mZpos = step->mZ->proc(this);
        mFront = mZpos - mDepth/2;
        mBack = mFront + mDepth;
    }
    return;
}

void FeuThingPic::dump() {
    std::map<std::string,float *>::iterator ifast;
    std::map<std::string,std::string>::iterator islow;

    FeuLog::i("FeuThingPic: \"" + mName + "\"\n");
    FeuLog::i("\tFast values:\n");
    for (ifast = mValues.begin(); ifast != mValues.end(); ifast++) {
        FeuLog::i("\t\t" + (*ifast).first + " = " + stringof(*((*ifast).second)) + "\n");
    }

    FeuLog::i("\tSlow values:\n");
    for (islow = mAttributes.begin(); islow != mAttributes.end(); islow++) {
        FeuLog::i("\t\t" + (*islow).first + " = " + (*islow).second + "\n");
    }
    FeuLog::i("\n\n");
}
