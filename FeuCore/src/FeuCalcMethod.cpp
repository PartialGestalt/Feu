/*
 * FeuCalcMethod.cpp
 */

#include "FeuCalcMethod.h"

#include "FeuCalcReference.h"
#include "FeuCalculable.h"


FeuCalcMethod::FeuCalcMethod(FeuCalculable *calc, FeuCalcReference *ref) : FeuCalcOperator(calc, (int)FEU_OP_ID_FUNCTION) {
    // Treat the reference as a method call...
    ref->mIsMethod = true;
    // Save it.
    mRef = ref;
}
