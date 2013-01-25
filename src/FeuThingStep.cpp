/*
 * FeuThingStep.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: akephart
 */

#include "feu_all.h"
#include <tinyxml.h>

FeuThingStep::FeuThingStep(Feu *feu, TiXmlElement *ele, FeuThing *parent) : FeuThing(feu,ele,parent) {
    std::string stype;
    // Init booleans
    hasCondition = hasX = hasY = hasZ = false;

    // Step type  (unspecified means "move")
    if (!mAttributes.count("type")) {
        stype = "move";
        mStepType = FEU_STEP_TYPE_MOVE;
    } else {
        stype = mAttributes["type"];
             if (stype == "move") mStepType = FEU_STEP_TYPE_MOVE;
        else if (stype == "place") mStepType = FEU_STEP_TYPE_PLACE;
        //else if (stype == "rotate") mStepType = FEU_STEP_TYPE_ROTATE;
        //else if (stype == "orient") mStepType = FEU_STEP_TYPE_ORIENT;
        //else if (stype == "size") mStepType = FEU_STEP_TYPE_SIZE;
        //else if (stype == "scale") mStepType = FEU_STEP_TYPE_SCALE;
        else if (stype == "path") mStepType = FEU_STEP_TYPE_PATH;
        //else if (stype == "destroy") mStepType = FEU_STEP_TYPE_DESTROY;
        else {
            FeuLog::e("Unknown step type, \"" + stype + "\" in step at line " + stringof(ele->Row()) + "\n");
            mStepType = FEU_STEP_TYPE_MAX;
        }
    }

    // Create calculables from attributes 
    if (mAttributes.count("condition"))  {
        mCondition = new FeuCalculable(feu,mAttributes["condition"],this);
        hasCondition = true;
    }
    if (mAttributes.count("x"))  {
        mX = new FeuCalculable(feu,mAttributes["x"],this);
        hasX = true;
    }
    if (mAttributes.count("y"))  {
        mY = new FeuCalculable(feu,mAttributes["y"],this);
        hasY = true;
    }
    if (mAttributes.count("z"))  {
        mZ = new FeuCalculable(feu,mAttributes["z"],this);
        hasZ = true;
    }
}

FeuThingStep::~FeuThingStep() {
    if (hasZ) delete mZ;
    if (hasY) delete mY;
    if (hasX) delete mX;
    if (hasCondition) delete mCondition;
}

