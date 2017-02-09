//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: canvas.cpp - implementation of the abstract data type that keeps
//               track of the drawing on the canvas

// Matt Stallmann, 19 Mar 1998

// REVISION: Suzanne Balik, 11 Jan 1999 - added sxwin& window  as a parameter
// to function definitions and calls as needed

#include <math.h>                // sqrt()
#include "sxwin.h"
#include "defs.h"
#include "canvas.h"


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
