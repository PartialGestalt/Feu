/*
 * FeuCalcNumber.cpp
 */

#include "feu.h"

FeuCalcNumber::FeuCalcNumber(float initVal) {
    mValue = initVal;
    //FeuLog::i("CONSTRUCT: FeuCalcNumber()\n");
}

FeuCalcNumber::FeuCalcNumber(string initVal) {
    mValue = floatof(initVal);
    //FeuLog::i("CONSTRUCT: FeuCalcNumber()\n");
}

void FeuCalcNumber::proc(FeuStack *calcStack) {
    // For processing, we simply push onto the calculator stack
    calcStack->push(this);
    FeuLog::i("Pushed NUM onto calcstack, depth is now: " + stringof(calcStack->size()) + "\n");
}

FeuCalcItem *FeuCalcNumber::copy() {
    FeuCalcNumber *fcn = new FeuCalcNumber(mValue);
    return (FeuCalcItem *)fcn;
}

float FeuCalcNumber::getValue() {
    return mValue;
}

void FeuCalcNumber::setValue(float newVal) {
    mValue = newVal;
}

string FeuCalcNumber::toString() {
    return stringof(mValue);
}
