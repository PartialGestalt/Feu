/*
 * FeuStack.cpp
 */

#include "feu.h"

#if 0
FeuStack::FeuStack() {
}

FeuStack::~FeuStack() {
    FeuRefCounted *frc;

    while (!empty()) {
        FeuLog::i("Stack not empty in destructor\n");
        frc = pop();
        if (!frc->ref_count()) delete frc;
    }
}
#endif

void FeuStack::push(FeuRefCounted *frc) {
    // Get a ref
    frc->ref_get();
    // Super push
    stack<FeuRefCounted *>::push(frc);
}

FeuRefCounted *FeuStack::pop() {
    FeuRefCounted *frc;
    // Get the object
    frc = stack<FeuRefCounted *>::top();
    // Pop it
    stack<FeuRefCounted *>::pop();
    // Release our reference
    frc->ref_put();

    // Return it
    return frc;
}
