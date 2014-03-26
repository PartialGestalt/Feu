/*
 * FeuList.cpp
 */

#include "FeuList.h"

#if 0
FeuList::FeuList() {
}

FeuList::~FeuList() {
    FeuRefCounted *frc;
    FeuLog::i("DESTRUCT: FeuList\n");
    // Pop everyone off and delete if they're at zero.
    while (!empty()) {
        frc = list::front();
        frc->ref_put();
        list::pop_front();
        if (!frc->ref_count()) {
            FeuLog::i("List not empty. (deleting) \n");
            delete frc;
        } else {
            FeuLog::i("List not empty, (refs left)\n");
        }
    }
}
#endif

void FeuList::push_back(FeuRefCounted *frc) {
    // Get a ref
    frc->ref_get();
    // Super push
    std::list<FeuRefCounted *>::push_back(frc);
}
void FeuList::push_front(FeuRefCounted *frc) {
    // Get a ref
    frc->ref_get();
    // Super push
    std::list<FeuRefCounted *>::push_front(frc);
}

void FeuList::pop_back() {
	FeuRefCounted *frc = std::list<FeuRefCounted *>::back();
    frc->ref_put();
    std::list<FeuRefCounted *>::pop_back();
}

void FeuList::pop_front() {
	FeuRefCounted *frc = std::list<FeuRefCounted *>::front();
    frc->ref_put();
    std::list<FeuRefCounted *>::pop_front();
}
