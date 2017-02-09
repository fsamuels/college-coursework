//: ShrinkObject.cpp
// Forrest Samuels 5.2.00

#include "ShrinkObject.h"

ShrinkObject::ShrinkObject() {}

ShrinkObject::~ShrinkObject() {}

char ShrinkObject::getChar() const {
   return 'S';
}

void ShrinkObject::action(Level& level, Worm& worm) {
    level.message("SHRINK(S) - Worm shrinks");
    worm.move(WORM_SHRINK);

}
