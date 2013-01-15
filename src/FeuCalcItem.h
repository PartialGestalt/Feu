/*
 * FeuCalcItem.h
 *
 * FeuCalcItem is a base class for items that contribute
 * to a calculation, for our internal arithmetic.
 *
 */

#ifndef _FEU_CALC_ITEM_H_
#define _FEU_CALC_ITEM_H_

#include <stack>

class FeuCalcItem : public FeuRefCounted {
public:
    FeuCalcItem();
	virtual ~FeuCalcItem() = 0;

public:
	virtual int proc(FeuStack *) = 0;
    virtual FeuCalcItem *copy() = 0;
    virtual float getValue() = 0;
    virtual void setValue(float) = 0;
    virtual std::string toString() = 0;
};

#endif /* _FEU_CALC_ITEM_H_ */
