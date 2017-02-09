//: Level.h - Level class header file
// Chris Church (cschurch@eos.ncsu.edu, chris@axesoftware.com)
// 03/29/2000

#include <stdlib.h>
#include <math.h>
#include <sys/timeb.h>
#include <strstream.h>
#include "sxwin.h"
#include "gameDefs.h"
#include "Worm.h"


#ifndef LEVEL_H
#define LEVEL_H

// Info about the Worm
struct WormData {
    Worm* w; 
    int lives;
    int score;
    int speed;
};

class Level {

public:

    Level(sxwin* w);
    ~Level();

    void start();
    // Starts a new level with WALLs around the sides, and then
    //   adds a Worm using startWorm(4) and LevelObjects using
    //   randAddObjects().

    void randAddObjects(LevelObject type, int n);
    // Randomly places n LevelObjects of type into the Level, and
    //   verifies that nothing exists at each grid position before
    //   placing a LevelObject there.

    void startWorm(int wl);
    // Creates a new myWorm.w of length wl  with a random direction
    //   and position, checks to make sure no level objects exist
    //   where myWorm.w is to be created.

    const WormData worm();
    // Returns a struct of type WormData containing myWorm's info

    void changeWormDir(WormDir wd);
    // Changes myWorm.w's current direction but only if wd is not 
    //   opposite of myWorm.w's direction.

    GameState checkAndMove();

    void draw();
    // Draws the Level and all LevelObjects, myWorm.w, Scoreboard,
    //   and Messages.

    void drawObject(LevelObject type, int x, int y);
    // Draws a LevelObject of type at grid position (x,y)

    void drawScoreboard();
    // Displays the scoreboard above the level, which displays time 
    //   remaining, lives, and score.

    void drawMessages();
    // Displays the scrolling messages below the level.

    void message(String s);
    // Adds a new message to the front of the array of scrolling 
    //   messages, removes the oldest message, and draws the messages.

    char* intToString(int n);
    // Converts any integer n to a character array, used for outputting
    //   numbers to the scoreboard.
    // Returns a ptr to an array of characters representing n.

    void decreaseTime(int ms);
    // Decreases timeRemaining by ms.

    const int timeToGo();
    // Returns timeRemaining.

private:
    
    sxwin* window;                                  // Ptr to game window
    int timeRemaining;                              // Milliseconds remaining
    String messages[_Level_NumMessages];            // Array of game messages
    WormData myWorm;                                // The Worm
    LevelObject grid[_Level_Width][_Level_Height];  // Level grid

};

#endif
