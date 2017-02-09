// Forrest Samuels
// CSC 210 - Section 001 - HOBSON
// HW4 - Order.cpp
// Finished: 3-7-00


#include "defs.h"
#include "Order.h"
#include "Pizza.h"
#include <string> //for strcpy() and strncpy()

//	char my_name[MAX_NAME_LENGTH];
//	char my_phone[MAX_PHONE_LENGTH];
//	int my_number_pizzas;
//	int my_order_price;
//	Pizza my_pizzas[MAX_PIZZAS];
	
ostream& operator<< (ostream& out, const Order& o) {

	
	// The code below was snatched and modified from "compfun.cpp"
	// which is included with the textbook 'Computing Fundamentals
	// with C++', 2nd edition - Rick Mercer 
	// - Copyright Franklin, Beedle, and Associates
	out.setf(ios::fixed, ios::floatfield);
    out.setf(ios::showpoint);
	out.precision(2);
	//	
	
	out << endl;
	out << "Name:   " << o.my_name << endl;
	out << "Phone:  " << o.my_phone << endl;
	out << "Total:  " << float(o.price()) / 100 << endl;
	
	
	for(int i = 0; i < o.my_number_pizzas; i++) { //made <, <=
		out << endl;
		out << o.my_pizzas[i];
	}
		
	return out;
}
   
 
 

 Order::Order(const char name[], const char phone[]) {
	my_number_pizzas = 0;
	my_order_price = 0;

	if (strlen(name) > MAX_NAME_LENGTH) {	//if input array is to long, use strncpy
		strncpy(my_name, name, MAX_NAME_LENGTH);
		my_name[MAX_NAME_LENGTH] = '\0';
	}
	else {
		strcpy(my_name, name);
	}


	if (strlen(phone) > MAX_PHONE_LENGTH) {		//if input array is to long, use strncpy
		strncpy(my_phone, phone, MAX_PHONE_LENGTH);
		my_phone[MAX_PHONE_LENGTH] = '\0';
	}
	else {
		strcpy(my_phone, phone);
	}

 
}


 bool Order::isFull() const {
  
	 if (MAX_PIZZAS == my_number_pizzas) 
		return true;
	else
		return false;
 }
   
   
 
 
 bool Order::addPizza(const Pizza& pizza) {
 
	 if (MAX_PIZZAS > my_number_pizzas) {
		
		my_pizzas[my_number_pizzas] = pizza;
		my_number_pizzas++;
		my_order_price += pizza.price();
		return true;
	}
	else
		return false;
 }
   
 
 

 int Order::price() const {
	 
 	 return my_order_price;
 }
   

