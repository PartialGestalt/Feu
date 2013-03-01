/*
 * FeuGlob.h
 *
 * FeuGlob is a list of files and/or directories
 * matching a given glob, optionally with recursion.
 */

#ifndef _FEU_GLOB_H_
#define _FEU_GLOB_H_

#include <glob.h>

class FeuGlob {
public:
      FeuGlob(std::string);  /* Init from path */
	 ~FeuGlob();

private:
     bool mIsRecursive; /* Recurse when searching */
     std::string *mBaseDir;
     std::list<std::string *> mDirs;
     std::list<std::string *> mFiles;
     void loadDirs(); /* Generate a recursive dir list */

public:
     void setRecursive(bool isRecursive); 
     int  addGlob(std::string pattern);
     int  newGlob(std::string pattern); /* Replace entries */
     void clearGlob(); /* Clear existing entries */
};

#endif /* _FEU_GLOB_H_ */
