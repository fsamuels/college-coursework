//: Level.h - Level class header file (changed from Chris Church's
//:           implementation to allow code reuse)
// Matt Stallmann, 21 Apr 2000
//
// Suzanne Balik, 24 Apr 2000 - changed grid to array of Object pointers
//                              removed LevelObject argument from 
//                              drawObject function
//                              added incrementSpeed(), decrementSpeed(), 
//                              decrementLives(),
//                              and changeScore() functions 
// Suzanne Balik, 25 Apr 2000 - changed to include <sys/types.h> and
//                              <sys/time.h> instead of <sys/timeb.h> c

#ifndef LEVEL_H
#define LEVEL_H

#include <stdlib.h>
#include <math.h>
#include <strstream.h>
#include "sxwin.h"
#include "gameDefs.h"
#include "Worm.h"
#include "sys_utils.h"

class Object;

class Level {

public:

  Level(sxwin* w);
  ~Level();

  void startWorm(int wl);
  // Creates a new worm of length wl  with a random direction
  //   and position, checks to make sure no level objects exist
  //   where myWorm is to be created.

  // Functions that return info relevant to the game
  int lives() const;
  int speed() const;
  int score() const;

  void changeWormDir(WormDir wd);
  // Changes myWorm's current direction but only if wd is not 
  //   opposite of myWorm.w's direction.

  GameState checkAndMove();

  void draw();
  // Draws the Level and all LevelObjects, myWorm, Scoreboard,
  //   and Messages.

  void decreaseTime(int ms);
  // Decreases timeRemaining by ms.
    
  void incrementSpeed();
  // Increments speed
    
  void decrementSpeed();
  // Decrements speed
    
  void decrementLives();
  // Decrements lives
    
  void changeScore(int amount);
  // Changes score by amount
    
  void message(String s);
  // Adds a new message to the front of the array of scrolling 
  //   messages, removes the oldest message, and draws the messages.

  int timeToGo() const;
  // Returns timeRemaining.

protected:
  sxwin* window;                // Ptr to game window
  int timeRemaining;            // Milliseconds remaining
  String messages[_Level_NumMessages]; // Array of game messages
  Worm * myWorm;                // The Worm
  Random myRandomStream;        // random number stream
  Object* grid[_Level_Width][_Level_Height]; // Level grid

  void start();
  // Starts a new level with WALLs around the sides, and then
  //   adds a Worm using startWorm(4) and LevelObjects using
  //   randAddObjects().

  void drawObject(int x, int y);
  // Draws an Object at grid position (x,y)

  void drawScoreboard();
  // Displays the scoreboard above the level, which displays time 
  //   remaining, lives, and score.

  void drawMessages();
  // Displays the scrolling messages below the level.

private:
  int mySpeed;
  int myScore;
  int myLives;
};

#endif
