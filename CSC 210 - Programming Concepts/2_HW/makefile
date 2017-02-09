# Forrest Samuels
# Febary 9, 2000
# CSC 210, Section 001, Hobson
# This here makefile first worked on 2.8.00 at about 9pm.
# This is the makefile for the 'drawing' and 'drawingTest' programs
# Added -f option to remove to supress errors 2.9.00 @ 12:20pm

all: drawing drawingTest

drawing: drawing.o buttons.o canvas.o sxwin.o String.o
	g++ -o drawing drawing.o buttons.o canvas.o sxwin.o String.o -lX11 -L/usr/X11R6/lib

drawingTest: drawing.o buttons.o canvas.o sxwin_dummy.o String.o
	g++ -o drawingTest drawing.o buttons.o canvas.o sxwin_dummy.o String.o

drawing.o: defs.h buttons.h canvas.h sxwin.h buttons.cpp canvas.cpp sxwin.cpp
	g++ -c drawing.cpp

buttons.o: defs.h buttons.h sxwin.h buttons.cpp sxwin.cpp
	g++ -c buttons.cpp

canvas.o: defs.h canvas.h sxwin.h canvas.cpp sxwin.cpp
	g++ -c canvas.cpp

sxwin.o: sxwin.h sxwin.cpp
	g++ -c sxwin.cpp -I/usr/X11R6/include

String.o: String.h String.cpp
	g++ -c String.cpp

sxwin_dummy.o: sxwin.h sxwin.cpp sxwin_dummy.cpp
	g++ -c sxwin_dummy.cpp

clean:
	rm -f *.o drawing drawingTest
