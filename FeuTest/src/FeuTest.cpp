//============================================================================
// Name        : FeuTest.cpp
// Author      : Andrew Kephart
// Version     :
// Copyright   : (c) 2014, Andrew Kephart
// Description : Test harness for Feu; load file given on command line and
//               run for the given interval at the given period
//============================================================================

#include <Feu.h>
//#include <FeuApi.h>
#include <FeuException.h>
#include <FeuLog.h>

int main(int argc, char **argv) {
    std::string *preset;  // Ruleset file to load
    int period;          // milliseconds between frames
    int frames;          // number of frames to simulate
    int i;
    Feu *feu;            // The loaded ruleset

    // Step 0: Process command line
    if (argc < 3) {
        FeuLog::e("Usage: FeuTest <ruleset> <frames> <period_msec>\n");
        return -1; // Bail out
    }
    preset = new std::string(argv[1]);
    frames = intof(argv[2]);
    period = intof(argv[3]);

    // Step 1: Load and initialize
    try {
        feu = new Feu(*preset);
    } catch (FeuException &fe) {
        fe.what();
        return -1;
    }

    // Step 2: Startup events
    try {
        feu->runEvent("onLoad");
        feu->runEvent("onActivate");
    } catch (FeuException &fe) {
        fe.what();
        delete feu;
        return -2;
    }

    // Step 3: Loop on frames
    for (i = 1; i <= frames; i++) {
        // Run main frame
        try {
            FeuLog::i("++++++++++++++++++++++++++++ Starting frame ++++++++++++++++++++++++++++++++++++++++++++++\n");
            feu->run();
        } catch (FeuException &fe) {
            fe.what();
            delete feu;
            return -3;
        }
        // Check timers

    }

    return 0;
}
