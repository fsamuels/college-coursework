//: DieObject.h
// Forrest Samuels 5.2.00

#ifndef DIEOBJECT_H
#define DIEOBJECT_H

#include "Object.h"
#include "Level.h"
#include "Worm.h"
    
class DieObject: public Object {

public:    
    DieObject();
    virtual ~DieObject();
    char getChar() const;
    void action(Level& level, Worm& worm);
};

#endif DIEOBJECT_H
