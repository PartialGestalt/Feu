/*
 * FeuCalcMethod.cpp
 */

#include "feu_all.h"

FeuCalcMethod::FeuCalcMethod(FeuCalcReference *ref) : FeuCalcOperator((int)FEU_OP_ID_FUNCTION) {
    // Treat the reference as a method call...
    ref->mIsMethod = true;
    // Save it.
    mRef = ref;
}
