#include "feu.h"
#include <iostream>

int main(int argc, char **argv)
{
	FeuThing *ft1,*ft2,*ft3;
    FeuCalculable  *fc;
    float fc_result;

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

    // 
    // Calculable.1: Test basic arithmetic
    //

    FeuLog::i("Calculable.1 test starting...\n");
    //fc = new FeuCalculable("3+4*2/(1-5)^^2^^3");
    fc = new FeuCalculable("3+4*(2/(1-5) + 4)");
    fc_result = fc->proc();
    delete fc;

    FeuLog::i("Calculable.1 finished, result is \"" + stringof(fc_result) + "\"\n");
    FeuLog::i("===============================================\n");

    // 
    // Calculable.2: Test hexadecimal and logic 
    //

    FeuLog::i("Calculable.2 test starting...\n");

    fc = new FeuCalculable("~0x3A + 0x2c");
    fc_result = fc->proc();
    delete fc;

    FeuLog::i("Calculable.2 finished, result is \"" + stringof(fc_result) + "\"\n");
    FeuLog::i("===============================================\n");

}
