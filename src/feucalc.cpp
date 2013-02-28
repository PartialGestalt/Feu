#include "feu_all.h"
#include <iostream>

int main(int argc, char **argv)
{
    FeuCalculable  *fc;
    double fc_result;
    std::string  *expr;

    if (argc < 2) {
        FeuLog::e("Usage: feucalc <expression>\n");
        return -1;
    }

    expr = new std::string(argv[1]);
    FeuLog::i("Calculating result of expression: \""+*expr+"\"\n");

    fc = new FeuCalculable(NULL,*expr);

    fc_result = fc->proc();

    FeuLog::i("============================================================\n","Result is: \"" + stringof(fc_result) + "\"\n");
}
