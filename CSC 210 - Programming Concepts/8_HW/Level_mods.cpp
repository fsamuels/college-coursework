//: Level_mods.cpp - implementation of Level member functions that may
//:                  require modification if new rules are added
// Matt Stallmann, 26 Apr 2000

#include "Level.h"
#include "Object.h"
#include "PlusObject.h"
#include "MinusObject.h"
#include "GrowObject.h"
#include "ShrinkObject.h"
#include "WallObject.h"
#include "DieObject.h"
#include "FasterObject.h"
#include "SlowerObject.h"
#include "sys_utils.h"
#include "gameDefs.h"

enum LevelObject {
  NONE,
  PLUS,
  MINUS,
  WALL,
  GROW,
  SHRINK,
  FASTER,
  SLOWER,
  DIE
};
             		   
static void randAddObjects(LevelObject type, int n,
                           Object * grid[][ _Level_Height ],
                           Random & rstream)
{
  for (int i = 0; i < n; i++) {
    bool objectAdded = false;   // Flag if LevelObject has been added yet
    int startX;                 // X position for LevelObject
    int startY;                 // Y position for LevelObject
    while (!objectAdded) {
      // pick a random position for the object
      startX = rstream.integer( _Level_Width );
      startY = rstream.integer( _Level_Height );
      
      if (!grid[startX][startY]) { // Adds Object if nothing
        objectAdded = true;        // is in that position
        switch (type){
        case NONE:   break;
        case PLUS:   grid[startX][startY] = new PlusObject();
          break;
        case MINUS:  grid[startX][startY] = new MinusObject();
          break;
        case GROW:   grid[startX][startY] = new GrowObject();
          break;
        case SHRINK: grid[startX][startY] = new ShrinkObject();
          break;
        case FASTER: grid[startX][startY] = new FasterObject();
          break;
        case SLOWER: grid[startX][startY] = new SlowerObject();
          break;
        case DIE:    grid[startX][startY] = new DieObject();
         break;
        default:     break;
        }
      }
    }
  }
}

void
Level::start()
{
  // Adds WALL's around the edge of level grid
  int i = 0;  // Counter for loops
  for (i = 0; i < _Level_Width; i++) {   
    grid[i][0] = new WallObject();
    grid[i][_Level_Height - 1] = new WallObject();
  }
  for (i = 1; i < _Level_Height - 1; i++) {
    grid[0][i] = new WallObject();
    grid[_Level_Width - 1][i] = new WallObject();
  }
  // Fills grid inside WALL's with NULL Object pointers
  for (int j = 1; j < _Level_Width - 1; j++)
    for (int k = 1; k < _Level_Height - 1; k++)
      grid[j][k] = 0;
            
  randAddObjects(PLUS, _Level_NumScoreObjects, grid, myRandomStream);
  randAddObjects(MINUS, _Level_NumScoreObjects, grid, myRandomStream);
  randAddObjects(DIE, _Level_NumKillObjects, grid, myRandomStream);
  randAddObjects(GROW, _Level_NumOtherObjects, grid, myRandomStream);
  randAddObjects(SHRINK, _Level_NumOtherObjects, grid, myRandomStream);
  randAddObjects(FASTER, _Level_NumOtherObjects, grid, myRandomStream);
  randAddObjects(SLOWER, _Level_NumOtherObjects, grid, myRandomStream);
  timeRemaining = _Level_TotalTime;

  startWorm(_Worm_InitialLength); // Randomly places Worm

  // Initial level messages
  message(" ");
  message("  before time runs out!");
  message("Go move your Worm and eat as many of the correct objects");
}
