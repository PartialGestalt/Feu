/*
 * FeuOps.h -- define available FeuCalculable operators
 */

#ifndef _FEU_OPS_H_
#define _FEU_OPS_H_

void feu_args_unary_get(FeuStack *s, FeuCalcItem **right)
{
    // CLEAN: TODO: NULL checks here? 
    *right = (FeuCalcItem *)s->pop();
    return;
}

void feu_args_binary_get(FeuStack *s, FeuCalcItem **left, FeuCalcItem **right)
{
    // CLEAN: TODO: NULL checks here? 
    *right = (FeuCalcItem *)s->pop();
    *left = (FeuCalcItem *)s->pop();
    return;
}

void feu_args_unary_put(FeuCalcItem *right)
{
    // Check refcount and delete if zero 
    if (!right->ref_count()) delete right;
}

void feu_args_binary_put(FeuCalcItem *left, FeuCalcItem *right)
{
    // Check refcount and delete if zero 
    if (!left->ref_count()) delete left;
    if (!right->ref_count()) delete right;
}


#define FEU_UNARY_OP(__name, __expr) \
    int feu_op_##__name(FeuStack *s, FeuCalcOperator *op) \
    { \
        FeuCalcItem *right, *result; \
        feu_args_unary_get(s,&right); \
        if (NULL == right) return -1; \
        result = new FeuCalcNumber(__expr); \
        s->push(result); \
        feu_args_unary_put(right);\
        return 0; \
    } 


#define FEU_BINARY_OP(__name, __expr) \
    int feu_op_##__name(FeuStack *s, FeuCalcOperator *op) \
    { \
        FeuCalcItem *left, *right, *result; \
        feu_args_binary_get(s,&left,&right); \
        if ((NULL == left) || (NULL == right)) return -1; \
        result = new FeuCalcNumber(__expr); \
        s->push(result); \
        feu_args_binary_put(left,right);\
        return 0; \
    } 

#define FEU_BINARY_SIMPLE(__name, __opstring) \
    FEU_BINARY_OP(__name,(left->getValue() __opstring right->getValue()))


FEU_BINARY_SIMPLE(          add, +  );
FEU_BINARY_SIMPLE(          sub, -  );
FEU_BINARY_SIMPLE(         mult, *  );
FEU_BINARY_SIMPLE(          div, /  );
FEU_BINARY_SIMPLE(    testequal, == );
FEU_BINARY_SIMPLE( testnotequal, != );
FEU_BINARY_SIMPLE(     testless, <  );
FEU_BINARY_SIMPLE(testlessequal, <= );
FEU_BINARY_SIMPLE(     testmore, >  );
FEU_BINARY_SIMPLE(testmoreequal, >= );
FEU_BINARY_SIMPLE(      orlogic, || );
FEU_BINARY_SIMPLE(     andlogic, && );

FEU_BINARY_OP(     exponent, (std::pow(left->getValue(),right->getValue())) );
FEU_BINARY_OP(       orbits, ((int)left->getValue() | (int)right->getValue()) );
FEU_BINARY_OP(      andbits, ((int)left->getValue() & (int)right->getValue()) );
FEU_BINARY_OP(      xorbits, ((int)left->getValue() ^ (int)right->getValue()) );

FEU_UNARY_OP(       notbits, (~((int)right->getValue())) );
FEU_UNARY_OP(    unaryminus, (-((int)right->getValue())) );

#endif /* _FEU_OPS_H_ */
