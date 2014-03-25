/*
 * FeuSpecifier.h
 *
 * FeuSpecifier is a base class for referencing an obkject or
 * attribute.
 */

#ifndef _FEU_SPECIFIER_H_
#define _FEU_SPECIFIER_H_

#include <string>
#include <vector>


class FeuSpecifier {
public:
	FeuSpecifier(std::string objectSpec);
	~FeuSpecifier();

public:
    std::vector<std::string> mVector;
    std::string mObject;
    std::string mAttribute;
    bool mIsSelf;

private:
    static void splitComponents(std::string, std::vector<std::string> *v, char delim);
    
public:
    bool isSelf(); // This this specifier a "self" reference?

};



#endif /* _FEU_SPECIFIER_H_ */
