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
    FeuCalcNumber(FeuCalculable *, double);
    FeuCalcNumber(FeuCalculable *, int);
    FeuCalcNumber(FeuCalculable *, std::string);
private:
	double mValue; // A single numeric value
public:
	int proc(FeuStack *);
    FeuCalcItem *copy();
    double getValue();
    void setValue(double);
    std::string toString();
};

#endif /* _FEU_CALC_NUMBER_H_ */
