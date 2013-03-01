/*
 * FeuGlob.cpp
 */

#include "feu_all.h"
#include <stdlib.h>

FeuGlob::FeuGlob(std::string basedir) {
    mIsRecursive=true; 
    mBaseDir = new std::string(basedir);
    mDirs.push_back(new std::string(basedir));
    loadDirs();
}

FeuGlob::~FeuGlob() {
    std::list<std::string *>::iterator i;

    /* Delete all of our entries */
    for (i = mDirs.begin(); i != mDirs.end(); i++) {
        delete *i;
    }
    for (i = mFiles.begin(); i != mFiles.end(); i++) {
        delete *i;
    }
}

void FeuGlob::setRecursive(bool isRecursive) {
    std::list<std::string *>::iterator i;

    /* Shortcut check */
    if (isRecursive == mIsRecursive) return;
    mIsRecursive = isRecursive;

    /* Change, wipe out old list */
    for (i = mDirs.begin(); i != mDirs.end(); i++) {
        delete *i;
    }

    /* If recursive, load dirs */
    if (mIsRecursive) {
        loadDirs();
    }

    return;
}

void FeuGlob::clearGlob() {
    std::list<std::string *>::iterator i;
    /* This only clears the files, not the dirs */
    for (i = mFiles.begin(); i != mFiles.end(); i++) {
        delete *i;
    }
    return;
}

int FeuGlob::newGlob(std::string pattern) {
    /* Restart globbing.  Clear and add */
    clearGlob();
    return addGlob(pattern);
}

static char *
buildPattern(
    std::string *base, 
    std::string *dirname, 
    std::string rawpat) 
{
    char *retstr = NULL;
    int retsz = 0;

    /* Get lengths (dirname can be null) */
    if (!base || !rawpat.length()) return NULL;

    retsz += base->length();
    retsz += dirname?dirname->length():0;
    retsz += rawpat.length();

    /* Alloc */
    if (NULL == (retstr = (char *)malloc(retsz+1))) {
        return NULL;
    }

    /* Fill it in */
    memset(retstr,0,retsz+1);
    if (dirname) {
        snprintf(retstr,retsz,"%s/%s/%s",base->c_str(),dirname->c_str(),rawpat.c_str());
    } else {
        snprintf(retstr,retsz,"%s/%s",base->c_str(),rawpat.c_str());
    }

    /* Return it */
    return retstr;
}

int FeuGlob::addGlob(std::string pattern) {
    std::list<std::string *>::iterator i;
    glob_t globby;
    char *fullpattern;
    int matchcount;
    char **namep;

    /* Basedir globbing */
    if (NULL != (fullpattern = buildPattern(mBaseDir,NULL,pattern))) {
        memset(&globby,0,sizeof(globby));
        glob(fullpattern,
             GLOB_MARK|GLOB_NOSORT|GLOB_BRACE,
             NULL,&globby);
        free(fullpattern); 
    } else {
        FeuLog::e("Memory allocation in addGlob()\n");
        return 0; /* Bail */
    }


    /* Rerun glob for each stored dir */
    for (i = mDirs.begin(); i != mDirs.end(); i++ ) {
        if (NULL != (fullpattern = buildPattern(mBaseDir,*i,pattern))) {
            glob(fullpattern,
                 GLOB_MARK|GLOB_NOSORT|GLOB_BRACE|GLOB_APPEND,
                 NULL, &globby);
            free(fullpattern); 
        } else {
            FeuLog::e("Memory allocation in addGlob()\n");
            globfree(&globby);
            return 0; /* Bail */
        }
    }

    /* Transfer anything found to our filelist */
    namep = globby.gl_pathv;
    while (namep && *namep) {
        mFiles.push_back(new std::string(*namep));
        namep++;
    }


    /* Return our total matches */
    matchcount = globby.gl_pathc;

    /* Release the globbins */
    globfree(&globby);

    return matchcount;
}

void FeuGlob::loadDirs() {
}
