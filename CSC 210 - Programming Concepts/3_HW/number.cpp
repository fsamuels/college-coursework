//Forrest Samuels
//CSC 210 - Section 001 - HOBSON
//HW3 - number.cpp
//this is an example of a Finite State Machine that converts HEX, OCTAL, and INTEGER
//char inputs to the other type
//
//Worked first on 2-16-00. Added in error checking 2-17-00.

#include <iostream.h>
#include <iomanip.h>

void main(int argc, char * argv[]) {

	// Initalize states
	enum {ERROR, INTEGER, OCTAL, HEX, OUTPUT} state = OUTPUT;

	//char string[10] = "0xafaf"; //argv[1]
	char ch;
	int i = 0;		//
	int value = 0;	//int value of input
	int B = 10;		//default Base for using Horner's Rule is set to 10

	int a = 10, b = 11, c = 12, d = 13, e = 14, f = 15; //define a-f for HEX conversion

//Error Checking from command line input//////
	if (2 != argc)			//command line should be program and 1 input
		state = ERROR;
//////////////////////////////////////////////


//START state////////////////////
	if (state != ERROR) {
	//if (state == ERROR) is used so the program will not crash and burn
	//if no command arguments are given
	ch = argv[1][i]; 
	
	if ('0' == ch)
		state = OCTAL;
	else if ( (1 <= (int(ch)-48))   &&   (9 >= (int(ch)-48)) )
		state = INTEGER;
	else 
		state = ERROR;
	}
//////////////////////////////

	while ((state != ERROR) && (ch = argv[1][i++])) {
		switch (state) {

		case INTEGER:
			if ( (0 <= (int(ch)-48))   &&   (9 >= (int(ch)-48)) ) //error checking
			value = (value + (int(ch) - 48))*B;
			else {
				cout << "Invalid number" << endl;
				state = ERROR;
			}
			break;

		case OCTAL:
			B = 8;
			if ((2 == i) && (('x' == ch) || ('X' == ch))) //check for HEX sate when i == 2
				state = HEX;
			else if ( (0 <= (int(ch)-48))   &&   (7 >= (int(ch)-48)) ) //error checking
				value = (value + (int(ch) - 48))*B;
			else {
				cout << "Invalid number" << endl;
				state = ERROR;
			}
			break;
		
		case HEX:
			B = 16;
			if ((0 <= (int(ch)-48))   &&   (9 >= (int(ch)-48))) //if 'ch' is 0-9
				value = (value + (int(ch) - 48))*B;
			else if ('a' == ch)					//a-f values
				value = (value + a)*B;
			else if ('b' == ch)
				value = (value + b)*B;
			else if ('c' == ch)
				value = (value + c)*B;
			else if ('d' == ch)
				value = (value + d)*B;
			else if ('e' == ch)
				value = (value + e)*B;
			else if ('f' == ch)
				value = (value + f)*B;
			else {
				cout << "Invalid number" << endl;
				state = ERROR;
			}
			break;
		
			
		}	
	}
	if (state == ERROR)
		cout << "Usage: number [1-9]([0-9])* | 0([0-7])* | 0[Xx]([0-9a-f])*" << endl;
	
	else {	//OUTPUT state
	value = value/B; //makes up for undesired multipication of the last digit and Base
	cout << setiosflags(ios::showbase) << value
			<< oct << '\t' << value 
			<< hex << '\t' << value << endl;
	}
}
