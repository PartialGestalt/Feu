#include "feu.h"
#include <iostream>

int main(int argc, char **argv)
{
	FeuThing *ft1,*ft2,*ft3;
    FeuCalculable  *fc;
    float fc_result;

    FeuLog::i("Starting adoption test...\n");

	ft1 = new FeuThing("grandma");
	ft2 = new FeuThing("mommy");
	ft3 = new FeuThing("kiddo");

	ft1->adopt(ft2);
	ft2->adopt(ft3);

	ft2->geneology();
    delete ft1;

    FeuLog::i("Adoption test done\n");
    FeuLog::i("===============================================\n");


    FeuLog::i("Starting calculable test...\n");


    //fc = new FeuCalculable("3+4*2/(1-5)^^2^^3");
    fc = new FeuCalculable("3+4*2/(1-5)");
    fc_result = fc->proc();
    delete fc;

    FeuLog::i("Calculable finished, result is \"" + stringof(fc_result) + "\"\n");
    FeuLog::i("===============================================\n");

}
