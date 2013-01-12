/*
 * FeuCalcReference.cpp
 */

#include "feu.h"

FeuCalcReference::FeuCalcReference() {
    mThing = NULL;
    mValue = 0.0;
    return;
}

FeuCalcReference::FeuCalcReference(std::string initVal, FeuThing *contextThing) {
    // "contextThing" is the object we will belong to, which defines the scope
    // and context.  "mThing" is the object whose value we will use during
    // calculations.
    FeuSpecifier fs = FeuSpecifier(initVal);
    mThing = FeuThing::findThing(contextThing,&fs);
    mAttribute = fs.mAttribute;
    mValue = mThing?mThing->getAttributeValue(mAttribute):0.0;
    return;
}

int FeuCalcReference::proc(FeuStack *calcStack) {
    // For processing, we simply push onto the calculator stack
    calcStack->push(this);
    return 0;
}

FeuCalcItem *FeuCalcReference::copy() {
    FeuCalcReference *fcr = new FeuCalcReference();

    fcr->mValue = mValue;
    fcr->mThing = mThing;
    fcr->mAttribute = mAttribute;
    return (FeuCalcItem *)fcr;
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
    return mAttribute;
}
