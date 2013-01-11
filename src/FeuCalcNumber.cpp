/*
 * FeuCalcNumber.cpp
 */

#include "feu.h"

FeuCalcNumber::FeuCalcNumber(float initVal) {
    mValue = initVal;
}

FeuCalcNumber::FeuCalcNumber(int initVal) {
    mValue = (float)initVal;
}

FeuCalcNumber::FeuCalcNumber(std::string initVal) {
    if (std::string::npos != initVal.find_first_of('.')) {
        // If the string contains a decimal point, it must be decimal float...
        //FeuLog::i("FeuCalcNumber(): Forced decimal for \""+initVal+"\".\n");
        mValue = floatof(initVal);
    } else if ((initVal[0] == '#')|| (initVal[0] == '0')) {
        // If the string may have a non-decimal radix, try to convert as integer first...
        //FeuLog::i("FeuCalcNumber(): Trying intof for \""+initVal+"\".\n");
        mValue = (float)intof(initVal);
    } else {
        // Punt.
        //FeuLog::i("FeuCalcNumber(): Trying floatof for \""+initVal+"\".\n");
        mValue = floatof(initVal);
    }
}

int FeuCalcNumber::proc(FeuStack *calcStack) {
    // For processing, we simply push onto the calculator stack
    calcStack->push(this);
    //FeuLog::i("Pushed NUM onto calcstack, depth is now: " + stringof(calcStack->size()) + "\n");
    return 0;
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

std::string FeuCalcNumber::toString() {
    return stringof(mValue);
}
