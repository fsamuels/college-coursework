//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: buttons.cpp - implementation of functions related to buttons


#include <assert.h>              // assert() macro
#include "sxwin.h"
#include "defs.h"
#include "buttons.h"   


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
