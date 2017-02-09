//: WormSegment.h - Worm Segment class header file
//  Suzanne Balik, 27 Mar 2000 - based on code by Chris Church

#ifndef WORM_SEGMENT_H
#define WORM_SEGMENT_H

#include <fstream.h>
#include "gameDefs.h"
#include "sxwin.h"

class WormSegment {

  friend ostream & operator << ( ostream & out, const WormSegment & ws ); 

public:

   WormSegment(int x, int y, WormSegment* link = 0);
   //Arguments: x - x coordinate of segment
   //           y - y coordinate of segment
   //           link - link to next WormSegment
   //Side effect: creates a new WormSegment
    
   void clear(sxwin* win_ptr);
   //Argument: win_ptr - pointer to sxwin window
   //Side effect: if win_ptr is non-zero, the segment is cleared from the
   //              window 
   //             if win_ptr is 0, nothing is done
   
   void draw(sxwin* win_ptr);
   //Argument: win_ptr - pointer to sxwin window
   //Side effect: if win_ptr is non-zero, the segment is drawn on the window
   //             if win_ptr is 0, nothing is done
   
   void drawHead(sxwin* win_ptr);
   //Argument: win_ptr - pointer to sxwin window
   //Side effect: if win_ptr is non-zero, a head segment is drawn on the window
   //             if win_ptr is 0, nothing is done
   	       
   int myX;
   int myY;
   WormSegment* myLink;
};
#endif




