// Forrest Samuels
// CSC 210 - Section 001 - HOBSON
// HW4 - Pizza.h
// Finished: 3-7-00

#ifndef PIZZA_H
#define PIZZA_H

#include "defs.h"
#include <ostream.h>


class Pizza {

friend ostream& operator<<(ostream& out, const Pizza& p);
   //Arguments:
   //  out - output stream
   //  p - Pizza object
   //Return value: output stream (out)
   //Side effect: output pizza information in following (or similar) format:
   //
   // Size:     Small
   // Price:    7.50
   // Toppings: Pepperoni
   //           Mushrooms
   //           Sausage
   //           Green Pepper
   //           Onions
   //
   // OR for a pizza with NO toppings
   //
   //  Size:     Large
   //  Price:    15.00



public:   
   
	Pizza::Pizza();
	//default

   Pizza(PizzaSize size);
   //Arguments:
   //  size of pizza - SMALL, MEDIUM, LARGE
   //  If no size or an invalid size is given, the size defaults to MEDIUM
   //Side effect: Creates a Pizza object with no toppings  
   //             A Pizza object can have 0 to 5 toppings
                       
   
   void setSize(PizzaSize size);
   //Arguments:
   // size of pizza - SMALL, MEDIUM, LARGE
   //Side effect: the pizza's size is set to given size
  
     
   bool addTopping(const char topping[]);
   //Arguments:
   //  topping - name of topping containing up to 20 chars. not including '\0'
   //            NO checking is done to validate topping name- 
   //            topping could be "pepperoni", "sausage", "xxxxx", etc.
   //Return value: true - topping was added to pizza
   //              false - topping was not added to pizza because it already
   //                      has the limit of 5 toppings
   
   int price() const;
   //Return value: the price of the pizza in cents calculated as follows:
   //              Small  -  500 +  50 per topping
   //              Medium - 1000 + 100 per topping
   //              Large  - 1500 + 150 per topping


private:

	char my_toppings[MAX_PIZZAS][MAX_NAME_LENGTH + 1];
	int my_size;
	int my_numberToppings;
};

#endif PIZZA_H
