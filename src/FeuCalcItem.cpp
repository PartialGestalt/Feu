#include "feu_all.h"

FeuCalcItem::FeuCalcItem(FeuCalculable *calc) {
    //FeuLog::i("CONSTRUCT: FeuCalcItem()\n");
    mCalculable = calc;
}

FeuCalcItem::~FeuCalcItem() {
}
