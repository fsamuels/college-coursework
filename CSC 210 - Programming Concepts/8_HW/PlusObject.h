//: PlusObject.h
// Forrest Samuels 5.2.00

#ifndef PLUSOBJECT_H
#define PLUSOBJECT_H

#include "Object.h"
#include "Level.h"
#include "Worm.h"
    
class PlusObject: public Object {

public:    
    PlusObject();
    virtual ~PlusObject();
    char getChar() const;
    void action(Level& level, Worm& worm);
};

#endif PLUSOBJECT_H

