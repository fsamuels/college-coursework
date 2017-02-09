//: sxwin_dummy.cpp --	Simple X Window class (dummy implementation
//:                     requiring no interaction with X11)
// Matt Stallmann, 24 Jan 2000

#include "sxwin.h"
#include <iostream.h>
#include <math.h>
#include <string.h>

struct sxwin::HiddenWindowData {
  HiddenWindowData( int x, int y, int width, int height, String title ):
    my_x( x ), my_y( y ), my_width( width ), my_height( height ),
    my_title( title ), my_number( number_of_windows++ ) { }
  ~HiddenWindowData() { --number_of_windows; }
  int my_x;
  int my_y;
  int my_width;
  int my_height;
  String my_title;
  int my_number;
  static int number_of_windows;
};

int sxwin::HiddenWindowData::number_of_windows = 0;

sxwin::sxwin( int x, int y, int width, int height, const String title )
{
  data_ = new HiddenWindowData( x, y, width, height, title );
  cout << "sxwin::sxwin( " << x << ", " << y << ", " << width << ", " <<
    height << ", " << title << " ), my_number = " << data_->my_number << endl;
}

sxwin::~sxwin()
{
  cout << "sxwin::~sxwin(), my_number = " << data_->my_number << endl;
  delete data_;
}

void sxwin::getNextEvent(EventType& type, int& x, int& y, char& c)
{
  cout << "sxwin::getNextEvent(), my_number = " << data_->my_number << endl;
 GetEvent:
  cout << "Menu of event types:" << endl;
  cout << "0. LeftPress" << endl;
  cout << "1. LeftRelease" << endl;
  cout << "2. MiddlePress" << endl;
  cout << "3. MiddleRelease" << endl;
  cout << "4. RightPress" << endl;
  cout << "5. RightRelease" << endl;
  cout << "6. MouseMotion" << endl;
  cout << "7. KeyStroke" << endl;
  cout << "8. WindowRefresh" << endl;
  cout << "EventType = ";

  int event;
  cin >> event; cin.ignore( 100, '\n' );
  if ( event < 0 || event > 8 ) {
    cout << "Bad event number " << event << ", please try again." << endl;
    goto GetEvent;
  }

  type = EventType( event );

  // distinguish mouse events from other events
  if ( 0 <= event && event <= 6 ) { // mouse event
    cout << "Mouse event, x = ";
    cin >> x; cin.ignore( 100, '\n' );
    cout << "             y = ";
    cin >> y; cin.ignore( 100, '\n' );
  }
  else if ( 7 == event ) {      // key stroke
    cout << "Keystroke, char = ";
    cin.get( c );
    if ( '\n' != c ) cin.ignore( 100, '\n' );
  }
}

void sxwin::cursorPosition( int& x, int& y )
{
  cout << "sxwin::cursorPosition(), my_number = " << data_->my_number << endl;
  cout << "x = ";
  cin >> x; cin.ignore( 100, '\n' );
  cout << "y = ";
  cin >> y; cin.ignore( 100, '\n' );
}

bool sxwin::eventPresent()
{
  cout << "sxwin::eventPresent(), my_number = " << data_->my_number << endl;
  cout << "(0 = false, 1 = true)? ";
  int answer;
  cin >> answer; cin.ignore( 100, '\n' );
  return bool( answer );
}

void sxwin::purgeEvents()
{
  cout << "sxwin::purgeEvents(), my_number = " << data_->my_number << endl;
}

void sxwin::mouseTracking(TrackingState track)
{
  cout << "sxwin::mouseTracking( " << track << " ), my_number = " <<
    data_->my_number << endl;
}

void sxwin::clearArea( int x, int y, int width, int height )
{
  cout << "sxwin::clearArea( " << x << ", " << y << ", " << width << ", "
       << height << " ),  my_number = " << data_->my_number << endl;
}

void sxwin::reverseVideo( int x, int y, int width, int height )
{
  cout << "sxwin::reverseVideo( " << x << ", " << y << ", " << width << ", "
       << height << " ),  my_number = " << data_->my_number << endl;
}

int sxwin::windowWidth() const
{
  return data_->my_width;
}

int sxwin::windowHeight() const
{
  return data_->my_height;
}

void sxwin::drawString( int x, int y, const String str )
{
  cout << "sxwin::drawString( " << x << ", " << y << ", " << str
       << " ), my_number = " << data_->my_number << endl;
}

void sxwin::drawChar( int x, int y, char c )
{
  cout << "sxwin::drawChar( " << x << ", " << y << ", " << c 
       << " ), my_number = " << data_->my_number << endl;
}

unsigned int sxwin::fontAscent() const
{
  cout << "sxwin::fontAscent(), my_number = " << data_->my_number << endl;
  cout << "ascent = ";
  unsigned int ascent;
  cin >> ascent; cin.ignore( 100, '\n' );
  return ascent;
}

unsigned int sxwin::fontDescent() const
{
  cout << "sxwin::fontDescent(), my_number = " << data_->my_number << endl;
  cout << "descent = ";
  unsigned int descent;
  cin >> descent; cin.ignore( 100, '\n' );
  return descent;
}

unsigned int sxwin::stringWidth( const String stg ) const
{
  cout << "sxwin::stringWidth( " << stg << " ), my_number = "
       << data_->my_number << endl;
  cout << "width = ";
  unsigned int width;
  cin >> width; cin.ignore( 100, '\n' );
  return width;
}

void sxwin::drawSegment( int x1, int y1, int x2, int y2 )
{
  cout << "sxwin::drawSegment( " << x1 << ", " << y1 << ", " << x2 << ", "
       << y2 << " ), my_number = " << data_->my_number << endl;
}

void sxwin::drawCircle( int x, int y, int radius )
{
  cout << "sxwin::drawCircle( " << x << ", " << y << ", " << radius
       << " ), my_number = " << data_->my_number << endl;
}

void sxwin::moveCursorTo( int x, int y )
{
  cout << "sxwin::moveCursorTo( " << x << ", " << y << " ), my_number = "
       << data_->my_number << endl;
}

void sxwin::beep()
{
  cout << "sxwin::beep(), my_number = " << data_->my_number << endl;
}


