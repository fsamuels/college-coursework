//: WormSegment.cpp - Worm Segment class implementation file
//  Suzanne Balik, 22 Mar 2000 - based on code by Chris Church

#include "WormSegment.h"

ostream& operator<<(ostream& out, const WormSegment& ws)
{
  out << '(' << ws.myX << ',' << ws.myY << ')';
  return out;
}


WormSegment::WormSegment(int x, int y, WormSegment* link) : 
             myX(x), myY(y), myLink(link) {}


   
void
WormSegment::clear(sxwin* win_ptr)
{
   if(win_ptr)
       win_ptr->clearArea(myX * GridSize + XOffset, myY * GridSize + YOffset, 
                      GridSize, GridSize);
}


static void drawUpperLeft( sxwin & window, int x, int y, int length )
  // Arguments: window - an sxwin
  //            x, y - coordinates of upper left corner of a square (pixels)
  //            length - length of a side of the square (pixels)
  // Side effect: draws the upper and left sides of the square
{
  window.drawSegment( x, y, x + length - 1, y );
  window.drawSegment( x, y + 1, x, y + length - 1 );
}

static void drawDiagonal( sxwin & window, int x, int y, int length )
  // Arguments: window - an sxwin
  //            x, y - coordinates of upper left corner of a square (pixels)
  //            length - length of a side of the square (pixels)
  // Side effect: draws a diagonal from upper left to lower right of the
  //              square, leaving the upper left pixel alone 
{
  window.drawSegment( x + 1, y + 1, x + length - 1, y + length - 1 );
}

// Note: Each worm segment (other than the head) is drawn as a black square 
//       with the upper and left sides white to ensure that you can always
//       distinguish segments. The head has a diagonal white line starting
//       at the upper left corner.

void
WormSegment::draw(sxwin* win_ptr)
{
  if (win_ptr) {
    clear(win_ptr);
    win_ptr->reverseVideo(myX * GridSize + XOffset, myY * GridSize + YOffset, 
                      GridSize,  GridSize);
    drawUpperLeft( * win_ptr,
                   myX * GridSize + XOffset, myY * GridSize + YOffset,
                   GridSize );
  }
}

void 
WormSegment::drawHead(sxwin* win_ptr)
{  
  if (win_ptr) {
    draw(win_ptr);
    drawDiagonal( * win_ptr,
                  myX * GridSize + XOffset, myY * GridSize + YOffset,
                  GridSize );
  }
}
