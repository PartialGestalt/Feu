/*
 * FeuCalcNumber.cpp
 */

#include "FeuCalcNumber.h"

#include <string>

#include "FeuCalculable.h"
#include "FeuLog.h"
#include "FeuStack.h"

FeuCalcNumber::FeuCalcNumber(FeuCalculable *calc, double initVal) : FeuCalcItem(calc)  {
    mValue = initVal;
}

FeuCalcNumber::FeuCalcNumber(FeuCalculable *calc, int initVal) : FeuCalcItem(calc)  {
    mValue = (double)initVal;
}

FeuCalcNumber::FeuCalcNumber(FeuCalculable *calc, std::string initVal) : FeuCalcItem(calc)  {
    if (std::string::npos != initVal.find_first_of('.')) {
        // If the string contains a decimal point, it must be decimal double...
        //FeuLog::i("FeuCalcNumber(): Forced decimal for \""+initVal+"\".\n");
        mValue = doubleof(initVal);
    } else if ((initVal[0] == '#')|| (initVal[0] == '0')) {
        // If the string may have a non-decimal radix, try to convert as integer first...
        //FeuLog::i("FeuCalcNumber(): Trying intof for \""+initVal+"\".\n");
        mValue = (double)intof(initVal);
    } else {
        // Punt.
        //FeuLog::i("FeuCalcNumber(): Trying doubleof for \""+initVal+"\".\n");
        mValue = doubleof(initVal);
    }
}

int FeuCalcNumber::proc(FeuStack *calcStack) {
    // For processing, we simply push onto the calculator stack
    calcStack->push(this);
    return 0;
}

FeuCalcItem *FeuCalcNumber::copy() {
    FeuCalcNumber *fcn = new FeuCalcNumber(mCalculable, mValue);
    return (FeuCalcItem *)fcn;
}

double FeuCalcNumber::getValue() {
    return mValue;
}

void FeuCalcNumber::setValue(double newVal) {
    mValue = newVal;
}

std::string FeuCalcNumber::toString() {
    return stringof(mValue);
}
