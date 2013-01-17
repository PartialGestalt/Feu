/*
 * FeuCalcOperator.h
 *
 * FeuCalcOperator is FeuCalcItem that manages an operator
 */

#ifndef _FEU_CALC_OPERATOR_H_
#define _FEU_CALC_OPERATOR_H_

#include "FeuCalcItem.h"
#include <stack>

class FeuCalcOperator;
class FeuThing;

class FeuCalcOperator : public FeuCalcItem {
public:
    FeuCalcOperator(std::string);
    FeuCalcOperator(int);
private:
	struct feuOpInfo *mInfo;
public:
	int proc(FeuStack *, FeuThing *contextThing = NULL);
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

#endif /* _FEU_CALC_OPERATOR_H_ */
