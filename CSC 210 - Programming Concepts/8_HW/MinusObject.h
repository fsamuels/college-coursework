//: MinusObject.h
// Forrest Samuels 5.2.00

#ifndef MINUSOBJECT_H
#define MINUSOBJECT_H

#include "Object.h"
#include "Level.h"
#include "Worm.h"
    
class MinusObject: public Object {

public:    
    MinusObject();
    virtual ~MinusObject();
    char getChar() const;
    void action(Level& level, Worm& worm);
};

#endif MINUSOBJECT_H

