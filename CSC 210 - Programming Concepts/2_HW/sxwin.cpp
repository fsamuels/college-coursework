//: sxwin.cpp --	Simple X Window class (implementation)
// Matt Stallmann
// 02 Feb 1999 - added exception handling to avoid segmentation fault when
//               display is not available
// Christopher G. Healey
// 15 Apr 1999 - added a cursorPosition method to query current cursor
//               position

#include "sxwin.h"
#include <iostream.h>
#include <math.h>
#include <string.h>

// X11 include files
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <X11/cursorfont.h>	 // file for cursor data

// constant default values for window parameters
const unsigned int BORDER_WIDTH = 5;
const unsigned int LINE_THICKNESS = 0;

// use xfontsel to pick a font you like
const char * const FONT =
 "-bitstream-courier-medium-r-normal-*-16-100-100-*-*-*-*-*";

const unsigned int BELL_DURATION = 5;

// constants for manipulating graphics context
const int ALL_ON = 0xffffffff;
const int ALL_OFF = 0;

// constant for bits selecting default events
const int DEFAULT_EVENTS = OwnerGrabButtonMask | ButtonPressMask |
                           ButtonReleaseMask | KeyPressMask | ExposureMask;

// constants for interpreting mouse events
const int	LEFT = 1;
const int	MIDDLE = 2;
const int	RIGHT = 3;

struct sxwin::HiddenWindowData {
  Display*        display_;       
  Window		      window_;
  GC		          gc_;         // graphics context
  Font            font_;
  unsigned long 	black_;
  unsigned long   white_;
  Cursor		      cursor_;
};

sxwin::sxwin(int x, int y, int width, int height, const String title) {
  int screen;
  XSizeHints hint;

  // create space for hidden data
  data_ = new HiddenWindowData;

  // window settings

  // setup display connection and screen
  data_->display_ = XOpenDisplay("");
  if ( ! data_->display_ ) {
    cerr << "X11 error: unable to open default display." << endl;
    abort();
  }
  screen = DefaultScreen(data_->display_);

  // initialize the values for white & black color
  data_->white_ = WhitePixel(data_->display_, screen);
  data_->black_ = BlackPixel(data_->display_, screen);

  // set up hints to the window manager about position and size
  hint.x = x; hint.y = y;
  hint.width = width; hint.height = height;
  hint.flags = PPosition | PSize;

  // create the main window
  data_->window_ = XCreateSimpleWindow(data_->display_,
                                    DefaultRootWindow(data_->display_),
                                    hint.x, hint.y,
                                    hint.width, hint.height,
                                    BORDER_WIDTH,
                                    data_->black_, data_->white_);

  // give the window a title bar and icon name, and report its size, etc. to
  // other applications
  XSetStandardProperties(data_->display_, data_->window_, PTR(title),
                         PTR(title), None, 0, 0, &hint);

  // select the input conditions that will generate events
  XSelectInput(data_->display_, data_->window_, DEFAULT_EVENTS);

                 // create the default graphics context
  data_->gc_ = XCreateGC(data_->display_, data_->window_, 0, 0);
  XSetState(data_->display_, data_->gc_,
            ALL_ON, ALL_OFF, GXxor,
            data_->black_ ^ data_->white_);
                           // set foreground black, background white, 
                           // drawing function xor (if the same pixel 
                           // is drawn twice, it will be erased),     
                           // and ensure all pixels are black or white
  XSetLineAttributes(data_->display_, data_->gc_, LINE_THICKNESS,
                     LineSolid, CapRound, JoinRound);
                           // set up attributes for lines

  // set up the default font
  data_->font_ = XLoadFont(data_->display_, PTR(FONT));
  XSetFont(data_->display_, data_->gc_, data_->font_);

  // Set up the default cursor (an upper-right pointing arrow)
  data_->cursor_ = XCreateFontCursor(data_->display_, XC_draft_small);
  XDefineCursor(data_->display_, data_->window_, data_->cursor_);

  // display the window (i.e. "map" it)
  XMapRaised(data_->display_, data_->window_);

  // flush the buffer
  XFlush(data_->display_);

  // wait for initial expose event
  {
  EventType etype;
  int   x, y;
  char  c;

  getNextEvent(etype, x, y, c);
  while (etype != WindowRefresh)
    getNextEvent(etype, x, y, c);
  }
}

sxwin::~sxwin()
{
  XFreeCursor(data_->display_, data_->cursor_);
  XFreeGC(data_->display_, data_->gc_);
  XDestroyWindow(data_->display_, data_->window_);
  XCloseDisplay(data_->display_);
  delete data_;
}

void sxwin::getNextEvent(EventType& type, int& x, int& y, char& c) {
  XEvent	eve;

  while (True)
  {
    XWindowEvent(data_->display_, data_->window_, ALL_ON, &eve);
      // return any event eve for this window
    switch (eve.type) {
      case MappingNotify:	// this is a "magic cookie" (don't ask why
                           // it's here, but don't remove it) 
        XRefreshKeyboardMapping((XMappingEvent *) &eve);
        continue;
      case Expose:
        if (eve.xexpose.count == 0) {
          // only pass along the last expose event in a series
          type = WindowRefresh; return;
        }
        continue;
      case ButtonPress:
        x = eve.xbutton.x; y = eve.xbutton.y;
        switch (eve.xbutton.button) {
          case LEFT:
            type = LeftPress; return;
          case MIDDLE:
            type = MiddlePress; return;
          case RIGHT:
            type = RightPress; return;
        }
      case ButtonRelease:
        x = eve.xbutton.x; y = eve.xbutton.y;
        switch (eve.xbutton.button) {
          case LEFT:
            type = LeftRelease; return;
          case MIDDLE:
            type = MiddleRelease; return;
          case RIGHT:
            type = RightRelease; return;
        }
      case MotionNotify:
        x = eve.xmotion.x; y = eve.xmotion.y;
        type = MouseMotion;
        return;
      case KeyPress:
        { char ans[1];			//for XLookupString
          KeySym key;
          XLookupString((XKeyEvent *) &eve, ans, 1, &key, 0);
                    // 1 is the length of buffer 'ans'
                    // 0 is to disable 'Compose Status'
          if (key >= 32 && key <= 126) { // printable ASCII character
            c = ans[0];	// copy the character
            type = KeyStroke;
            return;
          }
          else {  // non-printable characters, limited to the 5 below
            c = 0;
            if (key == XK_Return) c = RETURN;
            else if (key == XK_BackSpace) c = BACKSPACE;
            else if (key == XK_Delete) c = DELETE;
            else if (key == XK_Tab) c = TAB;
            else if (key == XK_Escape) c = ESC;
            if (c != 0) {
              type = KeyStroke;
              return;
            }
          }
        }
      }
   }
}

void sxwin::cursorPosition( int& x, int& y ) {
  Window        child;			// Child window ID
  Window        root;			// Root window ID
  int           root_x, root_y;		// Cursor pos relative to root window
  unsigned int  keys;			// Modifier key state

  XQueryPointer( data_->display_, data_->window_, &root, &child,
                 &root_x, &root_y, &x, &y, &keys );
}

bool sxwin::eventPresent() {
  XEvent eve;
  if (XCheckWindowEvent(data_->display_, data_->window_, ALL_ON, &eve)) {
    XPutBackEvent(data_->display_, &eve);
    return true;
  }
  else return false;
}

void sxwin::purgeEvents() {
  XEvent eve;
  while (XCheckWindowEvent(data_->display_, data_->window_, ALL_ON, &eve));
}

void sxwin::mouseTracking(TrackingState track) {
  if (track)
    XSelectInput(data_->display_, data_->window_,
                 DEFAULT_EVENTS | PointerMotionMask);  
  else
    XSelectInput(data_->display_, data_->window_, DEFAULT_EVENTS);  
}

void sxwin::clearArea(int x,int y,int width,int height) {
  if (width == 0 || height == 0) return; // XClearArea attaches special 
                                         // meaning to 0 width or height
                                         // rectangles                  
  XClearArea(data_->display_, data_->window_, x, y, width, height, 0);
             // last parameter means don't generate expose events
  XFlush(data_->display_);
  return;
}

void sxwin::reverseVideo(int x,int y,int width,int height) {
  // erase everything in a rectangular area with upper left corner at
  // (x,y) and the given width and height
  XFillRectangle(data_->display_, data_->window_, data_->gc_,
                 x, y, width, height);
  XFlush(data_->display_);
}

int sxwin::windowWidth() const
{
  Window          root;
  unsigned int    depth, width, height, bw;
  int x, y;
  XGetGeometry(data_->display_, data_->window_,
               &root, &x, &y, &width, &height, &bw, &depth);
  return width;
}

int sxwin::windowHeight() const
{
  Window          root;
  unsigned int    depth, width, height, bw;
  int x, y;
  XGetGeometry(data_->display_, data_->window_,
               &root, &x, &y, &width, &height, &bw, &depth);
  return height;
}

void sxwin::drawString(int x, int y, const String str) {
  XDrawString(data_->display_, data_->window_, data_->gc_,
              x, y, PTR(str), length(str));
  XFlush(data_->display_);
  return;
}

void sxwin::drawChar(int x,int y,char c)
{
  XDrawString(data_->display_, data_->window_, data_->gc_, x, y, &c, 1);
  XFlush(data_->display_);
  return;
}

unsigned int sxwin::fontAscent() const {
  XFontStruct* fontPtr = XQueryFont(data_->display_, data_->font_);
  int dummy;
  XCharStruct dummyCS;
  int font_ascent;
  XTextExtents(fontPtr, "", 0, &dummy, &font_ascent,
               &dummy, &dummyCS);
  return font_ascent;
}

unsigned int sxwin::fontDescent() const {
  XFontStruct* fontPtr = XQueryFont(data_->display_, data_->font_);
  int dummy;
  XCharStruct dummyCS;
  int font_descent;
  XTextExtents(fontPtr, "", 0, &dummy, &dummy, &font_descent,
               &dummyCS);
  return font_descent;
}

unsigned int sxwin::stringWidth(const String stg) const {
  XFontStruct* fontPtr = XQueryFont(data_->display_, data_->font_);
  return XTextWidth(fontPtr, PTR(stg), length(stg));
}

void sxwin::drawSegment(int x1,int y1,int x2,int y2) {
  XDrawLine(data_->display_, data_->window_, data_->gc_, x1, y1, x2, y2);
  XFlush(data_->display_);
  return;
}

void sxwin::drawCircle(int x, int y, int radius) {
  unsigned int diameter = 2 * radius;
  int upperLeftX = x - radius;  // coordinates of upper left corner of the
  int upperLeftY = y - radius;  // square in which the circle is inscribed
  XDrawArc(data_->display_, data_->window_, data_->gc_, upperLeftX, upperLeftY,
           diameter, diameter,  // width and height of that rectangle
           0, 360 * 64);        // starting and ending angle of the arc
                                // (degrees * 64)
  XFlush(data_->display_);
}

void sxwin::moveCursorTo(int x, int y) {
  XWarpPointer(data_->display_, None, data_->window_, 0, 0, 0, 0, x, y);
  XFlush(data_->display_);
  return;
}

void sxwin::beep() {
  XBell(data_->display_, BELL_DURATION);
  XFlush(data_->display_);
  return;
}


