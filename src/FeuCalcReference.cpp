/*
 * FeuCalcReference.cpp
 */

#include "feu_all.h"

FeuCalcReference::FeuCalcReference(std::string initVal, FeuThing *contextThing) : mSpecifier(initVal) {
    // "contextThing", if given, is the object we will belong to, which defines 
    // the scope and context.  "mThing" is the object whose value we will use during
    // calculations.
    mInitial = initVal;
        // If the reference is a global, this resolves now; if the reference
        // is local, it won't resolve yet.
    mThing = FeuThing::findGlobalThing(contextThing,&mSpecifier);
    mAttribute = mSpecifier.mAttribute;
        // If we've resolved a reference, go ahead and extract the current
        // value.
    mValue = mThing?mThing->getAttributeValue(mAttribute):0.0;
    return;
}

int FeuCalcReference::proc(FeuStack *calcStack) {
    // For processing, we simply push onto the calculator stack
    calcStack->push(this);
    return 0;
}

FeuCalcItem *FeuCalcReference::copy() {
    return new FeuCalcReference(mInitial,mThing);
}

float FeuCalcReference::getValue() {
    // CLEAN: TODO: Do this for real
    return 0.0;
}

void FeuCalcReference::setValue(float newVal) {
    // CLEAN: TODO: Do this for real
    mValue = newVal;
}

std::string FeuCalcReference::toString() {
    return mInitial;
}
