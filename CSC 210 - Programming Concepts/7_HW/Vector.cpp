//: Vector.cpp - implementation of the fixed-length vector class (length
//:              determined at time of creation [skeleton version]
// Matt Stallmann, 13 April 2000 from a working version of Vector.cpp
// -----------------------------------------
// Forrest Samuels
// 4.18.00	setHelper() working, cleaned up debug cout's and commented
//			getHelper() working, wrote in 5min
// 4.19.00	print_allHelper() working, took longer then anticipated
// 4.23.00	Added return 0.0 instead of 0 for getHelper(), errors in DOS
// 4.25.00	inner_productHelper() works on SunOS dut not DOS, returns -1.#IND
//			Fixed some bugs in setHelper() by checking other conditions
// 4.26.00	sumHelper() finished, not well tested but time is near the end
			

#include<iostream.h>
#include<assert.h>
#include"Vector.h"

class VNode {
  friend ostream & operator << ( ostream & out, const VNode & vn );
public:
  int my_index;
  double my_value;
  VNode * my_link;
  VNode( int index, double value, VNode * link = 0 ):
    my_index( index ), my_value( value ), my_link( link ) {}
};

ostream & operator << ( ostream & out, const VNode & vn )
{
  out << "(" << vn.my_index << ", " << vn.my_value << ")";
  return out;
}

ostream & operator << ( ostream & out, const VNode * vp )
{
  if ( vp ) {
    out << " " << *vp;
    out << vp->my_link;
  }
  return out;
}

ostream & operator << ( ostream & out, const Vector & v )
{
  out << "[" << v.my_length << " |" << v.my_head << "]";
  return out;
}

// CLASSINV: my_head points to a linked list of pairs of the form (i,x),
//           where 1 <= i <= my_length and x != 0; the i values are in
//           ascending order. v[i] == x != 0 if and only if (i,x) appears
//           in the list 

Vector::Vector( int length ): my_length( length ), my_head( 0 ) {}

static void setHelper( VNode * & vp, int i, double x ) {

	//Base Case 1 (End of Vector or is empty and x != 0, add VNode to end)
	if ((!vp) && (0 != x)) {
		vp = new VNode(i,x,0);	//add new VNode
		return;
	}
	
	//Base Case 2 (incase you are at the end but x = 0)
	if ((!vp) && (0 == x))
		return;

	//Base Case 3 (VNode exsists but x = 0, remove VNode)
	if ((vp->my_index == i) && (0 == x)) {
		VNode *temp = vp;	//set temp to current VNode
		vp = vp->my_link;	//set current VNode to next VNode
		delete temp;		//delete old VNode
		return;
	}
		
	//Base Case 4 (VNode does exsist and x != 0)
	if ((vp->my_index == i) && (0 != x)){
		vp->my_value = x;	//set new my_value
		return;
	}

	//Base Case 5 (VNode does not exsist, add node before current node)
	if ((i < vp->my_index) && (0 != x)) {
		VNode *temp = vp;			//set temp to current VNode	
		vp = new VNode(i,x,temp);	//create new VNode pointed to by 'vp' which
		return;						//		points to 'temp' which is old 'vp'
	}

	//Recursive Case
	setHelper(vp->my_link, i, x);
}



void Vector::set( int i, double x ) {
  assert( 1 <= i && i <= my_length );
  setHelper( my_head, i, x );
}

int Vector::length() const {
  return my_length;
}

static double getHelper( VNode * vp, int i ) {

	//Base Case 1 (if you get to the end of the vector and still no match)
	if (!vp)
		return 0.0;

	//Base Case 2 (if you find a match)
	if (vp->my_index == i)
		return vp->my_value;

	//Recursive Case
	getHelper(vp->my_link, i);
}



double Vector::get( int i ) const {
  assert( 1 <= i && i <= my_length );
  return getHelper( my_head, i );
}



static void addHelper(VNode *& vp0, VNode *& vp1) {
cout << "addHelper() executed" << endl;
/*
cout << "vp0->my_index: " << vp0->my_index << endl;
cout << "vp1->my_index: " << vp1->my_index << endl;

cout << "vp0->my_value: " << vp0->my_value << endl;
cout << "vp1->my_value: " << vp1->my_value << endl;
*/

	//Base Case 1 (till we get to the end of both)
	if ((!vp0) && (!vp1)) {
cout << "addHelper() Base Case 1" << endl;

		return;	
	}
	
	//Base Case 2 (if no vp0, just work with vp1)
	else if (!vp0) {
cout << "addHelper() Base Case 2" << endl;
	}

	//Base Case 3 (if no vp1,just work with vp0)
	else if (!vp1) {
cout << "addHelper() Base Case 3" << endl;
	}
	
	//Base Case 4 (if both are equal)
	else if (vp0->my_index == vp1->my_index) {
	
cout << "addHelper() Base Case 4" << endl;		
cout << "vp0->my_value: " << vp0->my_value << endl;		
		

		vp0->my_value = (vp0->my_value + vp1->my_value);	//add values

cout << "vp0->my_value: " << vp0->my_value << endl;	

		vp0 = vp0->my_link;	//set vp0 to next link

		VNode *temp = vp1;	
		vp1 = vp1->my_link;	//move to next vp1 VNode
//		delete temp;		//delete old vp1 VNode

	}

	//Base Case 5 (vp0 < vp1)
	else if (vp0->my_index < vp1->my_index) {
	}


	//Base Case 6 (vp0 > vp1)
	else if (vp0->my_index > vp1->my_index) {
	}



addHelper(vp0, vp1);

}



void Vector::add( Vector & other ) {
   assert(my_length == other.my_length);
   addHelper(my_head, other.my_head);
}

static VNode* sumHelper(VNode* vp0, VNode* vp1) {	
//written with the ideas from looking at
//copy constructor and inner_productHelper()	

	//Base Case 1 (till we get to the end of both)
	if ((!vp0) && (!vp1))
		return 0;	//return a NULL
	
	//Recursie Case 1 (if no vp0, just work with vp1)
	if (!vp0) {
		VNode *newVNode = new VNode(vp1->my_index,
									vp1->my_value,
									sumHelper(vp0, vp1->my_link));
		return newVNode;
	}

	//Recursie Case 2 (if no vp1,just work with vp0)
	if (!vp1) {
		VNode *newVNode = new VNode(vp0->my_index,
									vp0->my_value,
									sumHelper(vp0->my_link, vp1));
		return newVNode;
	}
	
	//Recursie Case 3 (if both are equal)
	if (vp0->my_index == vp1->my_index) {
		VNode *newVNode = new VNode(vp0->my_index,
									(vp0->my_value + vp1->my_value),
									sumHelper(vp0->my_link, vp1->my_link));
		return newVNode;
	}

	//Recursie Case 4 (vp0 < vp1)
	if (vp0->my_index < vp1->my_index) {
		VNode *newVNode = new VNode(vp0->my_index,
									vp0->my_value,
									sumHelper(vp0->my_link, vp1));
		return newVNode;
	}


	//Recursie Case 5 (vp0 > vp1)
	if (vp0->my_index > vp1->my_index) {
		VNode *newVNode = new VNode(vp1->my_index,
									vp1->my_value,
									sumHelper(vp0, vp1->my_link));
		return newVNode;
	}
}


Vector Vector::sum( const Vector & other ) const {
   assert(my_length == other.my_length);
   Vector retval(my_length);
   retval.my_head = sumHelper(my_head, other.my_head);
   return retval;
}


static double inner_productHelper(VNode* vp0, VNode* vp1, double sum = 0.0) {

	//Base Case 1 (if either vector is empty)
	if ((!vp0) || (!vp1))
		return sum;

	//Base Case 3 (vp0 > vp1)
	if (vp0->my_index > vp1->my_index)
		vp1 = vp1->my_link;

	//Base Case 4 (vp1 > vp0)
	else if (vp1->my_index > vp0->my_index)
		vp0 = vp0->my_link;

	//Base Case 2 (if both are = add product and goto next nodes)
	if ((vp0) && (vp1) && (vp0->my_index == vp1->my_index)) {
		sum = sum + ((vp0->my_value) * (vp1->my_value));
		vp1 = vp1->my_link;
		vp0 = vp0->my_link;
	}
	
	//Recursive Case
	inner_productHelper(vp0, vp1, sum);
	
}

double Vector::inner_product(const Vector& other) const {  
   
	assert(my_length == other.my_length);
   return inner_productHelper(my_head, other.my_head);
}



void print_allHelper(ostream& out, VNode* vp, int index, int length) {
	
	//Base Case 1 (Nothing more to print out)
	if (index > length)
		return;

	//Base Case 2 (VNode exsist, so print my_value and go to next VNode)
	if ((vp) && (vp->my_index == index)) {
		out << vp->my_value;	
		vp = vp->my_link;	//set to next link
	}

	//Base Case 3 (no VNode, so output 0)
	else 	
		out << 0;

	//Recursive Case
	if (index < length)
			out << ", ";
	print_allHelper(out, vp, ++index, length);
}


void Vector::print_all(ostream& out) const {

   assert (my_length > 0);
   out << '(';
   print_allHelper(out, my_head, 1, my_length);
   out << ')';
}



// Dynamic Memory Suite
static void deallocate(VNode* p) {

//I got this code from my class notes
	if (p) {
		deallocate(p->my_link);
		delete p;
	}
}



Vector::~Vector() {
	deallocate(my_head);
}



static VNode* copy(VNode* p) {

//Got this code from the online notes
	if (!p)
		return 0;
	else {
		VNode *newVNode = new VNode(p->my_index, p->my_value, copy(p->my_link));
		return newVNode;
	}
} 



Vector::Vector(const Vector& other) {

   my_length = other.my_length;
   my_head = copy(other.my_head);
}



Vector & Vector::operator = ( const Vector & rhs ) {

   if (this != &rhs) {
      deallocate (my_head);
      my_length = rhs.my_length;
      my_head = copy(rhs.my_head);
   }
   return *this;
}






