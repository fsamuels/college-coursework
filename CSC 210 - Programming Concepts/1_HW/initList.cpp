#include <ostream.h>

//////////////////////////////////////////////////////////////
void int_print( ostream & out, const int source[], int source_length) {

int n = 0;

while(n < source_length) {
	out << source[n] << " ";
	n++;
	} 
}





///////////////////////////////////////////////////
void int_reverse( int source[], int length ) {

int looptimes;
int dummy;

looptimes = (length / 2); //how many times to run loop = to half length
length--; //so it will not start at null b/c of arrays starting at 0

for(int t=0; t < looptimes; t++) {
        dummy = source[t];
        source[t] = source[length];       
    	source[length] = dummy;
        length--;
        }
}             



//////////////////////////////////////////////////////
void int_splice( int target[], const int source[], int n,
                       int& target_length, int source_length) {

int targetLength = target_length;
const int sourceLength = source_length;
const int substring = targetLength - n;

if (n > targetLength || n < 0) {
        cerr << "Sorry but your input is out of range!" << endl;
        }

for( int loopTemp = 0; loopTemp <= substring; loopTemp++ ) {            
target[((targetLength - 1) + sourceLength) - loopTemp] =
                target[(targetLength - 1) - loopTemp];
        }

for( int loop2Temp = 0; loop2Temp < sourceLength; loop2Temp++ ) {
        target[n + loop2Temp] = source[loop2Temp];
        }

target_length =  targetLength + sourceLength;
} 



/////////////////////////////////////////////////////////
bool findInt( int target[], const int to_be_removed[], int startingPoint2, int stopPoint ) {

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
void int_remove( int target[], const int to_be_removed[],
                       int& target_length, int remove_length) {

int targetLength = target_length;
const int removedLength = remove_length;
const int testTimes = targetLength - removedLength;
int startingPoint = 0;


//finds start position of string to be deleted as startingPoint
while ( (startingPoint < testTimes) && (findInt( target, to_be_removed, startingPoint, removedLength) == false) ) {
	//cout << "startingPoint: "<< startingPoint << endl;
	startingPoint++;
}

const int substring = (targetLength - removedLength) - startingPoint;

//must double check last one to see if needs to be removed or not!
if ((findInt( target, to_be_removed, testTimes, removedLength) == false) &&
		(startingPoint >= testTimes));			
	//do nothing and exit function
else {

//this moves everything back
	for( int loopTemp = 0; loopTemp <= substring; loopTemp++ ) {
		target[startingPoint + loopTemp] = 
			target[startingPoint + loopTemp + removedLength]; 
		}
target_length = targetLength - removedLength;
}

}