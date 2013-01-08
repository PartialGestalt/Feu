#include "feu.h"

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
    { FEU_OP_ID_ORLOGIC, "||", 14, true, NULL },
    { FEU_OP_ID_ANDLOGIC, "&&", 13, true, NULL },
    { FEU_OP_ID_ORBITS, "|", 12, true, NULL },
    { FEU_OP_ID_XORBITS, "^", 11, true, NULL },
    { FEU_OP_ID_ANDBITS, "&", 10, true, NULL },
    { FEU_OP_ID_TESTEQUAL, "==", 9, true, NULL },
    { FEU_OP_ID_TESTNOTEQUAL, "!=", 9, true, NULL },
    { FEU_OP_ID_TESTLESS, "<", 8, true, NULL },
    { FEU_OP_ID_TESTLESSEQUAL, "<=", 8, true, NULL },
    { FEU_OP_ID_TESTMORE, ">", 8, true, NULL },
    { FEU_OP_ID_TESTMOREEQUAL, ">=", 8, true, NULL },
    { FEU_OP_ID_SHL, "<<", 7, true, NULL },
    { FEU_OP_ID_SHR, ">>", 7, true, NULL },
    { FEU_OP_ID_ADD, "+", 6, true, NULL },
    { FEU_OP_ID_SUB, "-", 6, true, NULL },
    { FEU_OP_ID_MULT, "*", 5, true, NULL },
    { FEU_OP_ID_DIV, "/", 5, true, NULL },
    { FEU_OP_ID_MOD, "%", 5, true, NULL },
    { FEU_OP_ID_EXPONENT, "^^", 4, false, NULL }, 
    { FEU_OP_ID_INCR, "++", 3, false, NULL },
    { FEU_OP_ID_DECR, "--", 3, false, NULL },
    { FEU_OP_ID_NOTLOGIC, "!", 3, false, NULL },
    { FEU_OP_ID_NOTBITS, "~", 3, false, NULL },
    { FEU_OP_ID_LSUBSCRIPT, "[", 2, true, NULL },
    { FEU_OP_ID_RSUBSCRIPT, "]", 2, true, NULL },
    { FEU_OP_ID_LPAREN, "(", 2, true, NULL },
    { FEU_OP_ID_RPAREN, ")", 2, true, NULL },
    { FEU_OP_ID_FAILURE, "...", 0, true, NULL }
};

FeuCalculable::FeuCalculable(string expression) {
    mIsConstant = true; // May be overridden by tokenizer
    mLastResult = 0.0f; // As good a default as any...
    mRunCount = 0; // No runs yet.
    mOpMap = &feuOperators;
    FeuLog::i("Calculable is: \"", expression, "\"\n");
    // Convert input string into tokens
    this->tokenize(expression);
    // Convert infix to RPN for easy calculation
    //     (also releases all token memory)
    this->rpn();
}

FeuCalculable::~FeuCalculable() {
    // Walk our RPN list, deleting each item
    list<FeuCalcItem *>::iterator iter;
    for (iter = mRPN.begin();iter != mRPN.end(); iter++) {
        delete *iter;
    }
}

void FeuCalculable::tokenize(string formula) {
    string::iterator iter;
    char ch, lastch=0;
    int tokenState = FEU_TOKEN_NONE;
    string *accum = NULL;
    bool endAccum;
    bool startAccum;

    for (iter = formula.begin(); iter != formula.end(); iter++) {
        ch = *iter;
        endAccum=false;
        startAccum=false;
        switch (tokenState) {
            case FEU_TOKEN_NONE: {
                if (isdigit(ch) || (ch == '.')) {
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
                    (((ch == 'x') || (ch == 'X')) && (lastch == '0')))  {
                    // Add another numeric element to the accumulator
                } else if (isalpha(ch)) {
                    // Syntax error; must have an operator between number
                    // and object ref.
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
                if (isdigit(ch) || (ch == '.')) {
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
                    string *jamtest = new string(*accum);
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
                        FeuLog::i("FAILED\n");
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
            accum = new string;
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
        string a = "Token: \"";
        string b = "\"\n";
        list<string *>::iterator i;
        for (i = mTokens.begin(); i != mTokens.end(); i++) {
            FeuLog::i(a + **i + b);
        }
    }
}

void FeuCalculable::rpn() {
    list<string *>::iterator i;
    stack<FeuCalcOperator *> opstack;
    FeuCalcOperator *fcop;
    bool done=false;
    FeuCalcOperator *fco_top;
    // Walk token list, using the shunting yard algorithm to organize
    // tokens into RPN.  Then, convert each token into a FeuCalcItem of
    // the appropriate type.
    for (i = mTokens.begin(); i != mTokens.end() ;i++) {
        if (isdigit((**i)[0])) {
            // Numeric token, just push to output
            mRPN.push_back(new FeuCalcNumber(**i));
        } else if (isalpha((**i)[0])) {
            // Object reference, shunt as number
            mRPN.push_back(new FeuCalcReference(**i));
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
                        } else {
                            // Move it to output 
                            mRPN.push_back(fco_top);
                        }
                    }
                    break;
                }
                // Everything else is strict priority rules
                default: {
                    done = false;
                    while (!opstack.empty() && !done) {
                        if (fcop->canSupplant(opstack.top())) {
                            // New is higher priority; pop old onto output
                            mRPN.push_back(opstack.top());
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
        }
    }
    // Pop anything left onto output 
    while (!opstack.empty()) {
        mRPN.push_back(opstack.top());
        opstack.pop();
    }
    // Dump RPN for fun
    {
        list<FeuCalcItem *>::iterator i;
        for (i = mRPN.begin(); i != mRPN.end(); i++) {
            FeuLog::i("RPN Token: \"",(*i)->toString(),"\"\n");
        }
    }
}

float FeuCalculable::proc() {
    // Shortcut for constants....
    mRunCount++;
    if (mIsConstant && (mRunCount > 1)) {
        return mLastResult;
    }

    // No Shortcut -- actually run it
}

