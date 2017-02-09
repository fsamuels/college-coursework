//: defs.h - definitions header file
//  Suzanne Balik, 24 Feb 2000

#ifndef DEFS_H
#define DEFS_H

const int MAX_TOPPINGS = 5;
const int MAX_PIZZAS = 5;
const int MAX_NAME_LENGTH = 20;     //Maximum number of characters in
                                    //in a person or topping name
				    //Does not include '\0' character
const int MAX_PHONE_LENGTH = 8;     //Maximum number of characters in
                                    //a phone number not including '\0'
				    
enum PizzaSize              {SMALL, MEDIUM, LARGE};
const int base_price[] =    {  500,   1000,  1500};
const int topping_price[] = {   50,    100,   150};
const char size_name[][MAX_NAME_LENGTH] = {"Small", "Medium", "Large"}; 

				    
#endif
