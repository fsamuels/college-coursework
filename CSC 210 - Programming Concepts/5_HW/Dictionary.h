// Forrest Samuels
// CSC 210 - Section 001 - HOBSON
// HW5 - Dictionary.h
// Finished: 3.29.00 @ 7:10pm 

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <ostream.h>

const int INITIAL_NUMBER_OF_WORDS = 4;

class Dictionary {

friend ostream& operator<<(ostream& out, const Dictionary& d);
//Arguments: out - output stream
//           d - dictionary object
//Return value: output stream (out)
//Side effect: Outputs words in dictionary one word per line, e.g.,
//
//An
//Easter
//a
//apple
//away
//bad
//bike
//book
//candy
//doctor
//duck
//egg
//go
//hello
//time
//to


public:

   Dictionary();                                  //Constructor
   //Side effect: Creates a Dictionary object with no words and
   //             room for 4 words;
   
   Dictionary(const Dictionary& other);          //Copy constructor
   //Argument: other - reference to an "other" Dictionary object
   //Side effect: Creates a Dictionary object that is a deep copy of the
   //             "other" Dictionary object
                
   Dictionary& operator=(const Dictionary& rhs); //Overloaded assignment
                                                 //operator
   //Argument: rhs - reference to the Dictionary object on the "right-hand side"
   //                 of the equal sign in an assignment statement
   //Return value: a reference to "this" Dictionary object
   //Side effect: "this" object now has a deep copy of the data in the     
   //             "rhs" object
  
   ~Dictionary();                                //Destructor
   //Side effect: Deallocates any dynamically allocated data
   
   void insert (const char* word);
   //Argument: word - word to insert in the Dictionary
   //Side effect: If the word does not already appear in the myWords array
   //             the word is inserted in the array.
   //             If the myWords array does not have room for the word,
   //             the size of the array is doubled.
   
   bool search (const char* word);
   //Argument: word - word to search for in the Dictionary
   //Return value: true  - the word is contained in the Dictionary
   //              false - the word is not contained in the Dictionary
   
private:
   int findInsertPosition(int first, int last, const char* word);
   //Arguments: first - first position in myWords array
   //           last  - last position in myWords array
   //           word  - word to search for in array
   //Return value: -1 - word was found in array - it should not be inserted
   //              0 ... myNumberOfWords - position in which word should
   //                                      be inserted in array
   
   
    

   
   int myNumberOfWords;    //Number of words in myWords array
   int myMaxWords;         //Maximum number of words array can hold
   char** myWords;         //Array of pointers to words (character strings)
   char** TempMyWords;		//used to double array
   char* Tempword;			//used to move the words in the array	
};

#endif DICTIONAY_H
