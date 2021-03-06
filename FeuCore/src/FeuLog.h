/*
 * FeuLog.h
 *
 * FeuLog is a catchall class for logging and related utilities
 */

#ifndef _FEU_LOG_H_
#define _FEU_LOG_H_

#include <iostream>
#include <sstream>
#include <climits>


class FeuLog {
public:
	FeuLog();
	virtual ~FeuLog();

public:
    static void d(std::string); // Debug message; may or may not show
    static void d(std::string,std::string); 
    static void d(std::string,std::string,std::string); 
    static void i(const char *file, std::string); // Informational string (stdout)
    static void i(std::string);
    static void i(std::string,std::string);
    static void i(std::string,std::string,std::string);
    static void w(std::string); // Warning notice (stderr)
    static void w(std::string,std::string); 
    static void w(std::string,std::string,std::string);
    static void e(std::string); // Error condition (stderr)
    static void e(std::string,std::string);
    static void e(std::string,std::string,std::string);

};

#define info(__string) FeuLog::i((const char *)__FILE__, __string)

template <typename T> std::string stringof(T t) { std::ostringstream os; os << t; return os.str(); }

static inline double doubleof(std::string s) {
    double fout;
    std::stringstream os;
    os << s;
    os >> fout; 
    return fout; 
}

static inline int charval(char c) {
    if (c >= '0' && c <= '9') return c-'0';
    if (c >= 'a' && c <= 'z') return c-'a' + 10;
    if (c >= 'A' && c <= 'Z') return c-'A' + 10;
    return INT_MAX;
}

// Can't assume C++11 everywhere....
static inline int intof(std::string s) {
    unsigned int i;
    unsigned char ch;
    unsigned int start=0; // First meaningful digit
    unsigned int radix=10; // 2? 10? 16? 8?
    unsigned int digit;
    int accum = 0;

    // Step 1: Determine base
    switch (s[0]) {
        case '#': // HTML-style allowed in XML.
            radix = 16;
            start = 1;
            break;
        case '0':
            // CLEAN: TODO: Validate lengths of the string
            // while using radix prefixes!!
            if (s.size() == 1) {
                return 0;
            }
            // Allow 0x... and 0b...
            switch (ch = s[1]) {
                case 'b': case 'B':
                    // Binary
                    radix = 2;
                    start = 2;
                    break;
                case 'x': case 'X':
                    // Hexadecimal
                    radix = 16;
                    start = 2;
                    break;
                case 'd': case 'D':
                    // Non-standard, but consistent and clear.
                    radix = 10;
                    start = 2;
                    break;
                case '0': case '1': case '2': case '3': 
                case '4': case '5': case '6': case '7':
                    radix = 8;
                    start = 1;
                    break;
                default:
                    FeuLog::e("Can't convert numeric string \"" + s + "\", invalid radix specifier \'",stringof(ch),"\' in input.\n");
                    break;
            }
            break;
        default:
            // Normal decimal...
            radix = 10;
            start = 0;
            break;
    }

    // Step 2: Convert until we finish or hit a bad character.
    for (i=start;i < s.size();i++) {
        digit = charval(s[i]);
        if (digit < radix) {
            accum *= radix;
            accum += digit;
        } else {
            break;
        }
    }

    return accum;
}

#endif /* _FEU_LOG_H_ */
