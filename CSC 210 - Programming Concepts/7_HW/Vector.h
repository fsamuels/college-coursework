//: Vector.h - header for a fixed-length vector class (length determined at 
//:            time of creation
// Matt Stallmann, 06 April 2000

#include<iostream.h>

class VNode;

class Vector {
  // In the comments below, v[i] refers to the i-th element of the vector v;
  // vectors, unlike C++ arrays, are indexed beginning at 1.

  friend ostream & operator << ( ostream & out, const Vector & v );
  // for debugging - print the contents of the data structure
public:
  Vector( int length );
  // PRE: length > 0
  // POST: length() == length && get(i) == 0 for 1 <= i <= length()

  void set( int i, double x );
  // PRE: 1 <= i <= length()
  // POST: *this[i] == x

  int length() const;

  double get( int i ) const;
  // PRE: 1 <= i <= length()
  // POST: retval == *this[i]

  Vector sum( const Vector & other ) const;
  // PRE: length() == other.length()
  // POST: retval[i] == *this[i] + other[i] for 1 <= i <= length()

  void add( Vector & other );
  // PRE: length() == other.length()
  // POST: *this[i] == *this[i]<before> + other[i] for 1 <= i <= length()
  //       other[i] == 0 for 1 <= i <= length()

  double inner_product( const Vector & other ) const;
  // PRE: length() == other.length()
  // POST: retval == the sum of (*this[i] * other[i]) for 1 <= i <= length()

  void print_all( ostream & out ) const;
  // POST: (*this[1], *this[2], ..., *this[length()]) has been inserted
  //       into out 

  // dynamic memory suite
  ~Vector();
  Vector( const Vector & other );
  Vector & operator = ( const Vector & rhs );

private:
  // to be implemented as a linked list (sparse)
  int my_length;
  VNode * my_head;
};
