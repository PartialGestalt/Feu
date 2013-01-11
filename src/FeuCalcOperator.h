/*
 * FeuCalcOperator.h
 *
 * FeuCalcOperator is FeuCalcItem that manages an operator
 */

#ifndef _FEU_CALCOPERATOR_H_
#define _FEU_CALCOPERATOR_H_

#include "FeuCalcItem.h"
#include <stack>

class FeuCalcOperator;

class FeuCalcOperator : public FeuCalcItem {
public:
    FeuCalcOperator(std::string);
private:
	struct feuOpInfo *mInfo;
public:
	int proc(FeuStack *);
    FeuCalcItem *copy();
    float getValue();
    void setValue(float); 
    std::string toString();

public:
    int getID();
    void setInfo(struct feuOpInfo *); // for overloaded operators.
    int getPrecedence();
    bool isLeftAssociative();
    bool canSupplant(FeuCalcOperator *fco); // Is this more important than fco?
};

#endif /* _FEU_CALCOPERATOR_H_ */
