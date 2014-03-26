/*
 * FeuCalcReference.h
 *
 * FeuCalcReference is a FeuCalcItem that manages a single object
 * attribute or function reference.
 */

#ifndef _FEU_CALC_REFERENCE_H_
#define _FEU_CALC_REFERENCE_H_

#include "FeuCalcItem.h"
#include "FeuThing.h"
#include "FeuSpecifier.h"
#include <stack>

class FeuCalcReference;

class FeuCalcReference : public FeuCalcItem {
public:
    FeuCalcReference(Feu *, FeuCalculable *, std::string);

private:
    FeuSpecifier mSpecifier; // Parse once for faster lookups...
    Feu *mFeu;
    std::string mInitial;
	FeuThing *mThing;  // Object whose value we're dealing with (if global)
    std::string mAttribute;
    double mValue;

public:
    bool mIsMethod; // true if this is a method

public:
	int proc(FeuStack *);
    FeuCalcItem *copy();
    double getValue();
    void setValue(double);
    std::string toString();
    void setContext(FeuThing *);

private:
    void resolveReference();

};

#endif /* _FEU_CALC_REFERENCE_H_ */
