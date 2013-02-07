/*
 * FeuCalcOperator.cpp
 */

#include "feu_all.h"

FeuCalcOperator::FeuCalcOperator(FeuCalculable *calc, std::string initVal) : FeuCalcItem(calc) {
    std::map<std::string,int>::iterator i = feuOperators.find(initVal);
    if (i == feuOperators.end()) {
        // CLEAN: TODO: Throw an exception here.
        mInfo = &feuOpInfoTable[FEU_OP_ID_FAILURE];
    } else {
        mInfo = &feuOpInfoTable[i->second]; 
    }
}

FeuCalcOperator::FeuCalcOperator(FeuCalculable *calc, int idVal) : FeuCalcItem(calc) {
    // Constructor for creating by ID
    mInfo = &feuOpInfoTable[idVal];
}

int FeuCalcOperator::proc(FeuStack *calcStack) {
    if (NULL != mInfo->func) return (mInfo->func)(calcStack,this);
    else FeuLog::w("No function to implement operator \"",mInfo->op,"\"\n");
    return -1; // No handler is a problem.
}

FeuCalcItem *FeuCalcOperator::copy() {
    FeuCalcOperator *fco = new FeuCalcOperator(mCalculable, mInfo->op);
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

void FeuCalcOperator::setInfo(struct feuOpInfo *newInfo) {
    mInfo = newInfo;
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
    // Functions and grouping elements can't ever be superceded by normal 
    // operators.
    if (fcoID == FEU_OP_ID_FUNCTION || 
        fcoID == FEU_OP_ID_LPAREN   || 
        fcoID == FEU_OP_ID_LSUBSCRIPT) return false;
    if (mInfo->precedence < fcoPrec) return false;
    if (mInfo->precedence > fcoPrec) return true;
    // If equal, it comes down to left-associativity.
    if (mInfo->leftAssociative) return true;
    return false;
}

std::string FeuCalcOperator::toString() {
    return (mInfo->op);
}
