/*
 * FeuCalcMethod.h
 *
 * FeuCalcMethod is a wrapper around a FeuCalcReference, that
 * can be an operator.
 */

#ifndef _FEU_CALC_METHOD_H_
#define _FEU_CALC_METHOD_H_

#include "FeuCalcItem.h"
#include "FeuCalcOperator.h"
#include "FeuThing.h"
#include "FeuSpecifier.h"
#include <stack>

class FeuCalcReference;
class FeuCalcOperator;

class FeuCalcMethod : public FeuCalcOperator {
public:
    FeuCalcMethod(FeuCalculable *calc, FeuCalcReference *ref);

public:
    FeuCalcReference *mRef;

};

#endif /* _FEU_CALC_METHOD_H_ */
