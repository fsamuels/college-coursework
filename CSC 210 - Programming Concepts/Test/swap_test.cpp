#include <iostream.h>	//for cout
#include "mytemplates.h"	//swap template function

void main() {

int a = 11;
int b = 99;

float c = 11.11;
float d = 99.99;

double e = 11.111;
double f = 99.999;

char g = 'g';
char h = 'h';

cout << "Before:" << "\n";
cout << "\ta = " << a << "\n";
cout << "\tb = " << b << "\n"; 
cout << "\tc = " << c << "\n"; 
cout << "\td = " << d << "\n"; 
cout << "\te = " << e << "\n"; 
cout << "\tf = " << f << "\n";
cout << "\tg = " << g << "\n"; 
cout << "\th = " << h << "\n"; 


swap(a,b);
swap(c,d);
swap(e,f);
swap(g,h);

cout << "\n";
cout << "After:" << "\n";
cout << "\ta = " << a << "\n";
cout << "\tb = " << b << "\n";
cout << "\tc = " << c << "\n";
cout << "\td = " << d << "\n";
cout << "\te = " << e << "\n";
cout << "\tf = " << f << "\n";     
cout << "\tg = " << g << "\n";
cout << "\th = " << h << "\n";

}
