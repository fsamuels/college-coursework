//: MinusObject.cpp
// Forrest Samuels 5.2.00

#include "MinusObject.h"

MinusObject::MinusObject() {}

MinusObject::~MinusObject() {}

char MinusObject::getChar() const {
   return '-';
}

void MinusObject::action(Level& level, Worm& worm) {
    level.changeScore(worm.length() * level.speed() * -10);
    level.message("MINUS(-) - Worm shrinks and score decreases");
    worm.move(WORM_SHRINK);
}
