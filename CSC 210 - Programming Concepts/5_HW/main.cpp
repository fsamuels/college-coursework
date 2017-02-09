//: main.cpp - main function for spellCheck program
//  Suzanne Balik, 8 Mar 2000

#include <fstream.h>
#include <ctype.h>
#include <string.h>
#include "Dictionary.h"

const int MAX_CHARS_IN_UNIX_LINE = 511;
const int NUM_ARGS = 3;                //Expected number of arguments on the 
                                       //command line
				    
const char USAGE_MSG[] = {"Usage: spellCheck filename dictionary"};


void checkDictionary(const char word[], Dictionary& perm, Dictionary& tmp,
                     bool wordContainsUppercase);   

				    
int main(int argc, const char* argv[])
{

if (NUM_ARGS != argc) {
   cout << USAGE_MSG << endl;
   return 1;
}

ifstream infile(argv[1]);
if (!infile) {
   cout << "File - " << argv[1] << " could not be opened" << endl;
   cout << USAGE_MSG << endl;
   return 1;
}

ifstream dictfile(argv[2]);
if (!dictfile) {
   cout << "Dictionary - " << argv[2] << " could not be opened" << endl;
   cout << USAGE_MSG << endl;
   return 1;
}

//Create permanent and temporary Dictionary's
Dictionary permDictionary;
Dictionary tmpDictionary;

enum State {START, WORD} state = WORD; 
char ch;
int index = 0;    
char buffer[MAX_CHARS_IN_UNIX_LINE + 1];

//Insert the dictionary words into the permanent dictionary
while (dictfile.get(ch)) {
   switch (state) {
      
      case START: if (isalpha(ch)) {
                     buffer[index++] = ch;
		     state = WORD;
		  }
		  break;
		  
      case WORD:  if (isalpha(ch))
                     buffer[index++] = ch;
		  else {
		     buffer[index] = '\0';
		     permDictionary.insert(buffer);
		     index = 0;
		     state = START;
		  }
		  break;
   }
}
dictfile.close();


//Check the input file for words not appearing in the permanent or temporary
//dictionary as is or with any uppercase characters converted to lowercase.
//Allow the user to add the words to either dictionary with the option of 
//preserving the case of any word containing uppercase letters.

bool wordContainsUppercase = false;
index = 0;
while (infile.get(ch)) {
   switch (state) {
      
      case START: if (isalpha(ch)) {
                     buffer[index++] = ch;
		     state = WORD;
		     if (isupper(ch))
		        wordContainsUppercase = true;
		  }
		  break;
		  
      case WORD:  if (isalpha(ch)) {
                     buffer[index++] = ch;
		     if (isupper(ch))
		        wordContainsUppercase = true;
	          }
		  else {
		     buffer[index] = '\0';
		     checkDictionary(buffer, permDictionary, tmpDictionary,
		                     wordContainsUppercase);
		     index = 0;
		     state = START;
		     wordContainsUppercase = false;
		  }
		  break;
   }
}


cout << "\nDisplay Temporary Dictionary (y/n)? ";
cin >> ch;
if ('y' == ch || 'Y' == ch) {
   cout << "\nTemporary"
        << "\nDictionary" 
        << "\n----------" << endl;
   cout << tmpDictionary << endl;
}

cout << "\nDisplay Permanent Dictionary (y/n)? ";
cin >> ch;
if ('y' == ch || 'Y' == ch) {
   cout << "\nPermanent"
        << "\nDictionary" 
        << "\n----------" << endl;
   cout << permDictionary << endl;
}

cerr << "\nOutputting permanent dictionary file - " << argv[2] << " ...";
ofstream dictout(argv[2]);
dictout << permDictionary;
cout << endl;
}		  



void checkDictionary(const char word[], Dictionary& perm, Dictionary& tmp,
                     bool wordContainsUppercase)
{
   char ch;
   char wordInLowercase[MAX_CHARS_IN_UNIX_LINE + 1];
   if (!tmp.search(word) && !perm.search(word)) {
      bool found = false;
      if (wordContainsUppercase) {
         int length = strlen(word);
	 for (int i = 0; i < length; i++)
	    wordInLowercase[i] = tolower(word[i]);
	 wordInLowercase[length] = '\0';
	 if (tmp.search(wordInLowercase) || perm.search(wordInLowercase))
	    found = true;
      }
      if (!found) {
	 cout << "\n'" << word << "' not found in temporary or permanent"
	      << " dictionary"
              << "\nAdd to temporary dictionary (y/n)? ";
         cin >> ch;
         if ('y' == ch || 'Y' == ch) {
	    if (wordContainsUppercase) {
	       cout << "Preserve case of word (y/n)? ";
	       cin >> ch;
	       if ('y' == ch || 'Y' == ch) 
	          tmp.insert(word);
	       else
	          tmp.insert(wordInLowercase);
	       }	  
	    else
	       tmp.insert(word);
	 }      
         else {
	    cout << "Add to permanent dictionary (y/n)? ";
	    cin >> ch;
	    if ('y' == ch || 'Y' == ch) {
	       if (wordContainsUppercase) {
	          cout << "Preserve case of word (y/n)? ";
	          cin >> ch;
	          if ('y' == ch || 'Y' == ch) 
	             perm.insert(word);
	          else
	             perm.insert(wordInLowercase);
	       }	     
	       else
	          perm.insert(word);
            }
         }
      }	    
   }  
}


