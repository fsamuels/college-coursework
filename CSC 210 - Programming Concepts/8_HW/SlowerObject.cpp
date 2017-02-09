//: SlowerObject.cpp
// Forrest Samuels 5.2.00

#include "SlowerObject.h"

SlowerObject::SlowerObject() {}

SlowerObject::~SlowerObject() {}

char SlowerObject::getChar() const {
   return '<';
}

void SlowerObject::action(Level& level, Worm& worm) {
 if (level.speed() > _Worm_MinSpeed)
      level.decrementSpeed();
    level.message("SLOWER(<) - Worm slows down");
    worm.move(WORM_SAME);   
}
