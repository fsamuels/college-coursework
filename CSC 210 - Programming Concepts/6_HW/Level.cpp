//: Level.cpp - Level class implementation
// Chris Church  (cschurch@eos.ncsu.edu, chris@axesoftware.com)
// 03/29/2000

#include "Level.h"

Level::Level(sxwin* w) : window(w)
{
    start();                            // Start new level
    myWorm.lives = _Worm_DefaultLives;  // Set Worm defaults
    myWorm.score = _Worm_DefaultScore;
    myWorm.speed = _Worm_DefaultSpeed;
}


Level::~Level()
{
    delete myWorm.w;
    myWorm.w = NULL;
}

void
Level::start()
{
    // Adds WALL's around the edge of level grid
    int i = 0;  // Counter for loops
    for (i = 0; i < _Level_Width; i++) {   
        grid[i][0] = WALL;
        grid[i][_Level_Height - 1] = WALL;
    }
    for (i = 1; i < _Level_Height - 1; i++) {
        grid[0][i] = WALL;
        grid[_Level_Width - 1][i] = WALL;
    }
    // Fills space inside WALL's with LevelObject NONE
    for (int j = 1; j < _Level_Width - 1; j++)
        for (int k = 1; k < _Level_Height - 1; k++)
            grid[j][k] = NONE;
            
    startWorm(4);               // Randomly places Worm of length 4

    randAddObjects(PLUS, 20);   // Adds 20 PLUS's
    randAddObjects(MINUS, 20);  // Adds 20 MINUS's
    randAddObjects(DIE, 4);     // Adds 4 DIE's
    randAddObjects(GROW, 8);    // Adds 8 GROW's
    randAddObjects(SHRINK, 8);  // Adds 8 SHRINK's
    randAddObjects(FASTER, 8);  // Adds 8 FASTER's
    randAddObjects(SLOWER, 8);  // Adds 8 SLOWER's
    timeRemaining = 60000;      // Time remaining set to 60000ms (60 sec)

    // Initial level messages
    message(" ");
    message("  before time runs out!");
    message("Go move your Worm and eat as many of the correct objects");
}

void
Level::randAddObjects(LevelObject type, int n)
{
    for (int i = 0; i < n; i++) {
        bool objectAdded = false;   // Flag if LevelObject has been added yet
        int startX;                 // X position for LevelObject
        int startY;                 // Y position for LevelObject
        while (!objectAdded) {
            startX = int(drand48() * (_Level_Width - 1));   // Random
            startY = int(drand48() * (_Level_Height - 1));  // X and Y
            if (grid[startX][startY] == NONE) {
                grid[startX][startY] = type;    // Adds LevelObject if nothing
                objectAdded = true;             //   is in that position
            }
        }
    }
}

void
Level::startWorm(int wl)
{
    bool canStartWorm = false;  // Flag for checking for place for new Worm
    int startX;                 // Starting X grid position for Worm
    int startY;                 // Starting Y grid position for Worm
    WormDir startDir;           // Starting Worm direction
    
    while (!canStartWorm) {
        canStartWorm = true;
        startX = int(drand48() * (_Level_Width - 1));   // Randomly picks
        startY = int(drand48() * (_Level_Height - 1));  //   X, Y, and
        startDir = WormDir(drand48() * 3);              //   direction
        
        // Checks all grid positions where Worm would be drawn to make sure
        //   nothing exists there, also makes sure 5 positions ahead of Worm
        //   are clear so Worm doesn't run into a WALL or a DIE.
        for (int i = -5; i < wl; i++) {
            switch (startDir) {
                case WORM_UP:
                    if (grid[startX][startY + i] != NONE)
                        canStartWorm = false;
                    break;
                case WORM_DOWN:
                    if (grid[startX][startY - i] != NONE)
                        canStartWorm = false;
                    break;
                case WORM_LEFT:
                    if (grid[startX + i][startY] != NONE)
                        canStartWorm = false;
                    break;
                case WORM_RIGHT:
                    if (grid[startX - i][startY] != NONE)
                        canStartWorm = false;
                    break;
            }
        }
    }

    if (myWorm.w != NULL)
        delete myWorm.w;    // Deletes old Worm if one exists
    myWorm.w = new Worm(startX, startY, startDir, wl, window);
}

const WormData
Level::worm()
{
    return myWorm;
}

void
Level::changeWormDir(WormDir wd)
{
    switch (wd) {
        case WORM_UP:
            if (myWorm.w->direction() == WORM_DOWN)
                wd = WORM_DOWN;
            break;
        case WORM_DOWN:
            if (myWorm.w->direction() == WORM_UP)
                wd = WORM_UP;
            break;
        case WORM_LEFT:
            if (myWorm.w->direction() == WORM_RIGHT)
                wd = WORM_RIGHT;
            break;
        case WORM_RIGHT:
            if (myWorm.w->direction() == WORM_LEFT)
                wd = WORM_LEFT;
            break;
    }
    myWorm.w->changeDirection(wd);
}

GameState
Level::checkAndMove()
{
    if (timeRemaining <= 0)	// Bails out if time has run out
        return GAME_QUIT;
        
    GameState gs = GAME_PLAY;       // GameState to return
    int newX = myWorm.w->headX();   // X position of Worm
    int newY = myWorm.w->headY();   // Y position of Worm
    
    // Find correct new position of Worm
    switch (myWorm.w->direction()) {
        case WORM_UP:
            newY -= 1;
            break;
        case WORM_DOWN:
            newY += 1;
            break;
        case WORM_LEFT:
            newX -= 1;
            break;
        case WORM_RIGHT:
            newX += 1;
            break;
    }
    
    // Quit if Worm position ever gets outside the grid
    if (newX < 0 || newX > (_Level_Width - 1))
        return GAME_QUIT;
    else if (newY < 0 || newY > (_Level_Height - 1))
        return GAME_QUIT;
    // Check Worm collision with LevelObjects
    switch (grid[newX][newY]) {
        case NONE: default:
            // Check for Worm to collide with itself
            if (myWorm.w->existsAt(newX, newY)) {
                myWorm.lives--;
                message("Worm runs into itself");
                gs = GAME_RESTART;
            } else
                myWorm.w->move(WORM_SAME);
            break;
        case PLUS:
            myWorm.score += (myWorm.w->length() * myWorm.speed * 10);
            message("PLUS(+) - Worm grows and score increases");
            myWorm.w->move(WORM_GROW);
            break;
        case MINUS:
            myWorm.score -= (myWorm.w->length() * myWorm.speed * 10);
            message("MINUS(-) - Worm shrinks and score decreases");
            myWorm.w->move(WORM_SHRINK);
            break;
        case WALL:
            myWorm.lives--;
            message("WALL - Worm dies");
            gs = GAME_RESTART;
            break;
        case GROW:
            message("GROW(G) - Worm grows");
            myWorm.w->move(WORM_GROW);
            break;
        case SHRINK:
            message("SHRINK(S) - Worm shrinks");
            myWorm.w->move(WORM_SHRINK);
            break;
        case FASTER:
            if (myWorm.speed < _Worm_MaxSpeed)
                myWorm.speed++;
            message("FASTER(F) - Worm speeds up");
            myWorm.w->move(WORM_SAME);
            break;
        case SLOWER:
            if (myWorm.speed > _Worm_MinSpeed)
                myWorm.speed--;
            message("SLOWER(S) - Worm slows down");
            myWorm.w->move(WORM_SAME);
            break;
        case DIE:
            myWorm.lives--;
            message("DIE(D) - Worm dies");
            gs = GAME_RESTART;
            break;
    }
    if (grid[newX][newY] != NONE && grid[newX][newY] != WALL) {
        grid[newX][newY] = NONE;    // Erase LevelObject that Worm hit
        drawScoreboard();           // Update Scoreboard
    }
    return gs;
}

void
Level::draw()
{
    const int wWidth = window->windowWidth();     // shorter name for width
    const int wHeight = window->windowHeight();   // shorter name for height
    
    // draws diagonal lines over the screen
    const int diagSpace = 6;
    for (int i = 0; i < wWidth + wHeight; i += diagSpace) {
        window->drawSegment(i, 0, i - wHeight, wHeight);
    }
    
    drawScoreboard();
    drawMessages();

    // Draws all the LevelObjects in grid
    for (int j = 0; j < _Level_Width; j++)
        for (int k = 0; k < _Level_Height; k++)
            drawObject(grid[j][k], j, k);
            
    myWorm.w->draw();
}

void
Level::drawObject(LevelObject type, int x, int y)
{
    window->clearArea(x * GridSize + XOffset, y * GridSize + YOffset,
                      GridSize, GridSize);
    switch (type)
    {
        case NONE: 
            break;
        case PLUS:
            window->drawChar(x * GridSize + XOffset, 
                             (y + 1) * GridSize + YOffset, '+');
            break;
        case MINUS:
            window->drawChar(x * GridSize + XOffset, 
                             (y + 1) * GridSize + YOffset, '-');
            break;
        case WALL:
            window->reverseVideo(x * GridSize + XOffset, y * GridSize + YOffset,
                              GridSize, GridSize);
            break;
        case GROW:
            window->drawChar(x * GridSize + XOffset, 
                             (y + 1) * GridSize + YOffset, 'G');
            break;
        case SHRINK:
            window->drawChar(x * GridSize + XOffset, 
                             (y + 1) * GridSize + YOffset, 'S');
            break;
        case FASTER:
            window->drawChar(x * GridSize + XOffset, 
                             (y + 1) * GridSize + YOffset, '>');
            break;
        case SLOWER:
            window->drawChar(x * GridSize + XOffset, 
                             (y + 1) * GridSize + YOffset, '<');
            break;
        case DIE:
            window->drawChar(x * GridSize + XOffset, 
                             (y + 1) * GridSize + YOffset, 'D');
            break;
        default:
            window->reverseVideo(x * GridSize + XOffset + 1, y * GridSize + YOffset + 1,
                              GridSize - 2, GridSize - 2);
            break;
    }
}

void
Level::drawScoreboard()
{
    String s;
    window->clearArea(XOffset, GridSize / 2, GridSize * _Level_Width, 
                      YOffset - GridSize);
    s = String("Time: ") + String(intToString(timeRemaining / 1000)) + 
        String(" s");
    window->drawString(XOffset + GridSize, (YOffset + GridSize) / 2, s);
    s = String("Lives: ") + String(intToString(myWorm.lives));
    window->drawString(window->windowWidth() / 2 - window->stringWidth(s) / 2, 
                       (YOffset + GridSize) / 2, s);
    s = String("Score: ") + String(intToString(myWorm.score));
    window->drawString(GridSize * (_Level_Width - 1) + XOffset - 
                       window->stringWidth(s), (YOffset + GridSize) / 2, s);
}

void
Level::drawMessages()
{
    window->clearArea(XOffset, GridSize * (_Level_Height + 0.5) + YOffset, 
                      GridSize * _Level_Width, 16 * (_Level_NumMessages) + GridSize);
    for (int i = 0; i < _Level_NumMessages; i++)
        window->drawString(XOffset + GridSize, GridSize * (_Level_Height + 2) + 
                           YOffset + i * 16, messages[i]);
}

void
Level::message(String s)
{
    for (int i = _Level_NumMessages - 1; i > 0; i--)
        messages[i] = messages[i-1];
    messages[0] = s;
    drawMessages();
}

char*
Level::intToString(int n)
{
    ostrstream o;
    if (n < 0) {
        o << '-';
        n *= -1;
    } else if (n == 0) {
        o << '0';
        o << ends;
        return o.str();
    }
    
    int l = int(log10(n));
    for (int i = l; i >= 0; i--) {
        o << char(((n % int(pow(10,i+1))) / int(pow(10,i))) + '0');
    }
    o << ends;
    return o.str();
}

void
Level::decreaseTime(int ms)
{
    timeRemaining -= ms;    // Decreases time by ms
    if ((timeRemaining + ms) / 1000 != timeRemaining / 1000)
        drawScoreboard();   // If #seconds has changed, update Scoreboard
}

const int
Level::timeToGo()
{
    return timeRemaining;
}
