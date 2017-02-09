//: sxwin.h - simple X Window header file
// Matt Stallmann, ca. 1995 (lots of modifications since)
// 22 Mar 2000 - added code for recognizing the arrow keys (Chris Church)

#ifndef _SXWIN_H
#define _SXWIN_H

#include "String.h"
// NOTE: Some of the sxwin methods call for arguments of class String, a
//       home-grown String class created for pedagogical purposes in
//       1993. Since there is a constructor that converts from 'const
//       char *' to String, ordinary C-strings can be passed to these
//       methods. 


// character codes for non-printing characters available via getNextEvent
const char RETURN     = 13;
const char BACKSPACE  = 8;
const char DELETE     = 127;
const char TAB        = 9;
const char ESC        = 27;
const char UP_ARROW    = 11;
const char DOWN_ARROW  = 10;    // same as newline
const char LEFT_ARROW  = 8;     // same as backspace!
const char RIGHT_ARROW = 12;

enum EventType {
  LeftPress,        // left mouse button has been pressed
  LeftRelease,      // left mouse button has been released
  MiddlePress,      // middle mouse button has been pressed
  MiddleRelease,    // middle mouse button has been released
  RightPress,       // right mouse button has been pressed
  RightRelease,     // right mouse button has been released
  MouseMotion,      // the mouse has moved to location (x,y); generated only
                    //  if mouse motion tracking is turned on
  KeyStroke,        // a key on the keyboard has been pressed (sxwin
                    //  ignores any key that is neither printable
                    //  ASCII nor one of the codes defined above
  WindowRefresh     // a formerly hidden part of the window is now in view
};

enum TrackingState {
  OFF = 0,
  ON = 1
};

class sxwin {
  // private data is hidden behind a generic pointer: this allows data
  // structure to be modified without changing this file (sxwin.h)
  struct  HiddenWindowData;
  HiddenWindowData* data_;

  // don't allow sxwin's to be copied!
  sxwin( const sxwin & );
  sxwin & operator = ( const sxwin & );
public:
  sxwin(int x = 5, int y = 5, int width = 500, int height = 300,
        const String title = "");
  // create a new window with the given width and height at          
  // location (x,y) on the screen; title is the name on the title bar

  ~sxwin();
  // erase this window and clean up storage

  void cursorPosition( int& x, int& y );
  // get current cursor position relative to window origin

  void mouseTracking(TrackingState track = ON);
  // turn mouse motion events on or off (initially they are off)

  void getNextEvent(EventType& type,	// output: event type
                    int& x,     // output: mouse position (x coordinate)
                    int& y,     // output: mouse position (y coordinate)
                    char& c);	  // output: ASCII code of last keystroke
  // return information about the next event on the queue for this window
  // (waits for an event if none is present)

  bool eventPresent();
  // returns true iff an event for this window is present on the queue

  void purgeEvents();
  // remove all events for this window from the event queue

  int  windowWidth() const;
  int  windowHeight() const;
  // return window dimensions

  void clearArea(int x, int y, int width, int height);
  // erase everything in a rectangular area with upper left corner at
  // (x,y) and the given width and height

  void reverseVideo(int x, int y, int width, int height);
  // reverse the color (black/white) of everything in a rectangular area
  // with upper left corner at (x,y) and the given width and height

  void drawString(int x, int y, const String str);
  // write the string of characters str starting at location with
  // baseline height at y and left edge at x

  void drawChar(int x, int y, char c);
  // same as drawString, except only a single character is drawn

  unsigned int fontAscent() const;
  // returns the number of pixels that the tallest character extends above
  //  the baseline

  unsigned int fontDescent() const;
  // returns the number of pixels that the character with the longest "tail"
  //  extends below the baseline

  unsigned int stringWidth(const String stg) const;
  // returns the width of the given string in pixels

  void drawSegment(int x1, int y1, int x2, int y2);
  // draw a line segment from point (x1,y1) to (x2,y2) [inclusive of both
  // endpoints]

  void drawCircle(int x, int y, int radius);
  // draw a circle with center at (x,y) and the given radius

  void moveCursorTo(int x, int y);
  // move the cursor on the screen to location (x,y)

  void beep();
  // cause a "bell" or "beep" to sound at the terminal
  
};

#endif
