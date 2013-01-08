/*
 * FeuList.cpp
 */

#include "feu.h"

FeuList::FeuList() {
    // CLEAN: TODO: need to call super()?
}

FeuList::~FeuList() {
    // CLEAN: TODO: need to call super()?
}

void FeuList::push_back(FeuRefCounted *frc) {
    // Get a ref
    frc->ref_get();
    // Super push
    list::push_back(frc);
}
void FeuList::push_front(FeuRefCounted *frc) {
    // Get a ref
    frc->ref_get();
    // Super push
    list::push_front(frc);
}

void FeuList::pop_back() {
    list::back()->ref_put();
    list::pop_back();
}

void FeuList::pop_front() {
    list::front()->ref_put();
    list::pop_front();
}
