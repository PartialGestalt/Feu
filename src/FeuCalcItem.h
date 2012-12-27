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

class FeuCalcItem {
public:
	virtual ~FeuCalcItem() {};
protected:
    FeuCalcItem *mRef;  // If a copy, item this is a copy of...
public:
	virtual void proc(stack<FeuCalcItem> calcStack);
    virtual FeuCalcItem *copy();
    virtual float getValue();
    virtual void setValue(float);
    
};

#endif /* _FEU_CALCITEM_H_ */
