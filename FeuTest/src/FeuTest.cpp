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
	Feu *feu;            // The loaded ruleset


	// Step 0: Process command line
	if (argc < 3) {
		FeuLog::e("Usage: FeuTest <ruleset> <frames> <period_msec>\n");
		return -1; // Bail out
	}
	preset = new std::string(argv[1]);
	frames = intof(argv[2]);
	period = intof(argv[3]);


	try {
		feu = new Feu(*preset);
	} catch (FeuException &fe) {
		fe.what();
		if (NULL != feu) delete feu;
		return -1;
	}



	return 0;
}
