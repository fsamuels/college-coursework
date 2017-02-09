//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: drawing.cpp - a simple drawing program to illustrate finite-state
//                machine design in a graphical user interface
// Matt Stallmann, 12 March 1998

// revision 19 March 1998: put button handling and canvas into separately
// compilable modules and simplified the state versus mode distinction.

// revision 11 January 1999: moved definition of sxwin window to within main()
//                           added window to argument list for functions that
//                           use sxwin
// Suzanne Balik


// the type that is used to define states in the program (MODE_CHANGE if
// mouse is in the button area, WAITING if in the canvas and waiting for a
// left press, DRAWING if an object indicated by the mode is being drawn.

#include "defs.h"
#include "sxwin.h"
#include "buttons.h"
#include "canvas.h"

enum State { MODE_CHANGE, WAITING, DRAWING };

int main()
{
  sxwin window(10, 10, WIDTH, HEIGHT, "DRAWING");

  // determine correct state based on where mouse is initially
  State state = MODE_CHANGE;
  int initial_x = 0;
  int initial_y = 0;
  window.cursorPosition( initial_x, initial_y );
  if ( MODE_CHANGE_BORDER < initial_x ) state = WAITING;
  
  Mode mode = RECTANGLE;

  draw_buttons(window);               // draw buttons for mode changes
  highlight_button(window, RECTANGLE);  // highlight button for initial mode
  window.mouseTracking();       // ensure that mouse motion events are queued
  while ( 1 ) {   // infinite loop - uses return or break to escape
    EventType type;
    int x;
    int y;
    char c;
    window.getNextEvent(type, x, y, c);
    // type, x, y, and c represent the type, mouse position, and character
    // code of the next event (c is only defined in case of a keyboard event)

    switch(state) {
    case MODE_CHANGE:
      if ( MouseMotion == type ) {
        if ( MODE_CHANGE_BORDER < x ) state = WAITING;
      }
      else if ( LeftPress == type ) {
        highlight_button(window, mode); // erase highlighting of previous mode
        mode = which_button(x, y);
        if ( EXIT == mode ) return 0;
        highlight_button(window, mode);
      }
      break;
    case WAITING:
      if ( MouseMotion == type ) {
        if ( MODE_CHANGE_BORDER >= x )
         state = MODE_CHANGE;
      }
      else if ( LeftPress == type ) {
        state = DRAWING;
        starting_point(window, x, y);
      }
      break;
    case DRAWING:
      // error if in button area
      if ( out_of_bounds(mode, x, y) ) window.beep();
      else if ( MouseMotion == type ) {
        show_object(window, mode, x, y);
      }
      else if ( LeftPress == type ) {
        state = WAITING;
        end_object(window, mode, x, y);
      }
      break;
    default:
      cerr << endl << "Bad state " << state << endl;
      abort();
    }
  }
}
