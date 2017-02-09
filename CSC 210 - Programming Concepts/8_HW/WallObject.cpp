//: WallObject.cpp
// Forrest Samuels 5.2.00

#include "WallObject.h"

WallObject::WallObject() {}

WallObject::~WallObject() {}

char WallObject::getChar() const {
   return 'W';
}

void WallObject::action(Level& level, Worm& worm) {
    level.decrementLives();
    level.message("WALL - Worm dies");
}


