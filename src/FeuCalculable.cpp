#include "feu_all.h"
#include <cmath>
#include "FeuOps.h" // Get op handlers

// Operator info table (lower number means higher precedence)
struct feuOpInfo feuOpInfoTable[] = {
    { FEU_OP_ID_COMMA, ",", 17, true, NULL },
    { FEU_OP_ID_ASSIGN, "=", 15, false, NULL },
    { FEU_OP_ID_ADDASSIGN, "+=", 15, false, NULL },
    { FEU_OP_ID_SUBASSIGN, "-=", 15, false, NULL },
    { FEU_OP_ID_MULTASSIGN, "*=", 15, false, NULL },
    { FEU_OP_ID_DIVASSIGN, "/=", 15, false, NULL },
    { FEU_OP_ID_MODASSIGN, "%=", 15, false, NULL },
    { FEU_OP_ID_SHLASSIGN, "<<=", 15, false, NULL },
    { FEU_OP_ID_SHRASSIGN, ">>=", 15, false, NULL },
    { FEU_OP_ID_ANDASSIGN, "&=", 15, false, NULL },
    { FEU_OP_ID_XORASSIGN, "^=", 15, false, NULL },
    { FEU_OP_ID_ORASSIGN, "|=", 15, false, NULL },
    { FEU_OP_ID_ORLOGIC, "||", 14, true, feu_op_orlogic },
    { FEU_OP_ID_ANDLOGIC, "&&", 13, true, feu_op_andlogic },
    { FEU_OP_ID_ORBITS, "|", 12, true, feu_op_andbits },
    { FEU_OP_ID_XORBITS, "^", 11, true, feu_op_xorbits },
    { FEU_OP_ID_ANDBITS, "&", 10, true, feu_op_andbits },
    { FEU_OP_ID_TESTEQUAL, "==", 9, true, feu_op_testequal },
    { FEU_OP_ID_TESTNOTEQUAL, "!=", 9, true, feu_op_testequal },
    { FEU_OP_ID_TESTLESS, "<", 8, true, feu_op_testless },
    { FEU_OP_ID_TESTLESSEQUAL, "<=", 8, true, feu_op_testlessequal },
    { FEU_OP_ID_TESTMORE, ">", 8, true, feu_op_testmore },
    { FEU_OP_ID_TESTMOREEQUAL, ">=", 8, true, feu_op_testmoreequal },
    { FEU_OP_ID_SHL, "<<", 7, true, NULL },
    { FEU_OP_ID_SHR, ">>", 7, true, NULL },
    { FEU_OP_ID_ADD, "+", 6, true, feu_op_add },
    { FEU_OP_ID_SUB, "-", 6, true, feu_op_sub },
    { FEU_OP_ID_MULT, "*", 5, true, feu_op_mult },
    { FEU_OP_ID_DIV, "/", 5, true, feu_op_div },
    { FEU_OP_ID_MOD, "%", 5, true, NULL },
    { FEU_OP_ID_EXPONENT, "^^", 4, false, feu_op_exponent }, 
    { FEU_OP_ID_INCR, "++", 3, false, NULL },
    { FEU_OP_ID_DECR, "--", 3, false, NULL },
    { FEU_OP_ID_NOTLOGIC, "!", 3, false, NULL },
    { FEU_OP_ID_NOTBITS, "~", 3, false, feu_op_notbits },
    { FEU_OP_ID_UNARYMINUS, "-", 3, false, feu_op_unaryminus },
    { FEU_OP_ID_LSUBSCRIPT, "[", 2, true, NULL },
    { FEU_OP_ID_RSUBSCRIPT, "]", 2, true, NULL },
    { FEU_OP_ID_LPAREN, "(", 2, true, NULL },
    { FEU_OP_ID_RPAREN, ")", 2, true, NULL },
    { FEU_OP_ID_FAILURE, "...", 0, true, NULL }
};

FeuCalculable::FeuCalculable(std::string expression, FeuThing *parentThing) {
    mParentThing = parentThing;
    mIsConstant = true; // May be overridden by tokenizer
    mLastResult = 0.0f; // As good a default as any...
    mRunCount = 0; // No runs yet.
    mOpMap = &feuOperators;
    FeuLog::i("Calculable is: \"", expression, "\"\n");
    mRPN = new FeuList();
    // Convert input string into tokens
    this->tokenize(expression);
    // Convert infix to RPN for easy calculation
    //     (also releases all token memory)
    this->rpn();
}

FeuCalculable::~FeuCalculable() {
    FeuLog::i("DESTRUCT: FeuCalculable\n");
    /* Delete the string tokens */
    {
        std::list<std::string *>::iterator i;
        for (i = mTokens.begin(); i != mTokens.end(); i++) {
            delete *i;
        }
    }
    /* Delete our RPN list */
    {
        FeuCalcItem *fci;
        FeuList::iterator i;
        for (i = mRPN->begin(); i != mRPN->end(); i++) {
            fci = (FeuCalcItem *)*i;
            delete fci;
        }
        delete mRPN;
    }
}

void FeuCalculable::tokenize(std::string formula) {
    std::string::iterator iter;
    char ch, lastch=0;
    int tokenState = FEU_TOKEN_NONE;
    int lastTokenState = FEU_TOKEN_NONE;
    std::string *accum = NULL;
    bool endAccum;
    bool startAccum;

    for (iter = formula.begin(); iter != formula.end(); iter++) {
        ch = *iter;
        endAccum=false;
        startAccum=false;
        switch (tokenState) {
            case FEU_TOKEN_NONE: {
                if (isdigit(ch) || (ch == '.') || (ch == '#')) {
                    // Starting a new number
                    tokenState = FEU_TOKEN_NUM;
                    startAccum = true;
                } else if (isalpha(ch)) {
                    // Starting a new reference
                    tokenState = FEU_TOKEN_REF;
                    startAccum = true;
                } else if (isspace(ch)) {
                    // More non-token chars, nothing to do
                } else {
                    // Everything else must be an operator
                    tokenState = FEU_TOKEN_OP;
                    startAccum = true;
                }
                break;
            }
            case FEU_TOKEN_NUM: {
                if (isxdigit(ch) || (ch == '.') ||
                    (((ch == 'x') || (ch == 'X')) && (lastch == '0')) ||
                    (((ch == 'b') || (ch == 'B')) && (lastch == '0')) ||
                    (((ch == 'd') || (ch == 'D')) && (lastch == '0')) )  {
                    // Add another numeric element to the accumulator
                } else if (isalpha(ch)) {
                    // Syntax error; must have an operator between number
                    // and object ref, or botched radix specifier
                    FeuLog::e("SYNTAX ERROR: Must have an operator between numbers and object references.\n");
                    // TODO: CLEAN: Throw an exception here, but in the meantime, pretend it's ok.
                    tokenState = FEU_TOKEN_REF;
                    startAccum = true;
                } else if (isspace(ch)) {
                    // Finish number.
                    tokenState = FEU_TOKEN_NONE;
                    endAccum = true;
                } else {
                    // Anything else is an operator
                    tokenState = FEU_TOKEN_OP;
                    startAccum = true;
                }
                break;
            }
            case FEU_TOKEN_OP: {
                if (isdigit(ch) || (ch == '.') || (ch == '#')) {
                    // Starting a new number after operator
                    tokenState = FEU_TOKEN_NUM;
                    startAccum = true;
                } else if (isalpha(ch)) {
                    // Starting a new object reference
                    tokenState = FEU_TOKEN_REF;
                    startAccum = true;
                } else if (isspace(ch)) {
                    tokenState = FEU_TOKEN_NONE;
                    endAccum = true;
                } else {
                    std::string *jamtest = new std::string(*accum);
                    // Possible additional character, but it
                    // may also be two operators jammed up against
                    // each other.  Test to see if the additional char
                    // would make an invalid operator, and force 
                    // a restart if so.
                    jamtest->append(1,ch);
                    if (0 == feuOperators.count(*jamtest)) {
                        // Compound not found, start a new token without
                        // changing token state.
                        startAccum = true;
                    }
                    delete jamtest;
                }
                break;
            }
            case FEU_TOKEN_REF: {
                if (isdigit(ch) || (ch == '.') ||
                    (isalpha(ch))) {
                    // Refs can contain (but not start with) any
                    // alphanumeric, and may contain dots.
                } else if (isspace(ch)) {
                    tokenState = FEU_TOKEN_NONE;
                    endAccum = true;
                } else {
                    // Heading into an operator
                    tokenState = FEU_TOKEN_OP;
                    startAccum = true;
                } 
                break;
            }
        }
        if (((startAccum == true) || (endAccum == true)) &&
             (NULL != accum)) {
            // Finishing old either explicitly or by virtue of
            // starting a new token accumulator....
            mTokens.push_back(accum);
            accum = NULL;
        }
        if (startAccum == true) {
            // Only explicit starts allowed
            accum = new std::string;
        }
        if (!isspace(ch) && (NULL != accum)) {
            accum->append(1,ch);
        }
        lastch = ch;
    } // End for
    // Anything left over gets added....
    if (NULL != accum) mTokens.push_back(accum);

    // Dump it for fun
    {
        std::string a = "Token: \"";
        std::string b = "\"\n";
        std::list<std::string *>::iterator i;
        for (i = mTokens.begin(); i != mTokens.end(); i++) {
            FeuLog::i(a + **i + b);
        }
    }
}

void FeuCalculable::rpn() {
    std::list<std::string *>::iterator i;
    std::stack<FeuCalcOperator *> opstack;
    FeuCalcOperator *fcop;
    bool done=false;
    FeuCalcOperator *fco_top;
    int lastTokenType = FEU_TOKEN_NONE;
    // Walk token list, using the shunting yard algorithm to organize
    // tokens into RPN.  Then, convert each token into a FeuCalcItem of
    // the appropriate type.
    for (i = mTokens.begin(); i != mTokens.end() ;i++) {
        if (isdigit((**i)[0])) {
            // Numeric token, just push to output
            mRPN->push_back(new FeuCalcNumber(**i));
            // Save our token type
            lastTokenType = FEU_TOKEN_NUM;
        } else if (isalpha((**i)[0])) {
            // Object reference, shunt as number
            mRPN->push_back(new FeuCalcReference(**i,NULL));
            // Have at least one object reference, so not known to be constant.
            mIsConstant = false;
            // Save our token type
            lastTokenType = FEU_TOKEN_REF;
        } else {
            // Anything else should be an operator
            fcop = new FeuCalcOperator(**i); 
            // How we handle the operator depends on precedence rules...
            switch(fcop->getID()) {
                // Left-grouping just gets pushed onto shunt
                case FEU_OP_ID_LPAREN:
                case FEU_OP_ID_LSUBSCRIPT:
                    opstack.push(fcop);
                    break;
                // Right-grouping pops until left grouper is found
                case FEU_OP_ID_RPAREN:  
                case FEU_OP_ID_RSUBSCRIPT: {
                    // CLEAN: TODO: This treats square brackets as pure
                    // grouping, rather than as a subscript selector, and
                    // doesn't leave a subscript operation on the stack.
                    // Since we don't support subscripting or arrays yet,
                    // I'm not going to worry about it.  It needs to be
                    // fixed eventually, though.
                    //
                    // Define which lgrouper we're looking for
                    int tgt_id = (fcop->getID() == FEU_OP_ID_RPAREN)?
                                  FEU_OP_ID_LPAREN:FEU_OP_ID_LSUBSCRIPT;
                    done = false;
                    while (!opstack.empty() && !done) {
                        fco_top = opstack.top();
                        opstack.pop();
                        if (fco_top->getID() == tgt_id) {
                            // What we're looking for!
                            done = true;
                            // Destroy the left grouper
                            delete fco_top;
                        } else {
                            // Move it to output 
                            mRPN->push_back(fco_top);
                        }
                    }
                    // Delete the right grouper
                    delete fcop;
                    break;
                }
                // Everything else is strict priority rules
                default: {
                    done = false;
                    // Start with any special handling (eg: operator overload):
                    //
                    // Based on previous token type, determine if a SUB is 
                    // really a unary minus.  
                    // A '-' that follows an operator or at the beginning 
                    // is a unary minus.  
                    // A '-' that follows a number or an object is a subtraction.
                    if (fcop->getID() == FEU_OP_ID_SUB) {
                        if (lastTokenType == FEU_TOKEN_NONE ||
                            lastTokenType == FEU_TOKEN_OP) {
                            fcop->setInfo(&feuOpInfoTable[FEU_OP_ID_UNARYMINUS]);
                        }
                    }
                    // Now, handle common processing
                    while (!opstack.empty() && !done) {
                        if (fcop->canSupplant(opstack.top())) {
                            // New is higher priority; pop old onto output
                            mRPN->push_back(opstack.top());
                            opstack.pop();
                        } else {
                            // New is lower priority; push onto stack
                            opstack.push(fcop);
                            done = true;
                        }
                    }
                    if (!done) opstack.push(fcop);
                    break;
                }
            }
            // Save our token type
            lastTokenType = FEU_TOKEN_OP;
        }
    }
    // Pop anything left onto output 
    while (!opstack.empty()) {
        mRPN->push_back(opstack.top());
        opstack.pop();
    }
    // Dump RPN for fun
    {
        FeuList::iterator i;
        for (i = mRPN->begin(); i != mRPN->end(); i++) {
            FeuLog::i("RPN Token: \"",((FeuCalcItem *)(*i))->toString(),"\"\n");
        }
    }
}

float FeuCalculable::proc() {
    FeuList::iterator i;
    FeuCalcItem *fci;

    // Shortcut for constants....
    mRunCount++;
    if (mIsConstant && (mRunCount > 1)) {
        return mLastResult;
    }

    // No Shortcut -- actually run it

    // Walk list of calc items, calling each proc() routine.  
    // The result should be left on the stack at the end.
    for (i=mRPN->begin(); i != mRPN->end(); i++) {
        fci = (FeuCalcItem *)*i;
        if (0 != fci->proc(&mCalcStack)) {
            //  Something failed.
            FeuLog::e("Error in arithmetic processing.\n");
            break;
        }
    }

    // There should be exactly one calcitem left on the stack.
    fci = (FeuCalcItem *)mCalcStack.pop();
    mLastResult = fci->getValue();
    if (!fci->ref_count()) delete fci;

    //    Make sure stack is clear
    while (!mCalcStack.empty()) {
        FeuLog::w("Calculable stack not empty after proc() exit.\n");
        fci = (FeuCalcItem *)mCalcStack.pop();
        if (!fci->ref_count()) delete fci;
    }

    return mLastResult;
}

void FeuCalculable::setParentThing(FeuThing *thing) {
    mParentThing = thing;
}
