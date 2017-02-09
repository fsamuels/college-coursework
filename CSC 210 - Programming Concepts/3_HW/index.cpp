// Forrest Samuels
// CSC 210 Section 001 - Hobson
//
// Modifications:
// 2-20-00:	First working on (sort of)
// 2-22-00:	Corrected words with out a vowel not having any syllables
//			Corrected rounding up error for 'Index'
//			Added E state cause I forgot to earlier, and a using a bool to 
//				check would hamper the fact that this is a FSM
//2-23-00	Everything appears to work 100%. But I must do more testing
//			Works well on normal sentences and grammer, jibberish it does not like,
//				I think that is because my 'sentence' counting rule is wrong
//			Sentence counting is off on weird cases beacuase I desigened the punctuation
//				state wrong in the first place.. to late now...	
//


#include <fstream.h>
#include <ctype.h> //for isspace()

void main(int argc, char * argv[]) {


float ws = 0.0;		//word syllables
float s = 0.0;		//total syllables
float w = 0.0;		//total words
float sen = 0.0;	//total sentences
float Index = 0.0;
char ch;
char * filename = "";
bool endSentence = false; //to get around no space after punctuation
ifstream in;

enum { START, ERROR, OTHER, VOWEL, E, WHITESPACE, PUNCTUATION } state = START;
/////////////////////////////////////////////////////////


if (argc != 2) {
	cout << "Usage: index filename" << endl;
	state = ERROR;
}

else {
filename = argv[1];
in.open(filename); //open file
	if (!in) {
		cout << "You did not enter a valid filename!" << endl;
		state = ERROR;
	}
}

///////////////////////////////////////////////////////////////////////////
while ((state != ERROR) && (in.get(ch))){
	switch(state) {
	
	////////////
	case START:
		if (isspace(ch) != 0)
			state = WHITESPACE;
		else if (('.' == ch) || (':' == ch) || (';' == ch) || ('?' == ch) || ('!' == ch))
			state = PUNCTUATION;
		else if (('a' == ch) || ('i' == ch) || ('o' == ch) || ('u' == ch) ||
					('y' == ch) || ('A' == ch) || ('I' == ch) || ('O' == ch) ||
					('U' == ch) || ('Y' == ch)) {
			ws++;
			state = VOWEL;
		}
		else if (('e' == ch) || ('E' == ch)) {
			ws++;
			state = E;
		}
		else
			state = OTHER;
	break;
	

	
	///////////
	case OTHER:
		//cout << "OTHER: " << ch << " s: " << s << " ws: " << ws << endl;
		if (isspace(ch) != 0) {
			w++;
			if((0 == ws) || (1 == ws))
				s += 1;
			else 
				s += ws;
			ws = 0;
			state = WHITESPACE;
		}
		else if (('.' == ch) || (':' == ch) || (';' == ch) || ('?' == ch) || ('!' == ch)) {
			endSentence = true; //sen++;
			w++;
			if((0 == ws) || (1 == ws))
				s += 1;
			else 
				s += ws;
			ws = 0;
			state = PUNCTUATION;
		}
		else if (('a' == ch) || ('i' == ch) || ('o' == ch) || ('u' == ch) ||
					('y' == ch) || ('A' == ch) || ('I' == ch) || ('O' == ch) ||
					('U' == ch) || ('Y' == ch)) {
			ws++;
			state = VOWEL;
		}
		else if (('e' == ch) || ('E' == ch)) {
			ws++;
			state = E;
		}
		else
			state = OTHER;	
	break;

	
	
	////////////////
	case PUNCTUATION:
		//cout << "PUNCTUATION: " << ch << " s: " << s << " ws: " << ws << endl;
		if (isspace(ch) != 0) {
			if (true == endSentence)
				sen++;
			endSentence = false;
			state = WHITESPACE;
		}
		else if (('.' == ch) || (':' == ch) || (';' == ch) || ('?' == ch) || ('!' == ch))
			state = PUNCTUATION;
		else if (('a' == ch) || ('i' == ch) || ('o' == ch) || ('u' == ch) ||
					('y' == ch) || ('A' == ch) || ('I' == ch) || ('O' == ch) ||
					('U' == ch) || ('Y' == ch)) {
			ws++;
			state = VOWEL;
		}
		else if (('e' == ch) || ('E' == ch)) {
			ws++;
			state = E;
		}
		else
			state = OTHER;
		
	break;

	
	//////////
	case VOWEL:
		//cout << "VOWEL: " << ch << " s: " << s << " ws: " << ws << endl;
		if (isspace(ch) != 0) {
			w++;
			if((0 == ws) || (1 == ws))
				s += 1;
			else 
				s += ws;
			ws = 0;
			state = WHITESPACE;
		}
		else if (('.' == ch) || (':' == ch) || (';' == ch) || ('?' == ch) || ('!' == ch)) {
			endSentence = true; //sen++;
			w++;
			if((0 == ws) || (1 == ws))
				s += 1;
			else 
				s += ws;
			ws = 0;
			state = PUNCTUATION;
		}
		else if (('a' == ch) || ('i' == ch) || ('o' == ch) || ('u' == ch) ||
					('y' == ch) || ('A' == ch)  || ('I' == ch) || ('O' == ch) ||
					('U' == ch) || ('Y' == ch)) {
			state = VOWEL;
		}
		else if (('e' == ch) || ('E' == ch)) {
			state = E;
		}
		else
			state = OTHER;
		
		
	break;

	//////////
	case E:
		//cout << "E    : " << ch << " s: " << s << " ws: " << ws << endl;
		if (isspace(ch) != 0) {
			w++;
			if((0 == ws) || (1 == ws))
				s += 1;
			else 
				s = ((s + ws) - 1);
			ws = 0;
			state = WHITESPACE;
		}
		else if (('.' == ch) || (':' == ch) || (';' == ch) || ('?' == ch) || ('!' == ch)) {
			endSentence = true; //sen++;
			w++;
			if((0 == ws) || (1 == ws))
				s += 1;
			else 
				s = ((s + ws) - 1);
			ws = 0;
			state = PUNCTUATION;
		}
		else if (('a' == ch) || ('i' == ch) || ('o' == ch) || ('u' == ch) ||
					('y' == ch) || ('A' == ch) || ('I' == ch) || ('O' == ch) ||
					('U' == ch) || ('Y' == ch)) {
			state = VOWEL;
		}
		else if (('e' == ch) || ('E' == ch)) {
			state = E;
		}
		else
			state = OTHER;
		
	break;

	
	///////////////
	case WHITESPACE:
		//cout << "SPACE: " << ch << " s: " << s << " ws: " << ws << endl;
		if (isspace(ch) != 0)
			state = WHITESPACE;
		else if (('.' == ch) || (':' == ch) || (';' == ch) || ('?' == ch) || ('!' == ch)) {
			endSentence = false;
			state = PUNCTUATION;
		}
		else if (('a' == ch) || ('i' == ch) || ('o' == ch) || ('u' == ch) ||
					('y' == ch) || ('A' == ch) || ('I' == ch) || ('O' == ch) ||
					('U' == ch) || ('Y' == ch)) {
			ws++;
			state = VOWEL;
		}
		else if (('e' == ch) || ('E' == ch)) {
			ws++;
			state = E;
		}
		else
			state = OTHER;
		
					
	break;
	

	
	} //end switch
} //end while loop

	if (state != ERROR) {
		Index = 206.835 - 84.6 * (s/w) - 1.015 * (w/sen);
		Index += .5; //used to round up

		cout << "Syllable Count: " << s << endl;
		cout << "Word Count: " << w << endl;
		cout << "Sentence Count: " << sen << endl;
		cout << "Flesch Readability Index:  " << int(Index) << endl;
	}

in.close();

} //end main