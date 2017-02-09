//: industrial.cpp - industrial strength driver program for Dictionary class
//  Suzanne Balik, 8 March 2000

#include <iostream.h>
#include <stdlib.h>         //rand()
#include "Dictionary.h"

const int LOOP_MAX = 25000;

const int MAX_WORD_LENGTH = 20;

void randomWord(char word[])
{
   const int NUM_LETTERS = 26;
   int length = rand() % MAX_WORD_LENGTH;
   for (int i = 0; i < length; i++)
      word[i] = rand() % NUM_LETTERS + 'a';
   word[length] = '\0';
}


int main()
{
   cout << "Loop will be executed " << LOOP_MAX << " times" << endl;
   const int NUM_WORDS = 9;
   char words[NUM_WORDS][MAX_WORD_LENGTH] = {"apple", "boy", "constitution", "duck", 
                            "everything", "fox", "grapes", "helicopter",
			    "igloo"};
   const int MAX = 20;
   char wordToInsert[MAX_WORD_LENGTH+1];
   int i, j;
   
   //Create Dictionary A1 and insert random words
   Dictionary A1;
   for (i = 0; i < MAX; i++) {
      randomWord(wordToInsert);
      A1.insert(wordToInsert);
   }
   
   //Create Dictionary A2 and insert words listed above
   Dictionary A2;
   for (i = 0; i < NUM_WORDS; i++)
      A2.insert(words[i]);
      
   //Loop a large number of times   
   for (i = 0; i < LOOP_MAX; i++) {
   
      //Create Dictionary B1, insert random words, and assign it to A1
      Dictionary B1;
      for (j = 0; j < MAX; j++) {
         randomWord(wordToInsert);
         B1.insert(wordToInsert);
      }
      A1 = B1;                      //Uses overloaded assignment operator
      
      
      //Create Dictionary B2 as a copy of A2 and insert random words in it
      Dictionary B2 = A2;           //Uses copy constructor
      for (j = 0; j < MAX; j++) {
         randomWord(wordToInsert);
         B2.insert(wordToInsert);
      }
   }                                //Destructor is called
   
   //Output original words and compare with words in A2
   cout << "These words should be the same as the words that follow: " << endl;
   for (i = 0; i < NUM_WORDS; i++)
      cout << words[i] << endl;             
   cout << '\n' << A2 << endl;
}
             
