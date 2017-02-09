//: Worm.h - Worm class header file
//  Suzanne Balik, 27 Mar 2000 - based on code by Chris Church
//  21 Apr 2000 - added enums (taken from gameDefs.h) [MS]

#ifndef WORM_H
#define WORM_H

#include <fstream.h>
#include "sxwin.h"
#include "gameDefs.h"
#include "WormSegment.h"

enum WormDir { WORM_UP, WORM_DOWN, WORM_LEFT, WORM_RIGHT };
enum WormSize { WORM_GROW, WORM_SHRINK, WORM_SAME };

class Worm {

friend ostream& operator<<(ostream& out, const Worm& w);
//Arguments: out - output stream
//           w - reference to a Worm object
//Return value - output stream (out)
//Side effect: the Worm's segments are output starting with the head
//             segment in the form (no newline at end):
//
//           [ segment1, ..., segmentk ], where each segment has the
//           form (x,y) giving its coordinates. For example,
//             [(50,50), (51,50), (52,50), (53,50)]

public:
      
   Worm(int x, int y, WormDir direction, int length, sxwin* win_ptr);
   //Arguments: x - x coordinate of head segment
   //           y - y coordinate of head segment
   //           length - number of segments
   //           win_ptr - pointer to sxwin window
   //                    set win_ptr to 0 for debugging purposes so
   //                    that an sxwin window is not required
   //Side effect:  A Worm object is created and drawn on the sxwin
   //              window unless win_ptr is 0
   
   ~Worm();
   //Side effect: The Worm is cleared from the screen and the memory
   //             associated with its segments is deallocated
   
   Worm(const Worm& other);
   //Arguments: other - reference to an "other" Worm object
   //Side effect: Creates a Worm object that is a deep copy of the
   //             "other" Worm object
    
   Worm& operator=(const Worm& rhs);
   //Argument: rhs - reference to the Worm object on the "right-hand side"
   //                of the equal sign in an assignment statement
   //Return value: a reference to "this" Worm object
   //Side effect: "this" object now has a deep copy of the data in the
   //             "rhs" object
   
   void draw() const;
   //Side effect: The Worm's segments are drawn on the window
   
   void move(WormSize size);
  //Argument: size - specifies whether the Worm should grow, shrink,
  //                 or stay the same with this move
  //SideEffect: The Worm is moved on the window by adding and drawing a
  //            new head segment going in the current direction and redrawing
  //            the old head segment. If the Worm is shrinking, the last 2
  //            segments are cleared from the window. If the worm is
  //            staying the same, the last segment is cleared from the
  //            window. A worm with only 2 segments will stay the same if
  //            size == WORM_SHRINK.

   
   void changeDirection(WormDir direction);
   //Argument: direction - the Worm's direction of movement

   int length() const;
   //Return value: the number of segments in the Worm
   
   WormDir direction() const;
   //Return value: the Worm's direction of movement
   
   int headX() const;
   //Return value: the x coordinate of the Worm's head segment
   
   int headY() const;
   //Return value: the y coordinate of the Worm's head segment
   
   bool existsAt(int x, int y) const;
   //Arguments: x - x coordinate
   //           y - y coordinate
   //Return value: true - the coordinate pair of one of the Worm's segments
   //                     is (x,y)
   //              false - none of the Worm's segments exist at the
   //                      at the location (x,y)
   
private:
   WormSegment* myHead;
   int myLength;
   WormDir myDirection;
   sxwin* myWin_Ptr;
};
#endif
   
