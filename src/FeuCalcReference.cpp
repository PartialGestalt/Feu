/*
 * FeuCalcReference.cpp
 */

#include "feu.h"

FeuCalcReference::FeuCalcReference(string initVal) {
    // CLEAN: TODO: Lookup thing from name
    mAttribute = initVal;
    mValue = 0.0;
}

FeuCalcReference::FeuCalcReference(FeuThing *thing, string attr) {
    mThing = thing;
    mAttribute = attr;
    mValue = 0.0;
}

void FeuCalcReference::proc(FeuStack *calcStack) {
    // For processing, we simply push onto the calculator stack
    calcStack->push(this);
}

FeuCalcItem *FeuCalcReference::copy() {
    FeuCalcReference *fcr = new FeuCalcReference(mThing,mAttribute);
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

string FeuCalcReference::toString() {
    return mAttribute;
}
