/*
 * FeuGlob.cpp
 */

#include "feu_all.h"
#include <stdlib.h>
#include <fnmatch.h>

FeuGlob::FeuGlob(std::string basedir) {
    mIsRecursive=true; 
    mBaseDir = new std::string(basedir);
}

FeuGlob::~FeuGlob() {
    std::list<std::string *>::iterator i;

    /* Delete all of our entries */
    for (i = mMatches.begin(); i != mMatches.end(); i++) {
        delete *i;
    }
}

void FeuGlob::setRecursive(bool isRecursive) {
    mIsRecursive = isRecursive;
    return;
}

void FeuGlob::clearGlob() {
    std::list<std::string *>::iterator i;
    /* This only clears the files, not the dirs */
    for (i = mMatches.begin(); i != mMatches.end(); i++) {
        delete *i;
    }
    return;
}

int FeuGlob::newGlob(std::string pattern) {
    /* Restart globbing.  Clear and add */
    clearGlob();
    return addGlob(pattern);
}

int FeuGlob::globDir(const char *dir, const char *pattern, FeuGlob *obj) {
    DIR *d;
    struct dirent de;
    struct dirent *de_result;

    /* Open the dir */
    if (NULL == (d = opendir((const char *)dir))) {
        FeuLog::w("Couldn't open dir: " + stringof(dir) + stringof("\n"));
        return 0;
    }

    /* Scan the dir, recursing and matching */
    while ((0 == readdir_r(d,&de,&de_result)) && de_result) {
        if ((DT_DIR == de.d_type) && obj->mIsRecursive && ('.' != de.d_name[0])) {
            char subdir[1024];
            /* Is this a non-dot directory? Recurse! */
            snprintf(subdir,1023,"%s/%s",obj->mBaseDir->c_str(),de.d_name);
            FeuGlob::globDir(subdir,pattern,obj);
        } else {
            /* Not a dir.  Check for match */
            if (!fnmatch(pattern,de.d_name,FNM_PATHNAME|FNM_CASEFOLD)) {
                std::string *match = new std::string(de.d_name);
                /* Match! */
                obj->mMatches.push_back(match);
            }
        }
    }
}

int FeuGlob::addGlob(std::string pattern) {
    FeuGlob::globDir(mBaseDir->c_str(),pattern.c_str(),this);
}

int FeuGlob::dumpGlob() {
    std::list<std::string *>::iterator i;
    for (i = mMatches.begin(); i != mMatches.end(); i++) {
        FeuLog::i("[GLOB]:  " + **i + stringof("\n"));
    }
}
