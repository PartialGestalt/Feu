/*
 * FeuThingRandom.cpp
 *
 * Global FeuThing representing the Random superglobal.
 */

#include "feu_all.h"
#include <tinyxml.h>
#include <cstdlib> // For rand() and srand()
#include "FeuThingRandom.h"

// Method handlers
static float feu_random_get(FeuThing *,std::vector<float> *);
static float feu_random_getrange(FeuThing *, std::vector<float> *);
static float feu_random_seed(FeuThing *,std::vector<float> *);

static float feu_random_max = (float)RAND_MAX;

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


static float feu_random_get(FeuThing *feu, std::vector<float> *argv) {
    // Basic get.  Return a value between 0.0 and 1.0, inclusive
    return ((float)rand())/feu_random_max;
}

static float feu_random_seed(FeuThing *feu, std::vector<float> *argv) {
    srand((int)((*argv)[0]));
    return 0.0;
}

static float feu_random_getrange(FeuThing *feu, std::vector<float> *argv) {
    float min=(*argv)[0];
    float max=(*argv)[1];
    float range=max-min;
    float r = feu_random_get(NULL,NULL); // Between 0.0 and 1.0

    return (min + (r * range));
}
