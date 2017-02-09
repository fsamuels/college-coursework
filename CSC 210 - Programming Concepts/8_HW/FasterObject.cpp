//: FasterObject.cpp
// Forrest Samuels 5.2.00

#include "FasterObject.h"

FasterObject::FasterObject() {}

FasterObject::~FasterObject() {}

char FasterObject::getChar() const {
   return '>';
}

void FasterObject::action(Level& level, Worm& worm) {
    if (level.speed() < _Worm_MaxSpeed)
         level.incrementSpeed();
      level.message("FASTER(>) - Worm speeds up");
      worm.move(WORM_SAME);
}
