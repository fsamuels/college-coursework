//: ShrinkObject.h
// Forrest Samuels 5.2.00

#ifndef SHRINKOBJECT_H
#define SHRINKOBJECT_H

#include "Object.h"
#include "Level.h"
#include "Worm.h"
    
class ShrinkObject: public Object {

public:    
    ShrinkObject();
    virtual ~ShrinkObject();
    char getChar() const;
    void action(Level& level, Worm& worm);
};

#endif SHRINKOBJECT_H

