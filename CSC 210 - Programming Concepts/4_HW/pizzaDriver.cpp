//: pizzaDriver.cpp - test driver for Pizza class
//  Suzanne Balik, 24 Feb 2000


#include <fstream.h>
#include "Pizza.h"
#include "Order.h"


int main() 
{


Pizza pizza1(LARGE);                   //Create a Large pizza with no toppings

cout << pizza1 << endl << endl;        //Use overloaded output operator to
                                       //output Pizza information
Pizza pizza4(LARGE);
cout << pizza4;
pizza4.addTopping("Peporoni");
pizza4.addTopping("Beer");
pizza4.addTopping("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnop");
pizza4.addTopping("012345678901234567890123456789");
pizza4.addTopping("IfIhadAmillionDollars,I'dBuyYouACar");
cout << pizza4;


pizza1.addTopping("Pepperoni");        //Add 5 toppings
pizza1.addTopping("Mushrooms");
pizza1.addTopping("Sausage");
pizza1.addTopping("Green Pepper");
pizza1.addTopping("Onions");

cout << pizza1 << endl << endl;        //Output pizza info again


if (pizza1.addTopping("Black Olives")) //Try to add a 6th topping
   cout << "Topping added" << endl;
else
   cout << "Topping not added" << endl;
   
pizza1.setSize(SMALL);                  //Change the pizza's size to Small
cout << pizza1 << endl << endl;       //and output pizza information



Pizza pizza2;                         //Use Pizza null constructor
pizza2.addTopping("Ham");             //Add 2 toppings
pizza2.addTopping("Pineapple");      

cout << pizza2 << endl;               //Output info for second pizza

Pizza pizza3;
pizza3.addTopping("This topping name has more than 20 characters, it should be truncated");
cout << pizza3 << endl;


Order order1("Dedrick Forrest Samuels, III", "248-5858");
Order order2("George Peterson", "512-9455");
Order order3("Bob Smith", "123-4567");
Order order4("Joe Smith", "765-4321");
Order order5("Johnny Bobby Smith", "123-4567890123456789012348901234567890");
Order order6("Joey Carl Smith Johnson, Jr", "765-4321000000000000000000000");
Order order7("212121212121212121212", "999999999");
Order order8("20202020202020202020", "88888888");
Order order9(" ","");

cout << order1;
cout << order2;
cout << order3;
cout << order4;


order2.addPizza(pizza2);

cout << order2;


cout << order5;
cout << order6;


order2.addPizza(pizza1);
order2.addPizza(pizza2);

if (order2.isFull()) 
	cout << "Is Full." << endl;
else
	cout << "Is Not Full." << endl;

order2.addPizza(pizza1);
order2.addPizza(pizza2);

if (order2.isFull()) 
	cout << "Is Full." << endl;
else
	cout << "Is Not Full." << endl;

	
order2.addPizza(pizza1);

if (order2.addPizza(pizza2)) //Try to add a 6th pizza
   cout << "Pizza added" << endl;
else
   cout << "Pizza not added" << endl;

if (order2.isFull()) 
	cout << "Is Full." << endl;
else
	cout << "Is Not Full." << endl;


cout << order2;

cout << order3;
cout << order4;

cout << order5;

for(int z = 1; z < 10; z++) {
order5.addPizza(pizza4);
cout << order5;
}

//cout << order7;
//cout << order8;
//cout << order9;
  
return 0;
}


