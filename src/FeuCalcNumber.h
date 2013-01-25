/*
 * FeuCalcNumber.h
 *
 * FeuCalcNumber is FeuCalcItem that manages a single constant.
 */

#ifndef _FEU_CALC_NUMBER_H_
#define _FEU_CALC_NUMBER_H_

#include "FeuCalcItem.h"
#include <stack>


class FeuThing;

class FeuCalcNumber : public FeuCalcItem {
public:
    FeuCalcNumber(FeuCalculable *, float);
    FeuCalcNumber(FeuCalculable *, int);
    FeuCalcNumber(FeuCalculable *, std::string);
private:
	float mValue; // A single numeric value
public:
	int proc(FeuStack *);
    FeuCalcItem *copy();
    float getValue();
    void setValue(float);
    std::string toString();
};

#endif /* _FEU_CALC_NUMBER_H_ */
