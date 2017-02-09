//: FasterObject.h
// Forrest Samuels 5.2.00

#ifndef FASTEROBJECT_H
#define FASTEROBJECT_H

#include "Object.h"
#include "Level.h"
#include "Worm.h"
    
class FasterObject: public Object {

public:    
    FasterObject();
    virtual ~FasterObject();
    char getChar() const;
    void action(Level& level, Worm& worm);
};

#endif FASTEROBJECT_H