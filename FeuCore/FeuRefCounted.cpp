#include "FeuRefCounted.h"
#include "FeuLog.h"

FeuRefCounted::FeuRefCounted() {
    mRefCount = 0; // Nobody loves me yet....
}

void FeuRefCounted::ref_get() {
    mRefCount++;
}

void FeuRefCounted::ref_put() {
    mRefCount--;

    /* Error check */
    if (mRefCount < 0) {
        FeuLog::e("Negative refcount.");
        mRefCount = 0;
    }
}

int FeuRefCounted::ref_count() { 
    if (mRefCount < 0) {
        FeuLog::e("Negative refcount.");
        mRefCount = 0;
    }
    return mRefCount;
}
