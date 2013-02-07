
#include "feu_all.h"


FeuException::FeuException(std::string reason, std::string offender) throw() : exception() {
    mReason = new std::string(reason);
    mOffender = new std::string(offender);
}

FeuException::~FeuException() throw()  {
    delete mReason;
    delete mOffender;
}

const char *FeuException::what() const throw()  {
    FeuLog::e("EXCEPTION: " + *mReason + " caused by \"" + *mOffender  + "\"\n");
}
