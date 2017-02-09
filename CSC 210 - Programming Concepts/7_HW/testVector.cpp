//: testVector.cpp - test program for the Vector class
// Matt Stallmann, 06 Apr 2000

#include"Vector.h"
#include<iostream.h>

void message()
{
  cout <<
    "Command syntax"
       << endl <<
    "(v is 0 or 1, i is a positive int, and x is a real number):"
       << endl <<
    "  > v i x       | set i-th item of vector v to x"
       << endl <<
    "  < v i         | get the i-th item of vector v"
       << endl <<
    "  +             | print the sum of vector 0 and vector 1"
       << endl <<
    "  &             | add vector 1 to vector 0 (destroys both vectors)"
       << endl <<
    "  *             | print the inner product of vector 0 and vector 1"
       << endl <<
    "  =             | assignment: vector 1 = vector 0"
       << endl <<
    "  c             | print a copy of vector 0"
       << endl <<
    "  p v           | print all items of vector v"
       << endl <<
    "  q             | quit"
       << endl <<
    "Both vectors have 7 items."
       << endl
    ;
}

int main()
{
  Vector v0(7), v1(7); 
  message();
  cout << "Command? ";
  char command_char;
  cin >> command_char;
  while (command_char != 'q') {
    int vector;
    int index;
    double x;
    switch( command_char ) {
    case '>':
      cin >> vector >> index >> x;
      cin.ignore( 100, '\n' );
      if ( 0 == vector ) v0.set( index, x );
      else v1.set( index, x );
      break;
    case '<':
      cin >> vector >> index;
      cin.ignore( 100, '\n' );
      cout << "value = ";
      if ( 0 == vector ) cout << v0.get( index );
      else cout << v1.get( index );
      cout << endl;
      break;
    case '+':{
      cin.ignore( 100, '\n' );
      Vector vectorSum = v0.sum(v1);
      cout << "v0 + v1 = " << vectorSum << endl;
      break;}
    case '&':
      cin.ignore( 100, '\n' );
      v0.add(v1);
      break;
    case '*':
      cin.ignore( 100, '\n' );
      cout << "v0 * v1 = " << v0.inner_product(v1) << endl;
      break;
    case '=':
      cin.ignore(100, '\n' );
      v1 = v0;
      break;
    case 'c': {
      cin.ignore(100, '\n' );
      Vector vectorCopy(v0);
      cout << "copy = " << vectorCopy << endl;
      break;
    }
    case 'p':
      cin >> vector;
      cin.ignore( 100, '\n' );
      if ( 0 == vector) v0.print_all(cout);
      else v1.print_all(cout);
      cout << endl;
      break;
    default:
      cin.ignore( 100, '\n' );
      cout << "Unknown command " << command_char << endl;
      message();
    }
    cout << "v0  = " << v0 << endl
         << "v1  = " << v1 << endl
         << "Another command? ";
    cin >> command_char;
  }
  return 0;
}

