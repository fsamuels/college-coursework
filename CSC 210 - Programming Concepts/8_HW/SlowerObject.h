//: SlowerObject.h
// Forrest Samuels 5.2.00

#ifndef SLOWEROBJECT_H
#define SLOWEROBJECT_H

#include "Object.h"
#include "Level.h"
#include "Worm.h"
    
class SlowerObject: public Object {

public:    
    SlowerObject();
    virtual ~SlowerObject();
    char getChar() const;
    void action(Level& level, Worm& worm);
};

#endif SLOWEROBJECT_H

