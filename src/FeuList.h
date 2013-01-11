/*
 * FeuList.h
 *
 * FeuList is a special case of list that adds
 * refcount handling to the item.
 *
 * TODO: We only handle the push/pop semantics; probably
 * need to add support for insert/erase/delete/etc.
 *
 */

#ifndef _FEU_LIST_H_
#define _FEU_LIST_H_

#include <list>

class FeuList : public std::list<FeuRefCounted *> {
public:
#if 0
      FeuList();
	 ~FeuList();
#endif

public:
     void push_back(FeuRefCounted *);
     void pop_back();
     void push_front(FeuRefCounted *);
     void pop_front();
};

#endif /* _FEU_LIST_H_ */
