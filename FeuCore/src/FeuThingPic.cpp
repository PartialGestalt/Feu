/*
 * FeuThingPicPic.cpp
 *
 */

#include "FeuThingPic.h"

#include <list>
#include <utility>

#include "Feu.h"
#include "FeuCalculable.h"
#include "FeuException.h"
#include "FeuLog.h"
#include "FeuThingPath.h"
#include "FeuThingStep.h"
#include "FeuThingAction.h"

FeuThingPic::FeuThingPic(Feu *feu, FeuThingClass *parent, std::string name) :
        FeuThing(feu, name) {
    // Init some of our basics; anything not here is the responsibility of the path or class
    // to initialize (e.g. position and size)
    mFeu = feu;
    mAge = 0.0;
    mAlpha = 1.0;
    mParent = parent;
    mPath = NULL;  // Must be set by parent FeuThingClass.
    mType = "displayable";

    mBack = 0.0;
    mBottom = 0.0;
    mFront = 0.0;
    mTop = 0.0;
    mLeft = 0.0;
    mRight = 0.0;

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
    mValues["left"] = &mLeft;
    mValues["right"] = &mRight;
    mValues["top"] = &mTop;
    mValues["bottom"] = &mBottom;
    mValues["front"] = &mFront;
    mValues["back"] = &mBack;
    mValues["alpha"] = &mAlpha;
    mValues["ordinal"] = &mOrdinal;
    mValues["age"] = &mAge;

    // After creation, the parent FeuThingClass must:
    //   1. Append any class-specific properties (using addProperty())
    //   2. Put the pic onto a path (using setPath())
    //   3. Register the pic with the core.

}

FeuThingPic::~FeuThingPic() {
    std::map<std::string, feuPropInfo *>::iterator i;
    // Deregister
    mFeu->unregisterPic(this);

    // Release our ruleset-defined properties
    for (i = mPropInfo.begin(); i != mPropInfo.end(); i++) {
        FeuThingProperty::releasePropInfo(i->second);
    }

}

void FeuThingPic::runFrame() {
    bool done = false;
    std::list<FeuThing *>::iterator kid;
    FeuThingStep *step;

    // Step 1: If we're not on a path, there's nothing to do.
    if (!mPath)
        return;

    // Step 2: Cycle through all the steps in our current path
    for (kid = mPath->mKids.begin(); kid != mPath->mKids.end() && !done;
            kid++) {
        step = (FeuThingStep *)*kid;
        // CLEAN: TODO: Validate steps on adoption so we don't have to do this....
        if (step->mType != "step")
            continue;
        // If the condition evaluates to false, skip it
        if (step->hasCondition && (step->mCondition->proc(this) == 0.0))
            continue;
        // Select based on type
        switch (step->mStepType) {
            case FEU_STEP_TYPE_MOVE:
                doStep_move(step);
                break;
            case FEU_STEP_TYPE_PLACE:
                doStep_place(step);
                break;
            case FEU_STEP_TYPE_SETPATH:
                doStep_path(step);
                done = true;
                break;
            case FEU_STEP_TYPE_ACTION:
                doStep_action(step);
                break;
            case FEU_STEP_TYPE_DESTROY: {
                // We can't delete here, since the main Feu is walking the list of
                // registered pics.  Instead, put ourselves on the kill list and
                // let them clean up when the frame is finished.
                done = true; // So we don't continue...
                FeuLog::i("Going full Kervorkian\n");
                mFeu->mDeadPics.push_back(this);
                break;
            }
            default:
                // This should never happen, since it's checked on creation ...
                FeuLog::e(
                        "Unknown step type, \"" + step->mAttributes["type"]
                                + "\".\n");
                break;
        }
    }

    // Step 3: update non-step values
    mAge++;

    // Step 4: call out to class-specific renderer
    // Debug: dump the pic
    dump();
}

void FeuThingPic::doStep_path(FeuThingStep *step) {
    FeuThing *newPath;

    // Step 1: lookup new path
    newPath = findGlobalThing(mFeu, step->mAttributes["parameter"]);
    if (!newPath) {
        throw(FeuException("Step error",
                "Invalid path name \"" + step->mAttributes["parameter"]
                        + "\"\n"));
    } else {
        FeuLog::i("Switched displayable \"" + mName + "\" to new path \"" + step->mAttributes["parameter"] + "\".\n");
    }

    // Step 2: Set it up
    mPath = (FeuThingPath *)newPath;
    return;
}

void FeuThingPic::doStep_action(FeuThingStep *step) {
    FeuThingAction *act;

    // Step 1: lookup new path if needed
    if (NULL == step->mAction) {
        act = (FeuThingAction *)findGlobalThing(mFeu, step->mAttributes["parameter"]);
        if (!act) {
            throw(FeuException("Step error",
                    "Invalid action name \"" + step->mAttributes["parameter"]
                            + "\"\n"));
        } else {
            step->mAction = act;
        }
    }
    FeuLog::i(
            "Attempting to execute action \"" + step->mAttributes["parameter"]
                    + "\" from " + mName + "\n");

    // Step 2: Run that sucker, with ourselves as the context
    step->mAction->proc(this);

    return;
}
void FeuThingPic::doStep_move(FeuThingStep *step) {
    double calc;
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
        mLeft = mXpos - mWidth / 2;
        mRight = mLeft + mWidth;
    }
    if (step->hasY) {
        mYpos = step->mY->proc(this);
        mTop = mYpos - mHeight / 2;
        mBottom = mTop + mHeight;
    }
    if (step->hasZ) {
        mZpos = step->mZ->proc(this);
        mFront = mZpos - mDepth / 2;
        mBack = mFront + mDepth;
    }
    return;
}

void FeuThingPic::dump() {
    std::map<std::string, double *>::iterator ifast;
    std::map<std::string, std::string>::iterator islow;

#ifndef DUMP_FULL
    FeuLog::i(
            "FeuThingPic: \"" + mName + ": " + stringof(mWidth) + "x"
                    + stringof(mHeight) + "@("
                    + stringof(mLeft) + "/" + stringof(mXpos) + "/" + stringof(mRight)
                    + ","
                    + stringof(mYpos) + "," + stringof(mZpos) + ")" + "ROT("
                    + stringof(mXrot) + "," + stringof(mYrot) + ","
                    + stringof(mZrot) + ")\n");
#else
    FeuLog::i("FeuThingPic: \"" + mName + "\": ");
    FeuLog::i("\tFast values:\n");
    for (ifast = mValues.begin(); ifast != mValues.end(); ifast++) {
        FeuLog::i("\t\t" + (*ifast).first + " = " + stringof(*((*ifast).second)) + "\n");
    }

    FeuLog::i("\tSlow values:\n");
    for (islow = mAttributes.begin(); islow != mAttributes.end(); islow++) {
        FeuLog::i("\t\t" + (*islow).first + " = " + (*islow).second + "\n");
    }
    FeuLog::i("\n\n");
#endif
}

void FeuThingPic::addProperty(struct feuPropInfo *propInfo) {
    // Step 1: release the old....
    if (mPropInfo.count(*(propInfo->propName))) {
        FeuLog::i(
                "Pic \"" + mName + "\" updating property \""
                        + *(propInfo->propName) + "\" with initial value of "
                        + stringof(propInfo->propValue) + "\n");
        FeuThingProperty::releasePropInfo(mPropInfo[*(propInfo->propName)]);
    } else {
        FeuLog::i(
                "Pic \"" + mName + "\" adding property \""
                        + *(propInfo->propName) + "\" with initial value of "
                        + stringof(propInfo->propValue) + "\n");
    }

    // Step 2: Add the new to the list
    mPropInfo[*(propInfo->propName)] = propInfo;

    // Step 3: Register into our fast array
    mValues[*(propInfo->propName)] = &(propInfo->propValue);
}

void FeuThingPic::addProperties(FeuThing *propThing) {
    std::list<FeuThingProperty *>::iterator i;
    // Inherit all properties from the given thing....
    for (i = propThing->mProperties.begin(); i != propThing->mProperties.end();
            i++) {
        struct feuPropInfo *newInfo;

        newInfo = (*i)->getPropInfo(this);
        if (!newInfo) {
            FeuLog::i("PropInfo load fail.\n");
        }
        addProperty(newInfo);
    }
}
