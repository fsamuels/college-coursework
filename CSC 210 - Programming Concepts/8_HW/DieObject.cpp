//: DieObject.cpp
// Forrest Samuels 5.2.00

#include "DieObject.h"

DieObject::DieObject() {}

DieObject::~DieObject() {}

char DieObject::getChar() const {
   return 'D';
}

void DieObject::action(Level& level, Worm& worm) {
      level.decrementLives();
      level.message("DIE(D) - Worm dies");
}
