/*
 * FeuCalcOperator.h
 *
 * FeuCalcOperator is FeuCalcItem that manages an operator
 */

#ifndef _FEU_CALCOPERATOR_H_
#define _FEU_CALCOPERATOR_H_

#include "FeuCalcItem.h"
#include <stack>
using namespace std;

class FeuCalcOperator;

class FeuCalcOperator : public FeuCalcItem {
public:
    FeuCalcOperator(string);
private:
	struct feuOpInfo *mInfo;
public:
	void proc(FeuStack *);
    FeuCalcItem *copy();
    float getValue();
    void setValue(float); 
    string toString();

public:
    int getID();
    int getPrecedence();
    bool isLeftAssociative();
    bool canSupplant(FeuCalcOperator *fco); // Is this more important than fco?
};

#endif /* _FEU_CALCOPERATOR_H_ */
