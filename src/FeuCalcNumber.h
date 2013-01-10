/*
 * FeuCalcNumber.h
 *
 * FeuCalcNumber is FeuCalcItem that manages a single constant.
 */

#ifndef _FEU_CALCNUMBER_H_
#define _FEU_CALCNUMBER_H_

#include "FeuCalcItem.h"
#include <stack>
using namespace std;

class FeuCalcNumber;

class FeuCalcNumber : public FeuCalcItem {
public:
    FeuCalcNumber(float);
    FeuCalcNumber(int);
    FeuCalcNumber(string);
private:
	float mValue; // A single numeric value
public:
	int proc(FeuStack *);
    FeuCalcItem *copy();
    float getValue();
    void setValue(float);
    string toString();
};

#endif /* _FEU_CALCNUMBER_H_ */
