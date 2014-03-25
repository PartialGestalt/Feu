/*
 * FeuThingRandom.cpp
 *
 * Global FeuThing representing the Random superglobal.
 */

#include <tinyxml.h>
#include <cstdlib> // For rand() and srand()
#include "FeuThingRandom.h"

// Method handlers
static double feu_random_get(FeuThing *,std::vector<double> *);
static double feu_random_getrange(FeuThing *, std::vector<double> *);
static double feu_random_seed(FeuThing *,std::vector<double> *);

static double feu_random_max = (double)RAND_MAX;

// Method table
static feuMethod randomMethods[] = {
    // Name, returnval?, #args, handler
    { "seed", false, 1, feu_random_seed },
    { "get", true, 0, feu_random_get },
    { "getrange", true, 2, feu_random_getrange },
};

FeuThingRandom::FeuThingRandom(Feu *feu, int seed) : FeuThing(feu, (std::string)"Random") {
    int i;
    // Seed the randomizer
    srand(seed);

    // Setup method table
    for (i=0;randomMethods[i].func != NULL; i++) {
        mMethods[randomMethods[i].name] = &randomMethods[i];
    }

    // Other bits
    mType = "internal";
    return;
}

FeuThingRandom::~FeuThingRandom() {
}


static double feu_random_get(FeuThing *feu, std::vector<double> *argv) {
    // Basic get.  Return a value between 0.0 and 1.0, inclusive
    return ((double)rand())/feu_random_max;
}

static double feu_random_seed(FeuThing *feu, std::vector<double> *argv) {
    srand((int)((*argv)[0]));
    return 0.0;
}

static double feu_random_getrange(FeuThing *feu, std::vector<double> *argv) {
    double min=(*argv)[0];
    double max=(*argv)[1];
    double range=max-min;
    double r = feu_random_get(NULL,NULL); // Between 0.0 and 1.0

    return (min + (r * range));
}
