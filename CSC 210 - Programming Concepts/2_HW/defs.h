//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: defs.h - global definitions for the drawing program

// margins (in inches) and other constants to make default window size
// correspond to drawable part of paper

#ifndef DEFS_H
#define DEFS_H

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

#endif DEFS_H