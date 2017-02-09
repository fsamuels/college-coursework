//: WallObject.h
// Forrest Samuels 5.2.00

#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "Object.h"
#include "Level.h"
#include "Worm.h"
    
class WallObject: public Object {

public:    
    WallObject();
    virtual ~WallObject();
    char getChar() const;
    void action(Level& level, Worm& worm);
};

#endif WALLOBJECT_H

