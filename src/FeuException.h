/*
 * FeuException.h
 *
 */

#ifndef _FEU_EXCEPTION_H_
#define _FEU_EXCEPTION_H_

#include <exception>
#include <string>

class FeuException : public std::exception {
public:
      FeuException(std::string, std::string) throw();
	 ~FeuException() throw();

private:
     std::string *mReason;
     std::string *mOffender;

public:
     virtual const char *what() const throw();
};

#endif /* _FEU_EXCEPTION_H_ */
