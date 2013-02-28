/*
 * FeuCalcReference.cpp
 */

#include "feu_all.h"
#include <typeinfo>

FeuCalcReference::FeuCalcReference(Feu *feu, FeuCalculable *calc, std::string initVal) : mSpecifier(initVal), FeuCalcItem(calc) {
    mFeu = feu;
    // "contextThing", if given, is the object we will belong to, which defines 
    // the scope and context.  "mThing" is the object whose value we will use during
    // calculations, and must be resolved before use.
    mInitial = initVal;
    mAttribute = mSpecifier.mAttribute;
    mIsMethod = false; // Will get updated later if true...
    mThing = NULL;
        // If we're not in the initial load, and the reference is a global, 
        // this resolves now; if the reference is local (or relative) or 
        // we're just now loading, it won't resolve yet.
    resolveReference();
    return;
}

int FeuCalcReference::proc(FeuStack *calcStack) {
    FeuThing *procThing = NULL;
    struct feuMethod *meth;
    double retVal;

    if (mSpecifier.isSelf()) {
        procThing = mCalculable->mContext;
    } else {
        procThing = mThing;
    }
    if (!procThing) {
        // Couldn't resolve!
        FeuLog::e("Can't resolve processing object...dude, I just don't know what to do!\n");
        return -1;
    }
       
    // Case 1: Unmarked as method
    if (!mIsMethod) {
        if (procThing->hasAttribute(mAttribute)) {
            // Case 1.1: Basic attribute; just push onto stack
            calcStack->push(this);
            return 0;
        } else if (procThing->hasMethod(mAttribute)) {
            // Case 1.2: Really a method; If we're here, there were no
            //           parentheses in the declaration.  Call the
            //           method function with no args.
            meth = procThing->mMethods[mAttribute];
            if (0 != meth->argCount) {
                // Method requires arguments, but none were provided.
                FeuLog::e("Method \"" + mInitial + "\" requires " + stringof(meth->argCount) + " arguments, but none provided.\n");
                return (-1);
            }
            // Arg check passed, call func
            retVal = (meth->func)(procThing,NULL);
            // If we have a return value, push it onto the stack
            if (meth->isReturning) calcStack->push(new FeuCalcNumber(mCalculable, retVal));
            return 0;
        } else {
            // Case 1.3: Attribute or method not found...
            //      NOTE: We shouldn't ever get here, as the original
            //      ref resolution should catch this kind of error.
            FeuLog::e("Can't find attribute or method \"" + mInitial + "\"\n");
            return -1; 
        }
    } else {
        // Case 2: Actually marked as a method, so must be in method map
        if (!procThing->hasMethod(mAttribute)) {
            // Attribute as method error?
            if (procThing->hasAttribute(mAttribute)) {
                FeuLog::e("Attempt to call attribute (\"" + mInitial + "\") as a method.  Don't use parentheses for simple attribute references.\n");
            } else {
                // Generic "not found" error.
                FeuLog::e("Attempt to call unknown method \"" + mInitial + "\".\n");
            }
            return -1;
        } else {
            FeuCalcItem *item;
            FeuCalcOperator *op;
            int argcount = 0;
            bool done = false;
            std::vector<double> *argv = new std::vector<double>();
            // Yo La Tengo.  Build arg list and call handler.
            while (!calcStack->empty() && !done) {
                item = (FeuCalcItem *)calcStack->pop();
                if (typeid(*item) == typeid(FeuCalcOperator)) {
                    // Operator....is it our end marker? 
                    op = (FeuCalcOperator *)item;
                    if (op->getID() == FEU_OP_ID_ENDARG) {
                        done = true;   // Got it!
                    } else {
                        // Operators as function args?  That's an error.
                        FeuLog::e("Operator \"" + op->toString() + "\" cannot be used as a method argument.\n");
                        return -1;
                    }
                } else {
                    // Not an operator.  Add to list.
                    // NOTE: The push_front reorders the stack into natural
                    // arg order for the method function.
                    argcount++;
                    argv->insert(argv->begin(),item->getValue());
                }
                // Possibly delete item
                if (!item->ref_count()) delete item;
            }
            meth = procThing->mMethods[mAttribute];
            // Arg check
            if (argcount != meth->argCount) {
                // Method requires different # of arguments.
                FeuLog::e("Method \"" + mInitial + "\" requires " + stringof(meth->argCount) + " arguments (" + stringof(argcount) + " provided).\n");
                delete argv;
                return (-1);
            }
            // Arg check passed, call func
            retVal = (meth->func)(procThing,argv);
            // If we have a return value, push it onto the stack
            if (meth->isReturning) calcStack->push(new FeuCalcNumber(mCalculable, retVal));
            // Destroy arg list
            delete argv;
        }
    }
    return 0;
}

FeuCalcItem *FeuCalcReference::copy() {
    return new FeuCalcReference(mFeu,mCalculable,mInitial);
}

void FeuCalcReference::resolveReference() {
#if 0
    if (mSpecifier.isSelf()) {
        FeuLog::i("Resolving self() reference \"" + mInitial + "\"\n");
    } else {
        FeuLog::i("Resolving global reference \"" + mInitial + "\"\n");
    }
#endif
    // If we're not resolved yet, do it here....
    // NOTE: We must have a context pointer if we're not a global!!!
    if (!mSpecifier.isSelf() && !mThing) {
        // No context set! If global fails, this is an error.
        mThing = FeuThing::findGlobalThing(mFeu,&mSpecifier);
    }
    // If this is a self-reference (i.e. just attribute) we can defer
    // until runtime processing; otherwise, we've got an error.
    if (!mThing && !mSpecifier.isSelf()) {
        FeuLog::e("Failed to resolve object reference \"" + mInitial + "\"\n");
    }
}

double FeuCalcReference::getValue() {
    FeuThing *procThing;
    // TODO: CLEAN: For constants, use cached value?

    // Choose the reference object
    if (!mSpecifier.isSelf()) {
        // Try to resolve it....
        if (!mThing) {
            resolveReference();
        }
        procThing = mThing;
    } else {
        procThing = mCalculable->mContext;
    }
    // If we don't have a reference object, throw an error.
    if (!procThing) {
        FeuLog::e("Unknown object reference \"" + mInitial + "\", perhaps missing context?\n");
        // TODO: CLEAN: Throw an exception here....
        return mValue; 
    }
    // Now pull value
    return procThing->getAttributeValue(mAttribute);
}

void FeuCalcReference::setValue(double newVal) {
    FeuThing *procThing;
    // TODO: CLEAN: For constants, use cached value?

    // Choose the reference object
    if (!mSpecifier.isSelf()) {
        // Try to resolve it....
        if (!mThing) {
            resolveReference();
        }
        procThing = mThing;
    } else {
        procThing = mCalculable->mContext;
    }
    // If we don't have a reference object, throw an error.
    if (!procThing) {
        FeuLog::e("Unknown object reference \"" + mInitial + "\", perhaps missing context?\n");
        // TODO: CLEAN: Throw an exception here....
    }
    // Set it
    if (procThing) procThing->setAttributeValue(mAttribute,newVal);
    mValue = newVal;
}

std::string FeuCalcReference::toString() {
    return mInitial;
}
