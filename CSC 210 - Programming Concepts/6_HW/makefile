all: wormDriver wormGame

wormDriver: wormDriver.o Worm.o WormSegment.o sxwin.o String.o
	g++ -o wormDriver wormDriver.o Worm.o WormSegment.o sxwin.o String.o -lX11 -L/usr/X11R6/lib

wormGame: Worm.o WormSegment.o wormGame.o Level.o sxwin.o String.o
	g++ -o wormGame Worm.o WormSegment.o wormGame.o Level.o sxwin.o String.o -lX11 -L/usr/X11R6/lib

wormDriver.o: wormDriver.cpp gameDefs.h Worm.h Worm.cpp sxwin.h sxwin.cpp WormSegment.h WormSegment.cpp String.h String.cpp
	g++ -c wormDriver.cpp

Worm.o: gameDefs.h Worm.h Worm.cpp WormSegment.h WormSegment.cpp sxwin.h sxwin.cpp String.h String.cpp 
	g++ -c Worm.cpp

WormSegment.o: gameDefs.h sxwin.h sxwin.cpp WormSegment.h WormSegment.cpp String.h String.cpp
	g++ -c WormSegment.cpp

wormGame.o: wormGame.cpp sxwin.h sxwin.cpp gameDefs.h Worm.h Worm.cpp Level.h Level.cpp String.h String.cpp WormSegment.h WormSegment.cpp 
	g++ -c wormGame.cpp

sxwin.o: sxwin.h sxwin.cpp String.h String.cpp
	g++ -c sxwin.cpp

String.o: String.h String.cpp
	g++ -c String.cpp

Level.o: Level.h Level.cpp sxwin.h sxwin.cpp gameDefs.h Worm.h Worm.cpp String.h String.cpp WormSegment.h WormSegment.cpp
	g++ -c Level.cpp

clean:
	rm -f *.o wormDriver wormGame
