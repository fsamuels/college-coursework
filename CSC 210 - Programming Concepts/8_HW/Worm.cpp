//: Worm.cpp - Worm class implementation file
//  Suzanne Balik, 22 Mar 2000 - based on code by Chris Church

#include "Worm.h"

ostream& operator<<(ostream& out, const Worm& w)
{
   WormSegment* tmp = w.myHead;
   out << '[';
   while (tmp) {
      out << * tmp;
      if (tmp->myLink)
         out << ", ";
      tmp = tmp->myLink;
   }
   out << ']';
   return out;
}


static WormSegment* copy(WormSegment* ws)
{
   WormSegment* head = 0;
   WormSegment* tail = 0;
   
   while (ws) {
      if (!head)
         head = tail = new WormSegment(ws->myX, ws->myY);
      else {
         tail->myLink = new WormSegment(ws->myX, ws->myY);
	 tail = tail->myLink;
      }
      ws = ws->myLink;
   }
   return head;
}


static void deallocate(WormSegment* ws)
{
   WormSegment* tmp;
   while (ws) {
      tmp = ws;
      ws = ws->myLink;
      delete tmp;
   }
}



Worm::Worm(int x, int y, WormDir direction, int length, sxwin* win_ptr) :
           myDirection(direction), myWin_Ptr(win_ptr)
{
   if (length <= _Worm_MinimumLength )
      length = _Worm_MinimumLength;
   myLength = length;
   
   myHead = 0;
   for (int i = length - 1; i >= 0; i--) {
    
      switch (direction) {
            
         case WORM_UP:    myHead = new WormSegment(x, y + i, myHead);
                          break;
         
	 case WORM_DOWN:  myHead = new WormSegment(x, y - i, myHead);
                          break;
            
	 case WORM_LEFT:  myHead = new WormSegment(x + i, y, myHead);
                          break;
         
	 case WORM_RIGHT: myHead = new WormSegment(x - i, y, myHead);
                          break;
      }
   }
   draw();
}


Worm::~Worm()
{
   WormSegment* tmp = myHead;
   while (tmp) {
      tmp->clear(myWin_Ptr);
      tmp = tmp->myLink;
   }
   deallocate(myHead);
   myHead = 0;
}


Worm::Worm(const Worm& other) : myLength(other.myLength),
                                myDirection(other.myDirection),
				myWin_Ptr(other.myWin_Ptr)
				
{
   myHead = copy(other.myHead);
}


Worm&
Worm::operator=(const Worm& rhs)
{
   if (this != &rhs) {
      myLength = rhs.myLength;
      myDirection = rhs.myDirection;
      myWin_Ptr = rhs.myWin_Ptr;
      deallocate(myHead);
      myHead = copy(rhs.myHead);
   }
   return *this;
}
   


void
Worm::draw() const
{        
   WormSegment* tmp = myHead;
   if (tmp) {
      myHead->drawHead(myWin_Ptr);
      tmp = tmp->myLink;
      while (tmp) {
         tmp->draw(myWin_Ptr);
	 tmp = tmp->myLink; 
      }
   }
}


void
Worm::move(WormSize size)
{
   myHead->draw(myWin_Ptr); //Redraw the old head segment so it doesn't look
                           //like a head anymore
   
   switch (myDirection) {  //Add a new head segment going in the right direction
   
      case WORM_UP:   myHead = new WormSegment(myHead->myX, myHead->myY-1, myHead);
                      break;
		     
      case WORM_DOWN: myHead = new WormSegment(myHead->myX, myHead->myY+1, myHead);
                      break;
		      
      case WORM_LEFT: myHead = new WormSegment(myHead->myX-1, myHead->myY, myHead);
                      break; 
		      
      case WORM_RIGHT: myHead = new WormSegment(myHead->myX+1, myHead->myY, myHead);
                       break;
		     
   }
   
   myHead->drawHead(myWin_Ptr);   //Draw the new head segment
   
   switch (size) {
      
      case WORM_GROW: myLength++;   //Leave tail segment there so Worm grows by
                      break;        //one segment
		      
      case WORM_SHRINK: if (myLength > _Worm_MinimumLength) {
                           //Remove the last 2 segments so the Worm shrinks by
			   //one segment
                           WormSegment* tmp = myHead;
			   while (tmp->myLink->myLink->myLink)
			      tmp = tmp->myLink;
			   tmp->myLink->myLink->clear(myWin_Ptr);
			   tmp->myLink->clear(myWin_Ptr);
			   delete tmp->myLink->myLink;
			   tmp->myLink->myLink = 0;
			   delete tmp->myLink;
			   tmp->myLink = 0;
			   myLength--;
			}
			else { //Just remove tail segment so Worm stays the same 
			   WormSegment* tmp = myHead;
			   while (tmp->myLink->myLink)
			      tmp = tmp->myLink;
			   tmp->myLink->clear(myWin_Ptr);
			   delete tmp->myLink;
			   tmp->myLink = 0;
			}
			break;
			
      case WORM_SAME:  //Remove tail segment so Worm stays the same
                       WormSegment* tmp = myHead;
		       while (tmp->myLink->myLink)
		          tmp = tmp->myLink;
		       tmp->myLink->clear(myWin_Ptr);
		       delete tmp->myLink;
		       tmp->myLink = 0;
		       break;
   }
}


void
Worm::changeDirection(WormDir direction)
{
   myDirection = direction;
}


int
Worm::length() const
{
   return myLength;
}


WormDir
Worm::direction() const
{
   return myDirection;
}


int
Worm::headX() const
{
   return myHead->myX;
}


int
Worm::headY() const
{
   return myHead->myY;
}


bool
Worm::existsAt(int x, int y) const
{
   WormSegment* tmp = myHead;
   while (tmp) {
      if (tmp->myX == x && tmp->myY == y)
         return true;
      tmp = tmp->myLink;
   }
   return false;
}


			   
                        
		      
      
      
   
