/*
 * FeuCalcItem.h
 *
 * FeuCalcItem is a base class for items that contribute
 * to a calculation, for our internal arithmetic.
 *
 */

#ifndef _FEU_CALCITEM_H_
#define _FEU_CALCITEM_H_

#include <stack>
using namespace std;

class FeuCalcItem : public FeuRefCounted {
public:
	virtual ~FeuCalcItem() = 0;

public:
	virtual void proc(stack<FeuCalcItem *> *) = 0;
    virtual FeuCalcItem *copy() = 0;
    virtual float getValue() = 0;
    virtual void setValue(float) = 0;
    virtual string toString() = 0;
};

#endif /* _FEU_CALCITEM_H_ */
