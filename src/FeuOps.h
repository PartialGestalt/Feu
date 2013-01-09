
void feu_args_binary_get(FeuStack *s, FeuCalcItem **left, FeuCalcItem **right)
{
    // CLEAN: TODO: NULL checks here? 
    *right = (FeuCalcItem *)s->pop();
    *left = (FeuCalcItem *)s->pop();
    return;
}

void feu_args_binary_put(FeuCalcItem *left, FeuCalcItem *right)
{
    // Check refcount and delete if zero 
    if (!left->ref_count()) delete left;
    if (!right->ref_count()) delete right;
}



#define FEU_BINARY_OP(__name, __expr); \
    void feu_op_##__name(FeuStack *s) \
    { \
        FeuCalcItem *left, *right, *result; \
        feu_args_binary_get(s,&left,&right); \
        result = new FeuCalcNumber(__expr); \
        s->push(result); \
        feu_args_binary_put(left,right);\
        return; \
    } 


FEU_BINARY_OP(     add, (left->getValue() + right->getValue())    );
FEU_BINARY_OP(     sub, (left->getValue() - right->getValue())    );
FEU_BINARY_OP(    mult, (left->getValue() * right->getValue())    );
FEU_BINARY_OP(     div, (left->getValue() / right->getValue())    );
FEU_BINARY_OP(exponent, (pow(left->getValue(),right->getValue())) );
