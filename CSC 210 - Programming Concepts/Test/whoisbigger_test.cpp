#include <iostream.h>	//for cout
#include "mytemplates.h"	//my template functions

void main() {

int a = 70;
int b = 70;

float c = 70.00;
float d = 83.99;

double e = 69.111;
double f = 87.14159;

char g = 'a';
char h = 'z';

cout << "\ta = " << a << "\n";
cout << "\tb = " << b << "\n";
cout << "whoIsBigger = " << whoIsBigger(a,b) << "\n";
 
cout << "\tc = " << c << "\n"; 
cout << "\td = " << d << "\n"; 
cout << "whoIsBigger = " << whoIsBigger(c,d) << "\n";
                                              
cout << "\te = " << e << "\n";
cout << "\tf = " << f << "\n";
cout << "whoIsBigger = " << whoIsBigger(e,f) << "\n";
          
cout << "\tg = " << g << "\n";
cout << "\th = " << h << "\n";
cout << "whoIsBigger = " << whoIsBigger(g,h) << "\n";

}
