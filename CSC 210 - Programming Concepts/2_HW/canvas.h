//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: canvas.h - functions that manipulate drawable objects on the canvas


// *********************************************************************
// The following are the access functions for an abstract data type that
// keeps track of the drawing (current implementation does not store any
// previously drawn objects, only enough information to complete the
// drawing of the current object).

#ifndef CANVAS_H
#define CANVAS_H

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

#endif CANVAS_H