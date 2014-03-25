/*
 * FeuRefCounted.h
 *
 * FeuRefCounted is a base class for any object that has a reference
 * count.
 *
 * Objects are created with a refcount of zero.
 */

#ifndef _FEU_REF_COUNTED_H_
#define _FEU_REF_COUNTED_H_

class FeuRefCounted {
public:
    FeuRefCounted();

private:
    int mRefCount;

public:
	void ref_get();
	void ref_put();
    int ref_count();

};



#endif /* _FEU_REF_COUNTED_H_ */
