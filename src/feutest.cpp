#include "feu_all.h"
#include <iostream>

int main(int argc, char **argv)
{
	FeuThing *ft1,*ft2,*ft3;
    FeuCalculable  *fc;
    double fc_result;

    //
    // FileSys.1: Glob test
    //

    {
        std::string *tmpstring;
        FeuGlob *fg;

        FeuLog::i("Glob.1 test starting...\n");

        tmpstring = new std::string("/lv0/inbasket/media/");
        fg = new FeuGlob(*tmpstring);
        delete tmpstring;
        fg->setRecursive(false);
        tmpstring = new std::string("*.jpg");
        fg->addGlob(*tmpstring);
        tmpstring = new std::string("*.gif");
        fg->addGlob(*tmpstring);
        fg->dumpGlob();

        delete fg;
    }

#if 0
    // 
    // Adoption.1: Test basic FeuThing adoption
    //
    FeuLog::i("Adoption.1 test starting...\n");

	ft1 = new FeuThing("grandma");
	ft2 = new FeuThing("mommy");
	ft3 = new FeuThing("kiddo");

	ft1->adopt(ft2);
	ft2->adopt(ft3);

	ft2->geneology();
    delete ft1;

    FeuLog::i("Adoption.1 test done\n");
    FeuLog::i("===============================================\n");
#endif

    // 
    // Calculable.1: Test basic arithmetic
    //

#if 0
    FeuLog::i("Calculable.1 test starting...\n");
    //fc = new FeuCalculable("3+4*2/(1-5)^^2^^3");
    fc = new FeuCalculable("3+4*(2/(1-5) + 4)");
    fc_result = fc->proc();
    delete fc;

    FeuLog::i("Calculable.1 finished, result is \"" + stringof(fc_result) + "\"\n");
    FeuLog::i("===============================================\n");
#endif

    // 
    // Calculable.2: Test radices and logic 
    //
#if 0
    FeuLog::i("Calculable.2 test starting...\n");

    fc = new FeuCalculable("~0xFFFFFFFE + 0x2c + 0b101");
    fc_result = fc->proc();
    delete fc;

    FeuLog::i("Calculable.2 finished, result is \"" + stringof(fc_result) + "\"\n");
    FeuLog::i("===============================================\n");
#endif

    // 
    // Calculable.3: Test special operators
    //

#if 0
    FeuLog::i("Calculable.3 test starting...\n");

    fc = new FeuCalculable("-3/(-2-4)");
    fc_result = fc->proc();
    delete fc;

    FeuLog::i("Calculable.3 finished, result is \"" + stringof(fc_result) + "\"\n");
    FeuLog::i("===============================================\n");
#endif

    // TODO: More operator tests.

    // 
    // Ruleset.1: Load a ruleset
    //

    {
        Feu *feu;
        int i;

        FeuLog::i("Ruleset.1 test starting...\n");

        try {
            feu = new Feu("../presets/ParseTest.feu");
        } catch (FeuException *fe) {
            fe->what();
            delete feu;
            return -1;
        }

        FeuLog::i("Ruleset.1 loaded\n");
        FeuLog::i("===============================================\n");

    // 
    // Ruleset.2: Run a ruleset for some number of frames
    //

        FeuLog::i("Ruleset.2 test starting...\n");


        try {
        feu->runEvent("onLoad");     // Run the "onLoad" handlers
        feu->runEvent("onActivate"); // Run the "onActivate" handlers
        for (i=0;i<10000;i++) {
            feu->run();  // Run a single frame.
        }
        } catch (FeuException *fe) {
            fe->what();
            delete feu;
            return -1;
        }


        FeuLog::i("Ruleset.2 ran 1000 frames\n");
        delete feu;
        FeuLog::i("===============================================\n");
    }
}
