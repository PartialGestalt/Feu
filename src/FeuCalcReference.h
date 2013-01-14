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
#include "FeuSpecifier.h"
#include <stack>

class FeuCalcReference;

class FeuCalcReference : public FeuCalcItem {
public:
    FeuCalcReference(Feu *, std::string, FeuThing *contextThing = NULL);
private:
    Feu *mFeu;
    FeuSpecifier mSpecifier; // Parse once for faster lookups...
    std::string mInitial;
	FeuThing *mThing;
    std::string mAttribute;
    float mValue;
public:
	int proc(FeuStack *);
    FeuCalcItem *copy();
    float getValue();
    void setValue(float);
    std::string toString();
};

#endif /* _FEU_CALCREFERENCE_H_ */
