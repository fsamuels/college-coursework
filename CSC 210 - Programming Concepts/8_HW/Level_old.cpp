//: Level_old.cpp - Level class implementation (old version with cosmetic
//:                 changes) 
// Matt Stallmann, 21 Apr 2000 (based on original implementation by Chris
//                              Church) 

#include "Level.h"
#include "sys_utils.h"
#include "gameDefs.h"

// implementations of protected member functions

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
      window->drawChar(x * GridSize + XOffset, 
                       (y + 1) * GridSize + YOffset, 'W');
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
      window->reverseVideo(x * GridSize + XOffset + 1,
                           y * GridSize + YOffset + 1,
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
  s = String("Time: ") + String(timeRemaining / 1000) + String(" s");
  window->drawString(XOffset + GridSize, (YOffset + GridSize) / 2, s);
  s = String("Lives: ") + String(myLives);
  window->drawString(window->windowWidth() / 2 - window->stringWidth(s) / 2, 
                     (YOffset + GridSize) / 2, s);
  s = String("Score: ") + String(myScore);
  window->drawString(GridSize * (_Level_Width - 1) + XOffset - 
                     window->stringWidth(s), (YOffset + GridSize) / 2, s);
}

void
Level::drawMessages()
{
  window->drawText(XOffset, GridSize * (_Level_Height + 0.5) + YOffset, 
                   messages, _Level_NumMessages,
                   _Text_Padding, _Text_LineSpacing );
}

// public functions

Level::Level(sxwin* w): window(w)
{
  start();                            // Start new level
  myLives = _Worm_DefaultLives;
  myScore = _Worm_DefaultScore;
  mySpeed = _Worm_DefaultSpeed;
  draw();
}

Level::~Level()
{
  delete myWorm;
  myWorm = NULL;
}

void
Level::startWorm(int wl)
{
  bool canStartWorm = false;  // Flag for checking for place for new Worm
  int startX;                 // Starting X grid position for Worm
  int startY;                 // Starting Y grid position for Worm
  WormDir startDir;           // Starting Worm direction
    
  while ( ! canStartWorm ) {
    canStartWorm = true;

    // pick random starting position and direction
    startX = myRandomStream.integer( _Level_Width );
    startY = myRandomStream.integer( _Level_Height );
    startDir = WormDir( myRandomStream.integer( 4 ) );
        
    // Checks all grid positions where Worm would be drawn to make sure
    //   nothing exists there, also makes sure _Worm_space positions
    //   ahead of Worm are clear so Worm doesn't run into a WALL or a DIE.
    for ( int i = -_Worm_Space; i < wl && canStartWorm; i++ )
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

  delete myWorm;    // Deletes old Worm if one exists
  myWorm = new Worm(startX, startY, startDir, wl, window);
}

int
Level::lives() const
{
  return myLives;
}

int
Level::speed() const
{
  return mySpeed;
}

int
Level::score() const
{
  return myScore;
}

void
Level::changeWormDir(WormDir wd)
{
  switch (wd) {
  case WORM_UP:
    if (myWorm->direction() == WORM_DOWN)
      wd = WORM_DOWN;
    break;
  case WORM_DOWN:
    if (myWorm->direction() == WORM_UP)
      wd = WORM_UP;
    break;
  case WORM_LEFT:
    if (myWorm->direction() == WORM_RIGHT)
      wd = WORM_RIGHT;
    break;
  case WORM_RIGHT:
    if (myWorm->direction() == WORM_LEFT)
      wd = WORM_LEFT;
    break;
  }
  myWorm->changeDirection(wd);
}

GameState
Level::checkAndMove()
{
  if (timeRemaining <= 0)	// Bails out if time has run out
    return GAME_QUIT;
        
  GameState gs = GAME_PLAY;       // GameState to return
  int newX = myWorm->headX();   // X position of Worm
  int newY = myWorm->headY();   // Y position of Worm
    
  // Find correct new position of Worm
  switch (myWorm->direction()) {
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
    if (myWorm->existsAt(newX, newY)) {
      myLives--;
      message("Worm runs into itself");
      gs = GAME_RESTART;
    } else
      myWorm->move(WORM_SAME);
    break;
  case PLUS:
    myScore += (myWorm->length() * mySpeed * 10);
    message("PLUS(+) - Worm grows and score increases");
    myWorm->move(WORM_GROW);
    break;
  case MINUS:
    myScore -= (myWorm->length() * mySpeed * 10);
    message("MINUS(-) - Worm shrinks and score decreases");
    myWorm->move(WORM_SHRINK);
    break;
  case WALL:
    myLives--;
    message("WALL - Worm dies");
    gs = GAME_RESTART;
    break;
  case GROW:
    message("GROW(G) - Worm grows");
    myWorm->move(WORM_GROW);
    break;
  case SHRINK:
    message("SHRINK(S) - Worm shrinks");
    myWorm->move(WORM_SHRINK);
    break;
  case FASTER:
    if (mySpeed < _Worm_MaxSpeed)
      mySpeed++;
    message("FASTER(>) - Worm speeds up");
    myWorm->move(WORM_SAME);
    break;
  case SLOWER:
    if (mySpeed > _Worm_MinSpeed)
      mySpeed--;
    message("SLOWER(<) - Worm slows down");
    myWorm->move(WORM_SAME);
    break;
  case DIE:
    myLives--;
    message("DIE(D) - Worm dies");
    gs = GAME_RESTART;
    break;
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
            
  myWorm->draw();
}

void
Level::decreaseTime(int ms)
{
  timeRemaining -= ms;    // Decreases time by ms
  if ((timeRemaining + ms) / 1000 != timeRemaining / 1000)
    drawScoreboard();   // If #seconds has changed, update Scoreboard
}
