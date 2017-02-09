//: GrowObject.cpp
// Forrest Samuels 5.2.00

#ifndef GROWOBJECT_H
#define GROWOBJECT_H

#include "Object.h"
#include "Level.h"
#include "Worm.h" 
    
class GrowObject: public Object {

public:    
    GrowObject();
    virtual ~GrowObject();
    char getChar() const;
    void action(Level& level, Worm& worm);
};

#endif GROWOBJECT_H

