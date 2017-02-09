//: PlusObject.cpp
// Forrest Samuels 5.2.00

#include "PlusObject.h"

PlusObject::PlusObject() {}

PlusObject::~PlusObject() {}

char PlusObject::getChar() const {
   return '+';
}

void PlusObject::action(Level& level, Worm& worm) {
    level.changeScore(worm.length() * level.speed() * 10);
    level.message("PLUS(+) - Worm grows and score increases");
    worm.move(WORM_GROW);

}
