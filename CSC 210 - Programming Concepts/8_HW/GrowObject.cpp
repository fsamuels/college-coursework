//: GrowObject.h
// Forrest Samuels 5.2.00

#include "GrowObject.h"

GrowObject::GrowObject() {}

GrowObject::~GrowObject() {}

char GrowObject::getChar() const {
   return 'G';
}

void GrowObject::action(Level& level, Worm& worm) {
    level.message("GROW(G) - Worm grows");
    worm.move(WORM_GROW);

}

