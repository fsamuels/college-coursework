// Forrest Samuels
// CSC 210 - Section 001 - HOBSON
// HW4 - Pizza.cpp
// Finished: 3-7-00

#include "defs.h"
#include "Pizza.h"
#include <ostream.h>
#include <string> //for strcpy() and strncpy()
	

ostream& operator<<(ostream& out, const Pizza& p) {

	// The code below was snatched and modified from "compfun.cpp"
	// which is included with the textbook 'Computing Fundamentals
	// with C++', 2nd edition - Rick Mercer 
	// - Copyright Franklin, Beedle, and Associates
	out.setf(ios::fixed, ios::floatfield);
    out.setf(ios::showpoint);
	out.precision(2);
	//
	out << "Size:     " << size_name[p.my_size] << endl;
	out << "Price:    " << float(p.price()) / 100 << endl;
	
	if (0 < p.my_numberToppings) {
		out << "Toppings: ";
	for(int i = 0; i < p.my_numberToppings; i++) {
		out <<  p.my_toppings[i] << endl;
		out << "          ";	
	}
	out << endl;
	}
return out;
}
 



Pizza::Pizza() {
		my_size = MEDIUM;
		my_numberToppings = 0;
}




Pizza::Pizza(PizzaSize size = MEDIUM) {
	my_size = size;
	my_numberToppings = 0;  
}




void Pizza::setSize(PizzaSize size) {
	my_size = size;
}




bool Pizza::addTopping(const char topping[]) {

if (my_numberToppings < MAX_TOPPINGS) {
	
	if (strlen(topping) > MAX_NAME_LENGTH) {	//if input array is to long, use strncpy
		strncpy(my_toppings[my_numberToppings], topping, MAX_NAME_LENGTH);
		my_toppings[my_numberToppings][MAX_NAME_LENGTH] = '\0';
		
	}
	else {
		strcpy(my_toppings[my_numberToppings], topping);
	}

	my_numberToppings++;
	return true;

}	//end 'if (my_numberToppings < MAX_TOPPINGS)'

else {	//if (my_numberToppings => MAX_TOPPINGS)
	return false;
}

}




int Pizza::price() const {
	return base_price[my_size] + (topping_price[my_size] * my_numberToppings);
}