// Forrest Samuels
// CSC 210 - Section 001 - HOBSON
// HW4 - Order.h
// Finished: 3-7-00

#ifndef ORDER_H
#define ORDER_H

#include "defs.h"
#include "Pizza.h"
#include <ostream.h>

class Order {

	
  friend ostream& operator<<(ostream& out, const Order& o);
   //Arguments:
   //  out - output stream
   //  o - Order object
   //Return value: output stream (out)
   //Side effect: output order information in following (or similar) format:
   //
   // Name:  Bill Smith
   // Phone: 123-4567
   // Total: 52.00
   //          
   // Size:     Large
   // Price:    16.50
   // Toppings: Pepperoni
   //
   // Size:     Medium
   // Price:    11.00
   // Toppings: Extra Cheese
   //          
   // Size:     Medium
   // Price:    11.00
   // Toppings: Black Olives
   //          
   // Size:     Small
   // Price:    6.00
   // Toppings: Ham
   //           Pineapple
   //          
   // Size:     Small
   // Price:    7.50
   // Toppings: Extra Cheese
   //           Onions
   //           Green Peppers
   //           Black Olives
   //           Mushrooms
 
public:

	
   Order(const char name[], const char phone[]);
   //Arguments: name - name containing up to 20 chars. not including '\0'
   //           phone - phone number containing up to 8 chars. not including '\0'
   //Side effect: Creates an Order object with no pizzas  
   //             An Order object can have 0 to 5 Pizzas
   
   bool isFull() const;
   //Return value: true  - Order is full - contains 5 pizzas
   //              false - Order is not full - contains 0 - 4 pizzas
   
   bool addPizza(const Pizza& pizza);
   //Argument: pizza - Pizza object to add to Order
   //Return value: true - pizza was added to Order
   //              false - pizza was not added to Order because it already
   //                      has the limit of 5 pizzas
                
   int price() const;
   //Return value: total price in cents of all of the pizzas in the order 

private:

	char my_name[MAX_NAME_LENGTH + 1];
	char my_phone[MAX_PHONE_LENGTH + 1];
	int my_number_pizzas;
	int my_order_price;
	Pizza my_pizzas[MAX_PIZZAS];


};
#endif ORDER_H
