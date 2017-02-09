#include "str.cpp"
#include "initList.cpp"
#include <iostream.h>

int main() {


/////////////////////////////////test str_length()
cout << "///////////////str_length()" << endl;
char a[100] = "01234567890123456789012345678901234567890123456789";
char a1[30] = "abcdefghijklmnopqrstuvwxyz";
char a2[50] = "DFS3";
char a3[10] = " ";
cout << str_length(a) << " " << a << endl;
cout << str_length(a1) << " " << a1 << endl;
cout << str_length(a2) << " " << a2 << endl;
cout << str_length(a3) << " " << a3 << endl;

cout << endl;
///////////////////////////////test str_reverse()
cout << "///////////////str_reverse()" << endl;
char b[100] = "ABCD";
str_reverse(b);
cout << b << endl;

char c[100] = "0123456789";
str_reverse(c);
cout << c << endl;

cout << endl;
/////////////////////////////////////test str_splice()
cout << "///////////////str_splice()" << endl;
//int z = 5;
char d[50] = "abc";
char e[50] = "123";
cout << "d: " << d << endl;
cout << "e: " << e << endl;
cout << "d before: " << d << endl << "   After: ";
str_splice(d, e, 3);
cout << d << endl;                  
cout << "////this should cause error////" << endl;
str_splice(d, e, 7);

cout << endl;
/////////////////////////////////////test str_remove()
cout << "///////////////str_remove()" << endl;  
char f[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char g[20] = "XYZ";

cout << "f: " << f << endl;
cout << "g: " << g << endl;

str_remove(f,g);
cout << "after:" << endl;
cout << "f: " << f << endl;

cout << endl;


//////////////////////////////////test int_print()
cout << "/////////////////////////test int_print()" << endl;
int h[100] = {1,2,3,4,5,6,7,8,9,0};
int_print(cout,h,10);

///////////////////////////test int_reverse()
cout << endl << "/////////////////////////test int_reverse()" << endl;
int i[50] = {6,7,8};
int_reverse(i,3);
cout << i[0] << i[1] << i[2] << endl;

///////////////////////////////test int_splice()
cout << "//////////////////test int_splice()" << endl;
int length = 5;
int j[50] = {1,2,3,4,5};
int k[50] = {6,7,8};
int_splice(j, k, 0, length, 3);
cout << j[0] << j[1] << j[2] << j[3] << j[4] << j[5] << j[6] << j[7] << endl;
cout << "Length: " << length << endl;

///////////////////////////////test int_remove()
cout << "//////////////////test int_remove()" << endl;
length = 5;
int l[50] = {1,2,3,4,5};
int m[50] = {3,4,1};
int_remove(l,m,length,3);
cout << l[0] << l[1] << l[2] << l[3] << l[4] << l[5] << l[6] << l[7] << endl;
cout << "Length: " << length << endl;

return 0;
}  
    
