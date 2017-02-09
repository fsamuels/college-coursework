#include <iostream.h>	//for cout
#include "mytemplates.h"	//my template functions

void main() {

int a = 70;
int b = 83;

float c = 70.00;
float d = 83.99;

double e = 69.111;
double f = 87.14159;

cout << "\ta = " << a << "\n";
cout << "\tb = " << b << "\n";
cout << "average = " << average(a,b) << "\n";
 
cout << "\tc = " << c << "\n"; 
cout << "\td = " << d << "\n"; 
cout << "average = " << average(c,d) << "\n";
                                              
cout << "\te = " << e << "\n";
cout << "\tf = " << f << "\n";
cout << "average = " << average(e,f) << "\n";
                                              
}
