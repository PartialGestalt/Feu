/*
 * FeuCalcOperator.cpp
 */

#include "feu.h"

FeuCalcOperator::FeuCalcOperator(string initVal) {
    map<string,int>::iterator i = feuOperators.find(initVal);
    if (i == feuOperators.end()) {
        // CLEAN: TODO: Throw an exception here.
        mInfo = &feuOpInfoTable[FEU_OP_ID_FAILURE];
    } else {
        mInfo = &feuOpInfoTable[i->second]; 
    }
}

void FeuCalcOperator::proc(stack<FeuCalcItem *> *calcStack) {
    if (NULL != mInfo->func) (mInfo->func)(calcStack);
    else FeuLog::w("No function to implement operator \"",mInfo->op,"\"\n");
    FeuLog::i("Finished Op on calcstack; depth is now: " + stringof(calcStack->size()) + "\n");
    return;
}

FeuCalcItem *FeuCalcOperator::copy() {
    FeuCalcOperator *fco = new FeuCalcOperator(mInfo->op);
    return (FeuCalcItem *)fco;
}

float FeuCalcOperator::getValue() {
    // CLEAN: TODO: Throw an exception here.
    return 0.0;
}

void FeuCalcOperator::setValue(float newVal) {
    // CLEAN: TODO: Throw an exception here.
    return;
}

int FeuCalcOperator::getID() {
    return mInfo->id;
}

int FeuCalcOperator::getPrecedence() {
    return mInfo->precedence;
}

bool FeuCalcOperator::isLeftAssociative() {
    return mInfo->leftAssociative;
}

bool FeuCalcOperator::canSupplant(FeuCalcOperator *fco) {
    int fcoPrec = fco->getPrecedence();
    int fcoID = fco->getID();
    // Grouping elements can't ever be superceded
    if (fcoID == FEU_OP_ID_LPAREN || fcoID == FEU_OP_ID_LSUBSCRIPT) return false;
    if (mInfo->precedence < fcoPrec) return false;
    if (mInfo->precedence > fcoPrec) return true;
    // If equal, it comes down to left-associativity.
    if (mInfo->leftAssociative) return true;
    return false;
}

string FeuCalcOperator::toString() {
    return (mInfo->op);
}
