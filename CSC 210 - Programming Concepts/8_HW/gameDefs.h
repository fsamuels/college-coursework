//: gameDefs.h - defines, enums and structs for wormGame
// Chris Church
// cschurch@eos.ncsu.edu, chris@axesoftware.com
// 03/28/2000

// Modifications
//  21 Apr 2000 - changed #define's to const declarations, added a const
//                for initial worm length; moved some non-global stuff to
//                the appropriate places [MS]

#ifndef GAMEDEFS_H
#define GAMEDEFS_H

// Worm 
//  enums moved to Worm.h (they're not really global - only a Worm client
//  needs to know they exist and they're part of the "contract" between
//  client and implementer of Worm) 
const int _Worm_DefaultLives =              5;
const int _Worm_DefaultScore =              0;
const int _Worm_DefaultSpeed =              2;
const int _Worm_MinSpeed =                  1;
const int _Worm_MaxSpeed =                  10;
const int _Worm_InitialLength =             4;
const int _Worm_MinimumLength =             2;
const int _Worm_Space =                     5; // amount of space to give
                                               // worm initially

// Level
const int GridSize =                        10;
const int XOffset =                         GridSize;
const int YOffset =                         GridSize * 3;
const int _Level_Width =                    48;
const int _Level_Height =                   36;
const int _Level_MaxWorms =                 2;
const int _Level_NumMessages =              10;
const int _Level_TotalTime =                60000;
const int _Level_NumScoreObjects =          20;
const int _Level_NumKillObjects =           4;
const int _Level_NumOtherObjects =          8; // number of objects of each
                                               // other type 

// window dimensions
const int _gameWin_Left =                   10;
const int _gameWin_Top =                    10;
const int _gameWin_Width =                  500;
const int _gameWin_Height =                 600;
const char * const _gameWin_Title =         "wormGame";

// text dimensions
const int _Text_Padding = 5;
const double _Text_LineSpacing = 0.75;

// timing constants
const int _Game_TimeInterval = 10; // time between reactions to keystrokes
const int _Game_SpeedBenchmark = 500; // time between moves at lowest speed

// game state enum (used to communicate between Level and the game)
enum GameState { GAME_INTRO, GAME_PLAY, GAME_RESTART, GAME_QUIT };

#endif
