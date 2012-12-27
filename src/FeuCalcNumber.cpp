/*
 * FeuCalcNumber.cpp
 */

#include "feu.h"

FeuCalcNumber::FeuCalcNumber(float initVal) {
    mValue = initVal;
}

void FeuCalcNumber::proc(stack<FeuCalcItem *> calcStack) {
    // For processing, we simply push onto the calculator stack
    calcStack.push(this);
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
