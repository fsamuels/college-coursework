# wormGame makefile

wormGame: wormGame.o Level.o Level_mods.o Worm.o WormSegment.o \
          sxwin.o String.o \
          PlusObject.o MinusObject.o DieObject.o WallObject.o GrowObject.o \
          ShrinkObject.o FasterObject.o SlowerObject.o \
; g++ -o wormGame -lX11 -Wall  wormGame.o Level.o Level_mods.o \
         Worm.o WormSegment.o sxwin.o String.o \
	      PlusObject.o MinusObject.o DieObject.o WallObject.o \
	      GrowObject.o ShrinkObject.o FasterObject.o SlowerObject.o

wormGame.o: wormGame.cpp sxwin.h String.h gameDefs.h Worm.h Level.h \
            sys_utils.h \
; g++ -c -Wall -g wormGame.cpp

Level.o: Level.cpp Level.h Worm.h gameDefs.h sxwin.h String.h sys_utils.h \
         Object.h PlusObject.h MinusObject.h DieObject.h WallObject.h \
         GrowObject.h ShrinkObject.h FasterObject.h SlowerObject.h \
; g++ -c -Wall -g Level.cpp

Level_mods.o: Level_mods.cpp Level.h Worm.h gameDefs.h sxwin.h String.h \
         sys_utils.h Object.h PlusObject.h MinusObject.h DieObject.h \
         WallObject.h GrowObject.h ShrinkObject.h FasterObject.h \
         SlowerObject.h \
; g++ -c -Wall -g Level_mods.cpp

Worm.o: Worm.cpp Worm.h WormSegment.h sxwin.h String.h gameDefs.h \
; g++ -c -Wall -g Worm.cpp

WormSegment.o: WormSegment.cpp WormSegment.h sxwin.h String.h gameDefs.h \
; g++ -c -Wall -g WormSegment.cpp

sxwin.o: sxwin.cpp sxwin.h String.h \
; g++ -c -Wall -g sxwin.cpp

String.o: String.cpp String.h \
; g++ -c -Wall -g String.cpp

PlusObject.o: PlusObject.cpp PlusObject.h Object.h Level.h Worm.h \
; g++ -c -Wall -g PlusObject.cpp

MinusObject.o: MinusObject.cpp MinusObject.h Object.h Level.h Worm.h \
; g++ -c -Wall -g MinusObject.cpp

DieObject.o: DieObject.cpp DieObject.h Object.h Level.h Worm.h \
; g++ -c -Wall -g DieObject.cpp

GrowObject.o: GrowObject.cpp GrowObject.h Object.h Level.h Worm.h \
; g++ -c -Wall -g GrowObject.cpp

ShrinkObject.o: ShrinkObject.cpp ShrinkObject.h Object.h Level.h Worm.h \
; g++ -c -Wall -g ShrinkObject.cpp

FasterObject.o: FasterObject.cpp FasterObject.h Object.h Level.h Worm.h \
; g++ -c -Wall -g FasterObject.cpp

SlowerObject.o: SlowerObject.cpp SlowerObject.h Object.h Level.h Worm.h \
; g++ -c -Wall -g SlowerObject.cpp

WallObject.o: WallObject.cpp WallObject.h Object.h Level.h Worm.h \
; g++ -c -Wall -g WallObject.cpp


clean: \
; rm -f *.o wormGame
