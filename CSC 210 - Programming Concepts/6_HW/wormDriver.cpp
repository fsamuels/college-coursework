//: wormDriver.cpp - Worm class test driver
//  Suzanne Balik, 22 Mar 2000

#include <iostream.h>
#include "Worm.h"
#include "gameDefs.h"

int main() {
Worm leftWorm(50,50,WORM_LEFT,1,0);
cout << "Worm moving LEFT:  " << leftWorm << endl;

Worm rightWorm(50,50,WORM_RIGHT,0,0);
cout << "Worm moving RIGHT: " << rightWorm << endl;

Worm downWorm(50,50,WORM_DOWN,2,0);
cout << "Worm moving DOWN:  " << downWorm << endl;

Worm theWorm(50,50,WORM_UP,6,0);
cout << "Worm moving UP:    " << theWorm << endl;

cout << "Worm Length: " << theWorm.length() << endl;
cout << "Head Position: " << theWorm.headX() << ',' << theWorm.headY() << endl;
cout << "Worm Direction: " << theWorm.direction() << endl;


for (int i = 50; i > 40; i--) {
   if (downWorm.existsAt(50,i))
      cout << "Worm exists at (50," << i << ")" << endl;
   else
      cout << "Worm does not exist at (50," << i << ")" << endl;
}      

theWorm.move(WORM_SAME);
cout << "Length: " << theWorm.length() << " " << theWorm << endl;

theWorm.move(WORM_GROW);
cout << "Length: " << theWorm.length() << " " << theWorm << endl;

/*
for (int i = 0; i < 5; i++) {
   theWorm.move(WORM_SHRINK);
   cout << "Length: " << theWorm.length() << " " << theWorm << endl;
}


theWorm.changeDirection(WORM_LEFT);
cout << "Direction: " << theWorm.direction() << endl;

theWorm.move(WORM_SAME);
cout << "Length: " << theWorm.length() << " " << theWorm << endl;


for (int i = 0; i < 6; i++) {
   theWorm.move(WORM_GROW);
   cout << "Length: " << theWorm.length() << " " << theWorm << endl;
}


cout << "downWorm: " << downWorm << endl;
Worm someWorm(downWorm);
someWorm.move(WORM_GROW);
cout << "someWorm: " << someWorm << endl;
cout << "downWorm: " << downWorm << endl;
someWorm = leftWorm;
cout << "someWorm: " << someWorm << endl;
*/

}
