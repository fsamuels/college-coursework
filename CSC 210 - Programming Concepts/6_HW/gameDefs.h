//: gameDefs.h - defines, enums and structs for wormGame
// Chris Church
// cschurch@eos.ncsu.edu, chris@axesoftware.com
// 03/28/2000

#ifndef GAMEDEFS_H
#define GAMEDEFS_H


// Worm 
enum WormDir { WORM_UP, WORM_DOWN, WORM_LEFT, WORM_RIGHT };
enum WormSize { WORM_GROW, WORM_SHRINK, WORM_SAME };
const int MINIMUM_WORM_SIZE = 2;

#define _Worm_DefaultLives              5
#define _Worm_DefaultScore              0
#define _Worm_DefaultSpeed              2
#define _Worm_MinSpeed                  1
#define _Worm_MaxSpeed                  10


// Level
#define GridSize                        10
#define XOffset                         GridSize
#define YOffset                         GridSize * 3
#define _Level_Width                    48
#define _Level_Height                   34
#define _Level_MaxWorms                 2
#define _Level_NumMessages              3

enum LevelObject { NONE, PLUS, MINUS, WALL, GROW, SHRINK, FASTER, SLOWER, DIE };
             		   

// sxwin defines
#define _gameWin_Left                   10
#define _gameWin_Top                    10
#define _gameWin_Width                  500
#define _gameWin_Height                 440
#define _gameWin_Title                  "wormGame"


// GameLoop enum
enum GameState { GAME_INTRO, GAME_PLAY, GAME_RESTART, GAME_QUIT };


#endif
