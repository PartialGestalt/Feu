/*
 * FeuCalcNumber.h
 *
 * FeuCalcNumber is FeuCalcItem that manages a single constant.
 */

#ifndef _FEU_CALCNUMBER_H_
#define _FEU_CALCNUMBER_H_

#include "FeuCalcItem.h"
#include <stack>

class FeuCalcNumber;

class FeuCalcNumber : public FeuCalcItem {
public:
    FeuCalcNumber(float);
    FeuCalcNumber(int);
    FeuCalcNumber(std::string);
private:
	float mValue; // A single numeric value
public:
	int proc(FeuStack *);
    FeuCalcItem *copy();
    float getValue();
    void setValue(float);
    std::string toString();
};

#endif /* _FEU_CALCNUMBER_H_ */
