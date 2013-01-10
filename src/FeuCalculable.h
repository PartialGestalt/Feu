/*
 * FeuCalculable.h
 *
 * FeuCalculable is a base class for calculable
 * strings, for our internal arithmetic.  It encompasses
 * a raw string, a list of preparsed tokens, and whatever
 * other support is needed for running a calculation.
 *
 */

#ifndef _FEU_CALCULABLE_H_
#define _FEU_CALCULABLE_H_


#include "feu.h"
#include <stack>
#include <list>
#include "FeuCalcItem.h"

using namespace std;


// Operator table
struct feuOpInfo {
    int id;                   // ID of the operator
    string op;                // String representation
    int precedence;           // Precedence
    bool leftAssociative;     // true for left-associative
    int (*func)(FeuStack *);  // Implementation; return 0 on success
};

extern struct feuOpInfo feuOpInfoTable[];

// Enumeration of *known* operators.  The set of 
// *supported* operators is defined in the implementation file.
// An operator is supported iff a handler func is defined for it.
enum {
    FEU_OP_ID_COMMA = 0,
    FEU_OP_ID_ASSIGN,
    FEU_OP_ID_ADDASSIGN,
    FEU_OP_ID_SUBASSIGN,
    FEU_OP_ID_MULTASSIGN,
    FEU_OP_ID_DIVASSIGN,
    FEU_OP_ID_MODASSIGN,
    FEU_OP_ID_SHLASSIGN,
    FEU_OP_ID_SHRASSIGN,
    FEU_OP_ID_ANDASSIGN,
    FEU_OP_ID_XORASSIGN,
    FEU_OP_ID_ORASSIGN,
    FEU_OP_ID_ORLOGIC,
    FEU_OP_ID_ANDLOGIC,
    FEU_OP_ID_ORBITS,
    FEU_OP_ID_XORBITS,
    FEU_OP_ID_ANDBITS,
    FEU_OP_ID_TESTEQUAL,
    FEU_OP_ID_TESTNOTEQUAL,
    FEU_OP_ID_TESTLESS,
    FEU_OP_ID_TESTLESSEQUAL,
    FEU_OP_ID_TESTMORE,
    FEU_OP_ID_TESTMOREEQUAL,
    FEU_OP_ID_SHL,
    FEU_OP_ID_SHR,
    FEU_OP_ID_ADD,
    FEU_OP_ID_SUB,   /* The "subtraction" operator, "a-b" */
    FEU_OP_ID_MULT,
    FEU_OP_ID_DIV,
    FEU_OP_ID_MOD,
    FEU_OP_ID_EXPONENT,
    FEU_OP_ID_INCR,
    FEU_OP_ID_DECR,
    FEU_OP_ID_NOTLOGIC,
    FEU_OP_ID_NOTBITS,
    FEU_OP_ID_UNARYMINUS,  /* The "negative" operator "-a" */
    FEU_OP_ID_LSUBSCRIPT,
    FEU_OP_ID_RSUBSCRIPT,
    FEU_OP_ID_LPAREN,
    FEU_OP_ID_RPAREN,
    FEU_OP_ID_FAILURE // Reserved for the failure case object
}; 

enum {
    FEU_TOKEN_NONE, // Undefined state
    FEU_TOKEN_NUM,  // Processing a number
    FEU_TOKEN_OP,   // Processing an operator
    FEU_TOKEN_REF   // Processing an object reference
};

// Operator precedence as a static table
typedef map<string,int> feuOpMap;
const feuOpMap::value_type feuOpTable[] = {
    feuOpMap::value_type(",",FEU_OP_ID_COMMA),
    feuOpMap::value_type("=",FEU_OP_ID_ASSIGN),
    feuOpMap::value_type("+=",FEU_OP_ID_ADDASSIGN),
    feuOpMap::value_type("-=",FEU_OP_ID_SUBASSIGN),
    feuOpMap::value_type("*=",FEU_OP_ID_MULTASSIGN),
    feuOpMap::value_type("/=",FEU_OP_ID_DIVASSIGN),
    feuOpMap::value_type("%=",FEU_OP_ID_MODASSIGN),
    feuOpMap::value_type("<<=",FEU_OP_ID_SHLASSIGN),
    feuOpMap::value_type(">>=",FEU_OP_ID_SHRASSIGN),
    feuOpMap::value_type("&=",FEU_OP_ID_ANDASSIGN),
    feuOpMap::value_type("^=",FEU_OP_ID_XORASSIGN),
    feuOpMap::value_type("|=",FEU_OP_ID_ORASSIGN),
    feuOpMap::value_type("||",FEU_OP_ID_ORLOGIC),
    feuOpMap::value_type("&&",FEU_OP_ID_ANDLOGIC),
    feuOpMap::value_type("|",FEU_OP_ID_ORBITS),
    feuOpMap::value_type("^",FEU_OP_ID_XORBITS),
    feuOpMap::value_type("&",FEU_OP_ID_ANDBITS),
    feuOpMap::value_type("==",FEU_OP_ID_TESTEQUAL),
    feuOpMap::value_type("!=",FEU_OP_ID_TESTNOTEQUAL),
    feuOpMap::value_type("<",FEU_OP_ID_TESTLESS),
    feuOpMap::value_type("<=",FEU_OP_ID_TESTLESSEQUAL),
    feuOpMap::value_type(">",FEU_OP_ID_TESTMORE),
    feuOpMap::value_type(">=",FEU_OP_ID_TESTMOREEQUAL),
    feuOpMap::value_type("<<",FEU_OP_ID_SHL),
    feuOpMap::value_type(">>",FEU_OP_ID_SHR),
    feuOpMap::value_type("+",FEU_OP_ID_ADD),
    feuOpMap::value_type("-",FEU_OP_ID_SUB),
    feuOpMap::value_type("*",FEU_OP_ID_MULT),
    feuOpMap::value_type("/",FEU_OP_ID_DIV),
    feuOpMap::value_type("%",FEU_OP_ID_MOD),
    feuOpMap::value_type("^^",FEU_OP_ID_EXPONENT),
    feuOpMap::value_type("++",FEU_OP_ID_INCR),
    feuOpMap::value_type("--",FEU_OP_ID_DECR),
    feuOpMap::value_type("!",FEU_OP_ID_NOTLOGIC),
    feuOpMap::value_type("~",FEU_OP_ID_NOTBITS),
    // No entry for unary minus, since it would overload SUB 
    //feuOpMap::value_type("-",FEU_OP_ID_UNARYMINUS),
    feuOpMap::value_type("[",FEU_OP_ID_LSUBSCRIPT),
    feuOpMap::value_type("]",FEU_OP_ID_RSUBSCRIPT),
    feuOpMap::value_type("(",FEU_OP_ID_LPAREN),
    feuOpMap::value_type(")",FEU_OP_ID_RPAREN)
};

static int feuOpCount = sizeof(feuOpTable)/sizeof(feuOpTable[0]);
static feuOpMap feuOperators(feuOpTable, feuOpTable+feuOpCount);

class FeuCalculable  {
public:
    FeuCalculable(string);
	~FeuCalculable();

private:
    bool mIsConstant; // No extern references, simplifies.
    float mLastResult;  // Last calculation result
    FeuList *mRPN; // Our RPN list of calcitems
    list<string *>mTokens; // List of fundamental tokens
    FeuStack mCalcStack; // Stack for calculations
    int mRunCount;

public:
	float proc(); // Run the calculation, return the result

private:
    feuOpMap *mOpMap;

private:
    void tokenize(string); // Tokenize/syntax check
    void rpn();  // Convert infix to RPN
};

#endif /* _FEU_CALCULABLE_H_ */
