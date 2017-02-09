//: Object.h
// Forrest Samuels 4.28.00
#ifndef OBJECT_H
#define OBJECT_H

#include "Level.h"
#include "Worm.h"

class Object {

public:

    Object() {}
    
    virtual ~Object() {}

    virtual char getChar() const = 0;

    virtual void action(Level& level, Worm& worm) = 0;

private:


protected:



};
#endif OBJECT_H

