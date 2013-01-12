/*
 * FeuSpecifier.h
 *
 * FeuSpecifier is a base class for referencing an obkject or
 * attribute.
 */

#ifndef FEUSPECIFIER_H_
#define FEUSPECIFIER_H_


class FeuSpecifier {
public:
	FeuSpecifier(std::string objectSpec);
	~FeuSpecifier();

public:
    std::vector<std::string> mVector;
    std::string mObject;
    std::string mAttribute;

private:
    static void splitComponents(std::string, std::vector<std::string> v, char delim);

};



#endif /* FEUSPECIFIER_H_ */
