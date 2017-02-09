#include<iostream.h> //for cerr

/////////////////////////////////////////////////
int str_length( const char source[] ) {

char x='0'; 	//variable in array that si teste for null character
int n=0; 	//counter to determine how many characters in array

while(x != '\0') {
	x = source[n];
	n++;
}
return n-1;
}		





////////////////////////////////////////////////
void str_reverse( char source[] ) {

int looptimes;
int length;
char dummy;

length = str_length(source);
looptimes = (length / 2); //how many times to run loop = to half length
length--; //so it will not start at null b/c of arrays starting at 0

for(int t=0; t < looptimes; t++) {
	dummy = source[t];
	source[t] = source[length];
	source[length] = dummy;
	length--;
	}
}








/////////////////////////////////////////////////
void str_splice( char target[], const char source[], int n ) {

const int targetLength = str_length(target);
const int sourceLength = str_length(source); 
const int substring = targetLength - n;

if (n > targetLength || n < 0) {
	cerr << "Sorry but your input is out of range!" << endl;
	}
else {

for( int loopTemp = 0; loopTemp <= substring; loopTemp++ ) {
	target[((targetLength - 1) + sourceLength) - loopTemp] = 
		target[(targetLength - 1) - loopTemp];
	}

for( int loop2Temp = 0; loop2Temp < sourceLength; loop2Temp++ ) {
	target[n + loop2Temp] = source[loop2Temp];
	}
}

}




/////////////////////////////////////////////////////////
bool findString( char target[], const char to_be_removed[], int startingPoint2, int stopPoint ) {

int x = 0; //used to cycle from 0 -> stopPoint of to_be_removed Array

stopPoint = startingPoint2 + stopPoint; 

while(startingPoint2 < stopPoint) {
	if (to_be_removed[x] != target[startingPoint2]) 
		return false;
	else {
		x++;
		startingPoint2++;
		}
}

return true;
}



////////////////////////////////////////////////////////////
void str_remove( char target[], const char to_be_removed[] ) {

const int targetLength = str_length(target);
const int removedLength = str_length(to_be_removed);
const int testTimes = targetLength - removedLength;
int startingPoint = 0;


//finds start position of string to be deleted as startingPoint
while ( (startingPoint < testTimes) && (findString( target, to_be_removed, startingPoint, removedLength) == false) ) {
	//cout << "startingPoint: "<< startingPoint << endl;
	startingPoint++;
}

const int substring = (targetLength - removedLength) - startingPoint;

//must double check last one to see if needs to be removed or not!
if ((findString( target, to_be_removed, testTimes, removedLength) == false) &&
		(startingPoint >= testTimes));			
	//do nothing and exit function
else {

//this moves everything back
	for( int loopTemp = 0; loopTemp <= substring; loopTemp++ ) {
		target[startingPoint + loopTemp] = 
			target[startingPoint + loopTemp + removedLength]; 
		}
}



}
