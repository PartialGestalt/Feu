/*
 * FeuCalcReference.h
 *
 * FeuCalcReference is a FeuCalcItem that manages a single object
 * attribute reference.
 */

#ifndef _FEU_CALCREFERENCE_H_
#define _FEU_CALCREFERENCE_H_

#include "FeuCalcItem.h"
#include "FeuThing.h"
#include <stack>
using namespace std;

class FeuCalcReference;

class FeuCalcReference : public FeuCalcItem {
public:
    FeuCalcReference(string);
    FeuCalcReference(FeuThing *,string);
private:
	FeuThing *mThing;
    string mAttribute;
    float mValue;
public:
	void proc(stack<FeuCalcItem *> calcStack);
    FeuCalcItem *copy();
    float getValue();
    void setValue(float);
    string toString();
};

#endif /* _FEU_CALCREFERENCE_H_ */
