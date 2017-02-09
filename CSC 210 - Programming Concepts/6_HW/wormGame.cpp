//: wormGame.cpp - Control program for sxwin wormGame
// Chris Church (cschurch@eos.ncsu.edu, chris@axesoftware.com)
// 03/29/2000

#include <sys/timeb.h>
#include "sxwin.h"
#include "gameDefs.h"
#include "Worm.h"
#include "Level.h"

void gameIntro(sxwin* myWin);
// Displays an intro screen with instructions and controls and
//   waits for player to press SPACE.

void gameFinish(sxwin* myWin, Level* myLevel);
// Displays a screen with player's final score and waits for
//   player to press SPACE.

GameState gameLoop(sxwin* myWin);
// Plays the game, handles inputs, includes time scaling code so Worm
//   moves at a consistent speed.
// Returns GameState so main will know whether to quit or ask player
//   to play again.

char messageBox(sxwin* myWin, const String m1, const String m2,
                const char validChars[]);
// Displays a message box on the screen with text m1 and m2, and waits
//   for user to press one of the keys listed in validChars[].
// Returns character that user pressed.

void shadowRectangle(sxwin* myWin, int left, int top, int width, int height);
// Displays the diagonal lines and rectangle used for messageBox, 
//   gameIntro, and gameFinish.

bool isInCharList(const char one, const char list[]);
// Returns true is char one exists in list[].


int main()
{
    // New sxwin window for game
    sxwin* gameWin = new sxwin(_gameWin_Left, _gameWin_Top, _gameWin_Width, 
                               _gameWin_Height, _gameWin_Title);
    GameState gs = GAME_INTRO;  // Current state of the game
    
    while (true) {
        switch (gs) {
            case GAME_INTRO:
                gameIntro(gameWin);
                gs = GAME_PLAY;
                break;
            case GAME_QUIT:
                delete gameWin;
                gameWin = NULL;
                return 0;
                break;
            case GAME_PLAY: 
                gs = gameLoop(gameWin);
                break;
            case GAME_RESTART:
                char c = messageBox(gameWin, "Play again?", 
                               "(Y)es or (N)o", "YyNn");
                if (c == 'Y' || c == 'y')
                    gs = GAME_PLAY;
                else 
                    gs = GAME_QUIT;
                break;
        }
    }   
    
    return 1;   // Should never reach this point
}

void gameIntro(sxwin* myWin)
{
    const int wWidth = myWin->windowWidth();    // shorter name for width
    const int wHeight = myWin->windowHeight();  // shorter name for height
    const int bWidth = 460;                     // width of box
    const int bHeight = 360;                    // height of box
    
    EventType type;
    int x;
    int y;
    char c = '\0';
    while (!isInCharList(c, " ")) {

        // calls func to draw rectangle box with shadow
        shadowRectangle(myWin, wWidth / 2 - bWidth / 2, wHeight / 2 - bHeight / 2,
                    bWidth, bHeight);
                    
        String intro[20];
        intro[0] = "*** wormGame ***";
        intro[1] = "CSC 210 Homework 6, Spring 2000";
        intro[3] = "The object of this game is to move the worm";
        intro[4] = "around the level and eat as many of the correct";
        intro[5] = "objects in the level before time expires, without";
        intro[6] = "running into the walls or the worm itself.";
        intro[8] = "Use the arrow keys to move the worm";
        intro[9] = "UP, DOWN, LEFT, and RIGHT.";
        intro[11] = "Press P to pause and Q to quit.";
        intro[13] = "Objects the worm can eat:";
        intro[14] = "+ (Grow, increase score)    G (Grow)  ";
        intro[15] = "- (Shrink, decrease score)  S (Shrink)";
        intro[16] = "> (Move faster)             D (Die)   ";
        intro[17] = "< (Move slower)                       ";
        intro[19] = "Press SPACE to begin playing...";
        for (int i = 0; i < 20; i++)
            myWin->drawString(wWidth / 2 - myWin->stringWidth(intro[i]) / 2, 
                              wHeight / 2 + (i - 9) * 16, intro[i]);
    
        c = '\0';
        type = KeyStroke;
        while (!isInCharList(c, " ") && type != WindowRefresh)
            myWin->getNextEvent(type, x, y, c);
       
        myWin->clearArea(0, 0, myWin->windowWidth(), myWin->windowHeight());
    }
}
    
void gameFinish(sxwin* myWin, Level* myLevel)
{
    const int wWidth = myWin->windowWidth();    // shorter name for width
    const int wHeight = myWin->windowHeight();  // shorter name for height
    const int bWidth = 400;                     // width of box
    const int bHeight = 160;                    // height of box
    
   
    EventType type;
    int x;
    int y;
    char c = '\0';
    while (!isInCharList(c, " ")) {

        // calls func to draw rectangle box with shadow
        shadowRectangle(myWin, wWidth / 2 - bWidth / 2, wHeight / 2 - bHeight / 2,
                    bWidth, bHeight);
                    
        String finish[6];
        if (myLevel->worm().lives > 0)
            finish[0] = "Your Worm completed the level!!!  :-)";
        else
            finish[0] = "Your Worm has run out of lives.  :-(";
        finish[2] = String("Score: ") + 
            String(myLevel->intToString(myLevel->worm().score));
        finish[5] = "Press SPACE to continue...";
        for (int i = 0; i < 6; i++)
            myWin->drawString(wWidth / 2 - myWin->stringWidth(finish[i]) / 2, 
                              wHeight / 2 + (i - 2) * 16, finish[i]);
    
        c = '\0';            
        type = KeyStroke;
        while (!isInCharList(c, " ") && type != WindowRefresh)
            myWin->getNextEvent(type, x, y, c);
       
        myWin->clearArea(0, 0, myWin->windowWidth(), myWin->windowHeight());
    }
}

GameState gameLoop(sxwin* myWin)
{
    timeb* myTime = new timeb();
    ftime(myTime);
    int timeSeed = int((myTime->time % 1000) * 1000 + myTime->millitm);
    srand48(timeSeed);

    GameState gs = GAME_PLAY;
    Level* myLevel = new Level(myWin);
    myLevel->start();
    myLevel->draw();
    
    int prevTime;
    int curTime;
    int wait = 0;    
    
    EventType type;
    int x;
    int y;
    char c;
    
    while (gs == GAME_PLAY) {
        ftime(myTime);
	curTime = int((myTime->time % 1000) * 1000 + myTime->millitm);
	prevTime = curTime;
        type = KeyStroke;
	while (prevTime + 10 > curTime) {
            ftime(myTime);
  	    curTime = int((myTime->time % 1000) * 1000 + myTime->millitm);
   	    if (myWin->eventPresent())
                myWin->getNextEvent(type, x, y, c);
	}
        if (type == WindowRefresh) {
            myWin->clearArea(0, 0, myWin->windowWidth(), myWin->windowHeight());
            myLevel->draw();
        }
        wait += (curTime - prevTime);
        if (wait >= (500 / myLevel->worm().speed)) {
            switch (c) {
                case 'Q': case 'q': case ESC:
                    c = messageBox(myWin, "Do you wish to quit?", 
                                   "(Y)es or (N)o", "YyNn");
                    if (c == 'Y' || c == 'y')
                        gs = GAME_QUIT;
                    else
                        myLevel->draw();
                    break;
                case 'P': case 'p':
                    c = messageBox(myWin, "Game Paused", "Press SPACE to play", "Qq ");
                    myLevel->draw();
                    break;
                case UP_ARROW:
                    myLevel->changeWormDir(WORM_UP);
                    myLevel->decreaseTime(wait);
                    gs = myLevel->checkAndMove();
                    break;
                case DOWN_ARROW:
                    myLevel->changeWormDir(WORM_DOWN);
                    myLevel->decreaseTime(wait);
                    gs = myLevel->checkAndMove();
                    break;
                case LEFT_ARROW:
                    myLevel->changeWormDir(WORM_LEFT);
                    myLevel->decreaseTime(wait);
                    gs = myLevel->checkAndMove();
                    break;
                case RIGHT_ARROW:
                    myLevel->changeWormDir(WORM_RIGHT);
                    myLevel->decreaseTime(wait);
                    gs = myLevel->checkAndMove();
                    break;
                default:
                    myLevel->decreaseTime(wait);
                    gs = myLevel->checkAndMove();
                    break;
            }
            if (gs == GAME_RESTART && myLevel->worm().lives > 0) {
                c = messageBox(myWin, "Worm Died", "Press SPACE to play", "Qq ");
                myLevel->startWorm(4);
                myLevel->draw();
                gs = GAME_PLAY;
            }
            wait = 0;
        }
                    
    }
    gameFinish(myWin, myLevel);
    if (myLevel->timeToGo() <= 0)
        gs = GAME_RESTART;
    return gs;
}

char messageBox(sxwin* myWin, const String m1, const String m2,
                const char validChars[])
{
    const int wWidth = myWin->windowWidth();    // shorter name for width
    const int wHeight = myWin->windowHeight();  // shorter name for height
    const int bWidth = 200;                     // width of box
    const int bHeight = 80;                     // height of box
    
    EventType type; // X11 event
    int x;          // Mouse x
    int y;          // Mouse y
    char c = '\0';  // Input character
    while (!isInCharList(c, validChars)) {

        // calls func to draw rectangle box with shadow
        shadowRectangle(myWin, wWidth / 2 - bWidth / 2, wHeight / 2 - bHeight / 2,
                        bWidth, bHeight);
     
        myWin->drawString(wWidth / 2 - myWin->stringWidth(m1) / 2, 
                         wHeight / 2 - 8, m1);
        myWin->drawString(wWidth / 2 - myWin->stringWidth(m2) / 2, 
                         wHeight / 2 + 16, m2);
                         
        c = '\0';            
        type = KeyStroke;
        while (!isInCharList(c, validChars) && type != WindowRefresh) {
            myWin->getNextEvent(type, x, y, c);
        }
       
        myWin->clearArea(0, 0, myWin->windowWidth(), myWin->windowHeight());
    }
    return c;    
}

void shadowRectangle(sxwin* myWin, int left, int top, int width, int height)
{
    // draws diagonal lines over the screen
    const int diagSpace = 6;
    for (int i = -1 * myWin->windowHeight(); i < myWin->windowWidth();
         i += diagSpace) {
        myWin->drawSegment(i, 0, i + myWin->windowHeight(), 
                           myWin->windowHeight());
    }

    // draws shadow and box
    const int shadow = 6;
    myWin->clearArea(left + shadow, top + shadow, width, height);
    myWin->reverseVideo(left + shadow, top + shadow, width, height);
    myWin->clearArea(left, top, width + 1, height + 1);
    myWin->drawSegment(left, top, left, top + height);
    myWin->drawSegment(left + 1, top + height, left + width - 1, top + height);
    myWin->drawSegment(left + width, top, left + width, top + height);
    myWin->drawSegment(left + 1, top, left + width - 1, top);
}
    
bool isInCharList(const char one, const char list[])
{
    int i = 0;
    while (list[i])
    {
        if (list[i] == one)
            return true;
        i++;
    }
    return false;
}
