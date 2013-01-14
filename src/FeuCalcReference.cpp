/*
 * FeuCalcReference.cpp
 */

#include "feu_all.h"

FeuCalcReference::FeuCalcReference(Feu *feu, std::string initVal, FeuThing *contextThing) : mSpecifier(initVal) {
    mFeu = feu;
    // "contextThing", if given, is the object we will belong to, which defines 
    // the scope and context.  "mThing" is the object whose value we will use during
    // calculations, and must be resolved before use.
    mInitial = initVal;
    mContext = contextThing;
    mAttribute = mSpecifier.mAttribute;
    mThing = NULL;
        // If we're not in the initial load, and the reference is a global, 
        // this resolves now; if the reference is local (or relative) or 
        // we're just now loading, it won't resolve yet.
    resolveReference();
        // If we've resolved a reference, go ahead and extract the current
        // value; otherwise just init to zero.
    mValue = mThing?mThing->getAttributeValue(mAttribute):0.0;
    return;
}

int FeuCalcReference::proc(FeuStack *calcStack) {
    // For processing, we simply push onto the calculator stack
    calcStack->push(this);
    return 0;
}

FeuCalcItem *FeuCalcReference::copy() {
    return new FeuCalcReference(mFeu,mInitial,NULL);
}

void FeuCalcReference::setContext(FeuThing *context) {
    mContext = context;
}

void FeuCalcReference::resolveReference() {
    // If we're not resolved yet, do it here....
    // NOTE: We must have a context pointer if we're not a global!!!
    if (NULL == mThing) {
        if (mContext) { 
            // We're running in context; do full lookup
            mThing = FeuThing::findThing(mFeu,mContext,&mSpecifier);
        } else {
            // No context set! If global fails, this is an error.
            mThing = FeuThing::findGlobalThing(mFeu,&mSpecifier);
        }
    }
}

float FeuCalcReference::getValue() {
    // TODO: CLEAN: For constants, use cached value?
    // Try to resolve it....
    if (!mThing) {
        resolveReference();
        // If we didn't get it, throw an error.
        if (!mThing) {
            FeuLog::e("Unknown object reference \"" + mInitial + "\", perhaps missing context?\n");
        }
    }
    // Now pull value
    if (mThing) return mThing->getAttributeValue(mAttribute);
    else return mValue;
}

void FeuCalcReference::setValue(float newVal) {
    // Try to resolve it....
    if (!mThing) {
        resolveReference();
        // If we didn't get it, throw an error.
        if (!mThing) {
            FeuLog::e("Unknown object reference \"" + mInitial + "\", perhaps missing context?\n");
        }
    }
    // Set it
    if (mThing) mThing->setAttributeValue(mAttribute,newVal);
    mValue = newVal;
}

std::string FeuCalcReference::toString() {
    return mInitial;
}
