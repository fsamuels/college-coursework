//: BigFile.cpp - a simple drawing program to illustrate finite-state
//                machine design in a graphical user interface
// Matt Stallmann, 12 March 1998

// revision 19 March 1998: put button handling and canvas into separately
// compilable modules and simplified the state versus mode distinction.

// revision 11 January 1999: moved definition of sxwin window to within main()
//                           added window to argument list for functions that
//                           use sxwin
// Suzanne Balik
//
// revision 23 August 1999: included code for defs.h, canvas.h, buttons.h,
//                          canvas.cpp, buttons.cpp for Homework 2 so students
//                          could break it into separate modules again
// Suzanne Balik
//
// revision 28 January 2000: changed "const XXX = " definitions to 
//                           "const int XXX = "  so that it would compile 
//                           using gcc295
// Suzanne Balik
//
// revision 31 Jan 2000: changed main program so that State would be
//                       initialized correctly based on the initial
//                       position of the mouse
// Matt Stallmann 

#include<assert.h>              // assert() macro

#include"sxwin.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: defs.h - global definitions for the drawing program

// margins (in inches) and other constants to make default window size
// correspond to drawable part of paper

const float PAPER_WIDTH = 8.5;
const float PAPER_HEIGHT = 11.0;
const float LEFT_MARGIN = 1.0;
const float RIGHT_MARGIN = 1.5;
const float TOP_MARGIN = 1.0;
const float BOTTOM_MARGIN = 1.0;
const int PIXELS_PER_INCH = 72;

// the type that is used to define modes in the program
enum Mode { RECTANGLE, CIRCLE, LINE, EXIT };

// ***********************************************************************
// The following constants define a 100x200 region on the right side of the
// window consisting of 4 squares. The three top squares correspond to
// modes, while the bottom one is for exiting the program.

const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 100;
const int MODE_CHANGE_BORDER = BUTTON_WIDTH;
const int RECTANGLE_MODE_BORDER = BUTTON_HEIGHT;
const int CIRCLE_MODE_BORDER = RECTANGLE_MODE_BORDER + BUTTON_HEIGHT;
const int LINE_MODE_BORDER = CIRCLE_MODE_BORDER + BUTTON_HEIGHT;

// position and content of the messages in the squares
const int RECTANGLE_TEXT_X = 10;
const int RECTANGLE_TEXT_Y = BUTTON_HEIGHT / 2;
const char * const RECTANGLE_TEXT = "Rectangle";
const int CIRCLE_TEXT_X = 10;
const int CIRCLE_TEXT_Y = RECTANGLE_TEXT_Y + BUTTON_HEIGHT;
const char * const CIRCLE_TEXT = "Circle";
const int LINE_TEXT_X = 10;
const int LINE_TEXT_Y = CIRCLE_TEXT_Y + BUTTON_HEIGHT;
const char * const LINE_TEXT = "Line";
const int EXIT_TEXT_X = 10;
const int EXIT_TEXT_Y = LINE_TEXT_Y + BUTTON_HEIGHT;
const char * const EXIT_TEXT = "Exit";

// dimensions of the drawing program window
const int WIDTH = BUTTON_WIDTH + int((PAPER_WIDTH - LEFT_MARGIN - RIGHT_MARGIN)
                                 * PIXELS_PER_INCH);
const int HEIGHT = int((PAPER_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN) *
                   PIXELS_PER_INCH);

// size of the cross hatch used to mark the beginning of a drawing in the
// canvas 
const int CROSS_SIZE = 3;



//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: buttons.h - functions that access the button region



void draw_buttons(sxwin& window);
// draw the buttons

void highlight_button(sxwin& window, Mode mode);
// highlight the button corresponding to the given mode

Mode which_button(int x, int y);
// return the mode corresponding to the given button


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: canvas.h - functions that manipulate drawable objects on the canvas


// *********************************************************************
// The following are the access functions for an abstract data type that
// keeps track of the drawing (current implementation does not store any
// previously drawn objects, only enough information to complete the
// drawing of the current object).



void starting_point(sxwin& window, int x, int y);
// use (x, y) as the "starting point" for the current object (center of a
// rectangle or circle, beginning of a line segment) and draw a cross-hatch
// there

void show_object(sxwin& window, Mode mode, int x, int y);
// show what an object "started" at the most recent starting point would
// look like if another point was at (x, y); also erase the previously shown
// object of that mode (if mode is RECTANGLE, the current point defines a
// corner; if CIRCLE, a point on the circumference; if LINE, the endpoint).

void end_object(sxwin& window, Mode mode, int x, int y);
// draw an object of the given mode "started" at the most recent starting
// point with one point (corner for RECTANGLE, circumference for CIRCLE,
// end for LINE) at (x, y); erase the cross hatch and the most recently shown
// object of that mode

bool out_of_bounds(Mode mode, int x, int y);
// return true iff the object specified by mode would extend beyond the
// borders of the canvas if "started" at the most recent starting point
// and extended to (x, y)




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



//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: buttons.cpp - implementation of functions related to buttons


#include<assert.h>              // assert() macro



void draw_buttons(sxwin& window)
{
  window.clearArea(0, 0, BUTTON_WIDTH, 4 * BUTTON_HEIGHT);
  window.drawSegment(MODE_CHANGE_BORDER, 0, MODE_CHANGE_BORDER, HEIGHT);
  window.drawSegment(0, RECTANGLE_MODE_BORDER, MODE_CHANGE_BORDER,
                     RECTANGLE_MODE_BORDER);
  window.drawSegment(0, CIRCLE_MODE_BORDER, MODE_CHANGE_BORDER,
                     CIRCLE_MODE_BORDER);
  window.drawSegment(0, LINE_MODE_BORDER, MODE_CHANGE_BORDER,
                     LINE_MODE_BORDER);
  window.drawString(RECTANGLE_TEXT_X, RECTANGLE_TEXT_Y, RECTANGLE_TEXT);
  window.drawString(CIRCLE_TEXT_X, CIRCLE_TEXT_Y, CIRCLE_TEXT);
  window.drawString(LINE_TEXT_X, LINE_TEXT_Y, LINE_TEXT);
  window.drawString(EXIT_TEXT_X, EXIT_TEXT_Y, EXIT_TEXT);
}

void highlight_button(sxwin& window, Mode mode)
{
  switch (mode) {
  case RECTANGLE:
    window.reverseVideo(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
    break;
  case CIRCLE:
    window.reverseVideo(0, RECTANGLE_MODE_BORDER + 1,
                        BUTTON_WIDTH, BUTTON_HEIGHT - 1);
    break;
  case LINE:
    window.reverseVideo(0, CIRCLE_MODE_BORDER + 1,
                        BUTTON_WIDTH, BUTTON_HEIGHT - 1);
    break;
  default: cerr << endl << "highlight_button: Bad mode " << mode << endl;
    abort();
  }
}

Mode which_button(int x, int y)
{
  assert( MODE_CHANGE_BORDER >= x );
  if ( RECTANGLE_MODE_BORDER >= y ) return RECTANGLE;
  if ( CIRCLE_MODE_BORDER >= y ) return CIRCLE;
  if ( LINE_MODE_BORDER >= y ) return LINE;
  return EXIT;
}


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: canvas.cpp - implementation of the abstract data type that keeps
//               track of the drawing on the canvas

// Matt Stallmann, 19 Mar 1998

// REVISION: Suzanne Balik, 11 Jan 1999 - added sxwin& window  as a parameter
// to function definitions and calls as needed

#include<math.h>                // sqrt()



static int start_x = -1;        // coordinates of starting point
static int start_y = -1;
static int previous_x = -1;     // coordinates of previous point
static int previous_y = -1;

static inline int distance(int x1, int y1, int x2, int y2)
// distance from (x1, y1) to (x2, y2) expressed as an integer
{
  int xdiff = x1 - x2; int ydiff = y1 - y2;
  return int(sqrt(double(xdiff * xdiff + ydiff * ydiff)));
}

static void draw_crosshatch(sxwin& window, int x, int y)
// draw a cross hatch centered on (x,y)
{
  window.drawSegment(x - CROSS_SIZE, y, x + CROSS_SIZE, y);
  window.drawSegment(x, y - CROSS_SIZE, x, y + CROSS_SIZE);
}

void starting_point(sxwin& window, int x, int y)
{
  start_x = previous_x = x;
  start_y = previous_y = y;
  draw_crosshatch(window, x, y);
}

static void draw_rectangle(sxwin& window, int center_x, int center_y,
                           int corner_x, int corner_y)
// draw a rectangle with the given center and corner (note: this method
// leaves the four corners white
{
  int other_corner_x = 2 * center_x - corner_x;
  int other_corner_y = 2 * center_y - corner_y;
  window.drawSegment(corner_x, corner_y, other_corner_x, corner_y);
  window.drawSegment(other_corner_x, corner_y,
                     other_corner_x, other_corner_y);
  window.drawSegment(other_corner_x, other_corner_y,
                     corner_x, other_corner_y);
  window.drawSegment(corner_x, other_corner_y, corner_x, corner_y);
}

static void show_rectangle(sxwin& window, int x, int y)
{
  draw_rectangle(window, start_x, start_y, previous_x, previous_y);
  draw_rectangle(window, start_x, start_y, x, y);
  previous_x = x; previous_y = y;
}

static void draw_circle(sxwin& window, int center_x, int center_y, int x, int y)
// draw a circle centered at (center_x, center_y) with (x, y) on the
// circumference
{
  int radius = distance(center_x, center_y, x, y);
  window.drawCircle(center_x, center_y, radius);
}
 
static void show_circle(sxwin& window, int x, int y)
{
  draw_circle(window, start_x, start_y, previous_x, previous_y);
  draw_circle(window, start_x, start_y, x, y);
  previous_x = x; previous_y = y;
}

static void show_line(sxwin& window, int x, int y)
{
  window.drawSegment(start_x, start_y, previous_x, previous_y);
  window.drawSegment(start_x, start_y, x, y);
  previous_x = x; previous_y = y;
}

static void end_rectangle(sxwin& window, int x, int y)
{
  draw_rectangle(window, start_x, start_y, previous_x, previous_y);
  draw_rectangle(window, start_x, start_y, x, y);
  draw_crosshatch(window, start_x, start_y);
  previous_x = start_x = -1; previous_y = start_y = -1;
}

static void end_circle(sxwin& window, int x, int y)
{
  draw_circle(window, start_x, start_y, previous_x, previous_y);
  draw_circle(window, start_x, start_y, x, y);
  draw_crosshatch(window, start_x, start_y);
  previous_x = start_x = -1; previous_y = start_y = -1;
}

static void end_line(sxwin& window, int x, int y)
{
  window.drawSegment(start_x, start_y, previous_x, previous_y);
  window.drawSegment(start_x, start_y, x, y);
  draw_crosshatch(window, start_x, start_y);
  previous_x = start_x = -1; previous_y = start_y = -1;
}

void show_object(sxwin& window, Mode mode, int x, int y)
{
  switch ( mode ) {
  case RECTANGLE: show_rectangle(window, x, y); break;
  case CIRCLE: show_circle(window, x, y); break;
  case LINE: show_line(window, x, y); break;
  default: cerr << endl << "show_object: Bad mode " << mode << endl;
    abort();
  }
}

void end_object(sxwin& window, Mode mode, int x, int y)
{
  switch ( mode ) {
  case RECTANGLE: end_rectangle(window, x, y); break;
  case CIRCLE: end_circle(window, x, y); break;
  case LINE: end_line(window, x, y); break;
  default: cerr << endl << "end_object: Bad mode " << mode << endl;
    abort();
  }
}

bool out_of_bounds(Mode mode, int x, int y)
{
  if ( MODE_CHANGE_BORDER >= x ) return true;
  int left_side = 2 * start_x - x;
  if ( RECTANGLE == mode && MODE_CHANGE_BORDER >= left_side ) return true;
  int radius = distance(start_x, start_y, x, y);
  if ( CIRCLE == mode && MODE_CHANGE_BORDER >= start_x - radius ) return true;
  return false;
}
