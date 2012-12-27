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
private:
	float mValue; // A single numeric value
public:
	void proc(stack<FeuCalcItem *> calcStack);
    FeuCalcItem *copy();
    float getValue();
    void setValue(float);
};

#endif /* _FEU_CALCNUMBER_H_ */
