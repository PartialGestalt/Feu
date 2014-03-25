/*
 * FeuGlob.h
 *
 * FeuGlob is a list of files and/or directories
 * matching a given glob, optionally with recursion.
 */

#ifndef _FEU_GLOB_H_
#define _FEU_GLOB_H_

#include <list>
#include <string>

class FeuGlob {
public:
      FeuGlob(std::string);  /* Init from path */
	 ~FeuGlob();

private:
     bool mIsRecursive; /* Recurse when searching */
     std::string *mBaseDir;
     static int globDir(const char *dir, const char *pattern, FeuGlob *obj);

public:
     std::list<std::string *> mMatches;

public:
     void setRecursive(bool isRecursive); 
     int  addGlob(std::string pattern);
     int  newGlob(std::string pattern); /* Replace entries */
     void clearGlob(); /* Clear existing entries */
     void dumpGlob();
};

#endif /* _FEU_GLOB_H_ */
