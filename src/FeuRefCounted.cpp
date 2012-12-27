#include "feu.h"

FeuRefCounted::FeuRefCounted() {
    mRefCount = 0;
}

void FeuRefCounted::ref_get(FeuRefCounted *frc) {
    frc->mRefCount++;
}

void FeuRefCounted::ref_put(FeuRefCounted *frc) {
    frc->mRefCount--;
    if (frc->mRefCount <= 0) delete frc;
}
