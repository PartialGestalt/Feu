/*
 * FeuStack.h
 *
 * FeuStack is a special case of stack that adds
 * refcount handling to the stacked item.
 *
 */

#ifndef _FEU_STACK_H_
#define _FEU_STACK_H_

#include <stack>

#include "FeuRefCounted.h"

class FeuStack : public std::stack<FeuRefCounted *> {
public:
#if 0
      FeuStack();
	 ~FeuStack();
#endif

public:
     void push(FeuRefCounted *);
     FeuRefCounted *pop();
};

#endif /* _FEU_STACK_H_ */
