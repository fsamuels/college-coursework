// Forrest Samuels
// Worm.cpp
// Everything seems to WORK!!! 4/12/00 @ 2:42.45am
// added clear() function call in deallocate() to clear segment from screen
// made more efficient by moving removeTail() out of each loop in move() to after case
//    10:40pm 4/12/00
// for some reason the worm will pause for a moment when it is 2 long and encounters
//    a '-' or 'S'; too late for me to make that more efficient so that will not happen

#include <fstream.h>
#include "sxwin.h"
#include "gameDefs.h"
#include "WormSegment.h"
#include "Worm.h"

ostream& operator<<(ostream& out, const Worm& w){
  //some of the following code is editied code from the course pack
  WormSegment *temp = w.myHead; //set a temp pointer to the head pointer 
  out << "[";
  while (temp) {    //while pointer is not NULL more "segments" exsist
      out << "(" << temp->myX << "," << temp->myY << ")";   //output myX and myY
      if (temp->myLink)     //if the next link is not the last
        out << ", ";         //output a comma
      temp = temp->myLink;  //set temp pointer to pointer of next "segment"
  }
  out << "]";
  return out;
}

//copy() function is from page 95 in course pack
static WormSegment* copy(WormSegment* p){
    WormSegment* head = 0;
    WormSegment* tail = 0;
    while(p){
        if (!head)
            head = tail = new WormSegment(p->myX, p->myY, 0);
        else {
            tail->myLink = new WormSegment(p->myX, p->myY, 0);
            tail = tail->myLink;
        }
        p = p->myLink;
    }
    return head;
}

//deallocate() function is from page 96 in course pack
static void deallocate(WormSegment* p, sxwin* win_ptr) {
    WormSegment* temp;
    while (p) {
        temp = p;
        p = p->myLink;
        temp->clear(win_ptr);   //clear() function to delete old segment from the screen
        delete temp;
    }
}

//this function actualy came from my head, not and example from the book
static void removeTail(WormSegment* p, sxwin* win_ptr){
     WormSegment* prev = p; //set = to myHead
     WormSegment* curr = p->myLink;  //set = to second node
     
    while(curr->myLink) {     //while the farthest WormSegment from myHead != NULL
        prev = prev->myLink;  //will point to next to last segment
        curr = curr->myLink; //will point to last WormSegment
        
    }
    curr->clear(win_ptr);   //clear() function to delete old segment from the screen
    delete curr;        //deallocate curr (old last WormSegment)
    prev->myLink = 0;   //set new last WormSegment to NULL

}






Worm::Worm(int x, int y, WormDir direction, int length, sxwin* win_ptr) { //constructor
    //Set worm length to length of MINIMUM_WORM_SIZE or greater
    if (length > MINIMUM_WORM_SIZE)
        myLength = length;
    else
        myLength =  MINIMUM_WORM_SIZE;

    myDirection = direction;    //set direction
    myWin_Ptr = win_ptr;        //set sxwin pointer
    myHead = new WormSegment(x, y, 0);   //create the first segment with NULL pointer
    
    myHead->drawHead(myWin_Ptr);

    WormSegment *current = myHead; //set a temp pointer to the head pointer for working
                                    //down the linked list

    for(int z = 2; z <= myLength; z++){
        if (myDirection == WORM_UP)
            current->myLink = new WormSegment(current->myX, current->myY + 1, 0);
            //makes # 2 to myLength for UP
            
        if (myDirection == WORM_DOWN)
            current->myLink = new WormSegment(current->myX, current->myY - 1, 0);
            //makes # 2 to myLength for DOWN
            
        if (myDirection == WORM_LEFT)
            current->myLink = new WormSegment(current->myX + 1, current->myY, 0);
            //makes # 2 to myLength for LEFT
            
        if (myDirection == WORM_RIGHT)
            current->myLink = new WormSegment(current->myX - 1, current->myY, 0);
            //makes # 2 to myLength for RIGHT
            
        current->draw(myWin_Ptr);
        current = current->myLink;  //set current pointer to next object
    }   //end for(int z = 2; z <= myLength; z++)
    
}

Worm::~Worm() { //deconstructor
    deallocate(myHead, myWin_Ptr);
    myHead = 0;       //set to NULL
}

Worm::Worm(const Worm& other) { //copy constructor
    
    myLength = other.myLength;
    myDirection = other.myDirection;   
    myWin_Ptr = other.myWin_Ptr;       
    myHead = copy(other.myHead);
}

Worm& Worm::operator=(const Worm& rhs) {
    if (this != &rhs) {
        myLength = rhs.myLength;
        myDirection = rhs.myDirection;   
        myWin_Ptr = rhs.myWin_Ptr;
        deallocate(myHead, myWin_Ptr);
        myHead = copy(rhs.myHead);
    }

    return *this;
}

void Worm::draw() const {
    WormSegment *temp = myHead; //set a temp pointer to the head pointer 
    temp->drawHead(myWin_Ptr);
    while (temp) {    //while pointer is not NULL more "segments" exsist
        temp->draw(myWin_Ptr);
        temp = temp->myLink;  //set temp pointer to pointer of next "segment"  
    }
}
      
void Worm::move(WormSize size) {
    WormSegment *current = myHead; //set a temp pointer to the head pointer 
    switch(size) {
        //////////////
        case WORM_GROW:
            
            if (myDirection == WORM_UP)
                myHead = new WormSegment(myHead->myX, myHead->myY - 1, myHead);
            
            if (myDirection == WORM_DOWN)
                myHead = new WormSegment(myHead->myX, myHead->myY + 1, myHead);  
                
            if (myDirection == WORM_LEFT)
                 myHead = new WormSegment(myHead->myX - 1, myHead->myY, myHead); 
                 
            if (myDirection == WORM_RIGHT)
                myHead = new WormSegment(myHead->myX + 1, myHead->myY, myHead);  
         
         myLength++;    //length + 1
         break;  //break case WORM_GROW
            
        /////////////////
        case WORM_SHRINK:
        if (myLength > MINIMUM_WORM_SIZE) {
            removeTail(myHead, myWin_Ptr);  // remove the last two
            removeTail(myHead, myWin_Ptr);  // segments of the worm

            if (myDirection == WORM_UP)   
                myHead = new WormSegment(myHead->myX, myHead->myY - 1, myHead);
                                        
            if (myDirection == WORM_DOWN)
                myHead = new WormSegment(myHead->myX, myHead->myY + 1, myHead);  
                                             
            if (myDirection == WORM_LEFT)
                myHead = new WormSegment(myHead->myX - 1, myHead->myY, myHead); 
                                             
            if (myDirection == WORM_RIGHT)
                myHead = new WormSegment(myHead->myX + 1, myHead->myY, myHead);  
         
            myLength--;  //length - 1
         } //end if (myLength > MINIMUM_WORM_SIZE)
            break; //break case WORM_SHRINK
            
        //////////////
        case WORM_SAME:
            removeTail(myHead, myWin_Ptr); //remove last segment
            if (myDirection == WORM_UP)
                myHead = new WormSegment(myHead->myX, myHead->myY - 1, myHead);
                
            if (myDirection ==  WORM_DOWN)
                myHead = new WormSegment(myHead->myX, myHead->myY + 1, myHead);  
                                          
            if (myDirection ==  WORM_LEFT)
                myHead = new WormSegment(myHead->myX - 1, myHead->myY, myHead); 
                    
            if (myDirection ==  WORM_RIGHT)
                myHead = new WormSegment(myHead->myX + 1, myHead->myY, myHead);  
                

         //myLength = myLength; 
         break; //break case WORM_SAME
        }   //end switch(size)
    
    WormSegment *temp = myHead;
    temp->drawHead(myWin_Ptr);    //draw new head
    temp = temp->myLink;          //set temp to next WormSegment
    temp->draw(myWin_Ptr);        //redraw old head position
}   


void Worm::changeDirection(WormDir direction) {
    myDirection = direction;
}
     
int Worm::length() const {
    return myLength;
}
     
WormDir Worm::direction() const {
    return myDirection;
}
    
int Worm::headX() const {
    return myHead->myX;
}

int Worm::headY() const {
    return myHead->myY;
}
   
bool Worm::existsAt(int x, int y) const {
    //code used from operator<<
    WormSegment *temp = myHead; //set a temp pointer to the head pointer 

    while (temp) {    //while pointer is not NULL more "segments" exsist
        if ((temp->myX == x) && (temp->myY == y))    //comapare myX and myY to x and y
            return true;                             //if the same, return true
        temp = temp->myLink;  //set temp pointer to pointer of next "segment"
    }
    return false;
}
