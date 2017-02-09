//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//: buttons.h - functions that access the button region

#ifndef BUTTONS_H
#define BUTTONS_H

void draw_buttons(sxwin& window);
// draw the buttons

void highlight_button(sxwin& window, Mode mode);
// highlight the button corresponding to the given mode

Mode which_button(int x, int y);
// return the mode corresponding to the given button

#endif BUTTONS_H