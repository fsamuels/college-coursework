// Forrest Samuels
// CSC 210 - Section 001 - HOBSON
// HW5 - Dictionary.cpp
// Finished: 3.29.00 @ 7:10pm 

	//int myNumberOfWords;    //Number of words in myWords array
	//int myMaxWords;         //Maximum number of words array can hold
	//char** myWords;         //Array of pointers to words (character strings)
	//const int INITIAL_NUMBER_OF_WORDS = 4
	
#include <string>
#include "Dictionary.h"

ostream& operator<<(ostream& out, const Dictionary& d) {

	for (int x = 0; x < d.myNumberOfWords; x++) {
		out << d.myWords[x] << "\n";
	}	
		
	return out;
}






Dictionary::Dictionary() {                                  //Constructor

	myWords = new char*[INITIAL_NUMBER_OF_WORDS];
	myNumberOfWords = 0;			//Number of words in myWords array
	myMaxWords = INITIAL_NUMBER_OF_WORDS;	//Maximum number of words array can hold
}




Dictionary::Dictionary(const Dictionary& other) {          //Copy constructor
  //creates a NEW object
	myWords = new char*[other.myMaxWords];
	myNumberOfWords = other.myNumberOfWords;
	myMaxWords = other.myMaxWords;

	for(int x = 0; x < other.myNumberOfWords; x++) {
		myWords[x] = new char[strlen(other.myWords[x]) + 1];
		strcpy(myWords[x], other.myWords[x]);		
	}
}





Dictionary& Dictionary::operator=(const Dictionary& rhs) { //Overloaded assignment
	//MODIFIES and exsisting object
	if (this != &rhs) {

	for (int z = 0; z < myNumberOfWords; z++) {	//deallocate all the words in the array
		delete [] myWords[z];
	}		
	delete [] myWords;	//delete [] myWords
		
	
	myWords = new char*[rhs.myMaxWords];
	myNumberOfWords = rhs.myNumberOfWords;
	myMaxWords = rhs.myMaxWords;

	for(int x = 0; x < rhs.myNumberOfWords; x++) {
		myWords[x] = new char[strlen(rhs.myWords[x]) + 1];
		strcpy(myWords[x], rhs.myWords[x]);		
	}
}

	return *this;
}




	
Dictionary::~Dictionary(){                                //Destructor
	for (int x = 0; x < myNumberOfWords; x++) {	//deallocate all the words in the array
		delete [] myWords[x];
	}	
	
	delete [] myWords;		//deallocate the array
	
}





void Dictionary::insert (const char* word) {

int i = 0;	//temp variable for insert position
	
	if (false == search(word)) {	//if the word is not in the object
		
		// Some of the below code was modified from code found at:
		// <http://wolfware.ncsu.edu/courses/csc210/common/Examples/>
		if (myNumberOfWords >= myMaxWords) {	//Double the array and myMaxWords
		
			myMaxWords = myMaxWords * 2;	//double Max Words in array
			TempMyWords = new char *[myMaxWords];
			
			for ( int x = 0; x < myMaxWords; ++x ) {
				TempMyWords[x] = myWords[x];
			}
			delete [] myWords;		//get rid of old myWords
			myWords = TempMyWords;	//create new myWords array
			
		} //end if (myNumberOfWords >= myMaxWords)


	//////////Find Insert Position/////////////////
	if (0 < myNumberOfWords)
		i = findInsertPosition(0, myNumberOfWords - 1, word);
	

	/////////////Code to move array back for insert//////
	if (i == myNumberOfWords) { //if place to be inserted is last position
		myWords[i] = new char[strlen(word) + 1];
		strcpy(myWords[i], word);	//just insert it
		myNumberOfWords++;
	}
	else { //we have to move things
		
	//Move everything back	
	const int moveSpaces = (myNumberOfWords - i);
		
		for( int loopTemp = 0; loopTemp < moveSpaces; loopTemp++ ) {
		
			Tempword = new char[strlen(myWords[(myNumberOfWords - 1) - loopTemp]) + 1];	//temp for holding 'word'
			strcpy(Tempword, myWords[(myNumberOfWords - 1) - loopTemp]);
			
			delete [] myWords[(myNumberOfWords - 1) - loopTemp];
			myWords[(myNumberOfWords - 1) - loopTemp] = NULL;
			
			myWords[myNumberOfWords - loopTemp] = new char[strlen(Tempword) + 1];
			strcpy(myWords[myNumberOfWords - loopTemp], Tempword);
			
			delete [] Tempword;
			Tempword = NULL;

		}

	myWords[i] = new char[strlen(word) + 1];	//allocate new word
	strcpy(myWords[i], word);					//insert new word
	myNumberOfWords++;							//add 1 to myNumberOfWords						

	} //end else for if we have to move things

	} //end (false == search(word)) 
	//code executed if word is found in the array is below

} //end insert()





bool Dictionary::search (const char* word) {

if (0 < myNumberOfWords) {	//you WILL get a seg fault otherwise because
							//there is nothing at myWords[0] yet

	if (-1 == findInsertPosition(0, myNumberOfWords - 1, word))
		return true;
	else
		return false;
}
else
	return false;

}


  

int Dictionary::findInsertPosition(int first, int last, const char* word) {

	if (first < last) {
      int mid = (first + last)/2;

      if (strcmp(word,myWords[mid]) <= 0)            
         return findInsertPosition(first, mid, word);
      else
         return findInsertPosition(mid+1, last, word);
   }
   else {
      if (0 == strcmp(word, myWords[first]))     //word is already in
         return -1;                              //myWords array
         
      else if (strcmp(word, myWords[first]) < 0) //word belongs before 
         return first;                           //myWords[first]
         
      else                                       //word belongs after                                    
         return first + 1;                       //myWords[first]
   }

}   

