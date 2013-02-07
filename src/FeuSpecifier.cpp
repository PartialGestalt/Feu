#include "feu_all.h"

FeuSpecifier::FeuSpecifier(std::string objectSpec) {
    size_t dotpos;

    //FeuLog::i("[FeuSpecifier]: decoding \"" + objectSpec + "\".\n");
    dotpos = objectSpec.find_first_of('.');

    mVector = std::vector<std::string>();
    // Special case handling for 'this' references
    if (dotpos == std::string::npos) {
        mIsSelf = true;
        mObject = std::string("this");
        mAttribute = objectSpec;
        mVector.push_back(mObject);
        mVector.push_back(mAttribute);
        return;
    }

    // Normal handling, at least one object component
    mIsSelf = false;
    dotpos = objectSpec.find_last_of('.');
    mObject = objectSpec.substr(0,dotpos);
    splitComponents(objectSpec,&mVector,'.');    
    mAttribute = mVector[mVector.size() - 1];

    return;
}

FeuSpecifier::~FeuSpecifier() {
}

void FeuSpecifier::splitComponents(std::string s,std::vector<std::string> *v, char delimiter) 
{
    std::stringstream ss(s);
    std::string component;
    while (std::getline(ss,component,delimiter)) {
        v->push_back(component);
    }
    return;
}

bool FeuSpecifier::isSelf() {
    return mIsSelf;
}
