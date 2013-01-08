/*
 * FeuStack.cpp
 */

#include "feu.h"

FeuStack::FeuStack() {
    // CLEAN: TODO: need to call super()?
}

FeuStack::~FeuStack() {
    // CLEAN: TODO: need to call super()?
}

void FeuStack::push(FeuRefCounted *frc) {
    // Get a ref
    frc->ref_get();
    // Super push
    stack::push(frc);
}

FeuRefCounted *FeuStack::pop() {
    FeuRefCounted *frc;
    // Get the object
    frc = stack::top();
    // Pop it
    stack::pop();
    // Release our reference
    frc->ref_put();

    // Return it
    return frc;
}
