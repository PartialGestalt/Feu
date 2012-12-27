/*
 * FeuRefCounted.h
 *
 * FeuRefCounted is a base class for any object that has a reference
 * count and self-destructs when the refcount goes to zero.
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
	static void ref_get(FeuRefCounted *);
	static void ref_put(FeuRefCounted *);
};



#endif /* _FEU_REF_COUNTED_H_ */
