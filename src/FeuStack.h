/*
 * FeuStack.h
 *
 * FeuStack is a special case of stack that adds
 * refcount handling to the item.
 *
 */

#ifndef _FEU_STACK_H_
#define _FEU_STACK_H_

#include <stack>
using namespace std;

class FeuStack : public stack<FeuRefCounted *> {
public:
      FeuStack();
	 ~FeuStack();

public:
     void push(FeuRefCounted *);
     FeuRefCounted *pop();
};

#endif /* _FEU_STACK_H_ */
