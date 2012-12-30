#include "feu.h"

// Operator info table
static struct feuOpInfo feuOpInfoTable[] = {
    { FEU_OP_ID_COMMA, ",", 17, true },
    { FEU_OP_ID_ASSIGN, "=", 15, false },
    { FEU_OP_ID_ADDASSIGN, "+=", 15, false },
    { FEU_OP_ID_SUBASSIGN, "-=", 15, false },
    { FEU_OP_ID_MULTASSIGN, "*=", 15, false },
    { FEU_OP_ID_DIVASSIGN, "/=", 15, false },
    { FEU_OP_ID_MODASSIGN, "%=", 15, false },
    { FEU_OP_ID_SHLASSIGN, "<<=", 15, false },
    { FEU_OP_ID_SHRASSIGN, ">>=", 15, false },
    { FEU_OP_ID_ANDASSIGN, "&=", 15, false },
    { FEU_OP_ID_XORASSIGN, "^=", 15, false },
    { FEU_OP_ID_ORASSIGN, "|=", 15, false },
    { FEU_OP_ID_ORLOGIC, "||", 14, true },
    { FEU_OP_ID_ANDLOGIC, "&&", 13, true },
    { FEU_OP_ID_ORBITS, "|", 12, true },
    { FEU_OP_ID_XORBITS, "^", 11, true },
    { FEU_OP_ID_ANDBITS, "&", 10, true },
    { FEU_OP_ID_TESTEQUAL, "==", 9, true },
    { FEU_OP_ID_TESTNOTEQUAL, "!=", 9, true },
    { FEU_OP_ID_TESTLESS, "<", 8, true },
    { FEU_OP_ID_TESTLESSEQUAL, "<=", 8, true },
    { FEU_OP_ID_TESTMORE, ">", 8, true },
    { FEU_OP_ID_TESTMOREEQUAL, ">=", 8, true },
    { FEU_OP_ID_SHL, "<<", 7, true },
    { FEU_OP_ID_SHR, ">>", 7, true },
    { FEU_OP_ID_ADD, "+", 6, true },
    { FEU_OP_ID_SUB, "-", 6, true },
    { FEU_OP_ID_MULT, "*", 5, true },
    { FEU_OP_ID_DIV, "/", 5, true },
    { FEU_OP_ID_MOD, "%", 5, true },
    { FEU_OP_ID_INCR, "++", 3, false },
    { FEU_OP_ID_DECR, "--", 3, false },
    { FEU_OP_ID_NOTLOGIC, "!", 3, false },
    { FEU_OP_ID_NOTBITS, "~", 3, false },
    { FEU_OP_ID_LSUBSCRIPT, "[", 2, true },
    { FEU_OP_ID_RSUBSCRIPT, "]", 2, true },
    { FEU_OP_ID_LPAREN, "(", 2, true },
    { FEU_OP_ID_RPAREN, ")", 2, true }
};

FeuCalculable::FeuCalculable(string expression) {
    mIsConstant = true; // May be overridden by tokenizer
    mLastResult = 0.0f; // As good a default as any...
    mRunCount = 0; // No runs yet.
    mOpMap = &feuOperators;
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
                    // Continue accumulating operator
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
    // Walk token list, using the shunting yard algorithm to organize
    // tokens into RPN.  Then, convert each token into a FeuCalcItem.
}

float FeuCalculable::proc() {
    // Shortcut for constants....
    mRunCount++;
    if (mIsConstant && (mRunCount > 1)) {
        return mLastResult;
    }

    // No Shortcut -- actually run it
}

