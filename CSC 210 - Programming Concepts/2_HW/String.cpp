//: String.cxx (reference count version) - implementation of an abstract data
//                 type String (adapted from "Learning C++" by Neill Graham)

// Matt Stallmann
// (prehistoric)

#include "String.h"
#include <ctype.h>			// for isspace()
#include <assert.h>
#include <string.h>                     // for search
const int BUFFER_SIZE = 32;
// size of each new chunk of storage allocated while reading a string;
// for best performance, should be set so that 90-95% of strings are less
// than this size, and a power of 2. (set to 4 for leak testing)

// CLASSINV: Each nonempty instance of class String has an allocated
//           character array, and this array is deallocated when
//           refcount goes to 0.  The field refcount is the number of
//           String instances that use this same array to store their
//           character array.
//
//           bufferlength == 0 <--> buffer = 0 <--> the string is empty
//           bufferlength > 0 --> buffer[1], ... , buffer[bufferlength]
//                                all contain non-null characters
//                                && buffer[0] == refcount
//                                && buffer[bufferlength + 1] == NULL
//           buffer is an allocated string with bufferlength + 2 characters
//
// NOTE: the strings stored in the buffer are terminated by the null
//       character (PTR makes use of this fact) 

// private members of class String:
// int compare(const String& right) const;
//      behaves like strcmp (returns -1, 0, or 1)
// int bufferlength;
// char* buffer;

int CstringLength(const char* stg)
// POST: FCTVAL == number of non-null characters in stg
{
   if (stg != 0) {
      int i = 0;
      while (stg[i] != '\0') i++;
      return i;
   }
   else return 0;
}

// various constructors

String::String()
   // POST: bufferlength == 0 && buffer == 0
{
   bufferlength = 0;
   buffer = 0;
}

String::String(const String& stg)
   // POST: bufferlength == stg.bufferlength && buffer == stg.buffer
   //       (copy constructor, used implicitly during parameter passing and
   //       returns from functions)
{
   bufferlength = stg.bufferlength;
   if (stg.bufferlength == 0)
     buffer = 0;
   else {
     (*stg.buffer)++;
     buffer = stg.buffer;
   }
}

String::String(const char* stg)
   // POST: bufferlength == length of stg && buffer contains a copy of stg
{
  bufferlength = CstringLength(stg);
  if (bufferlength == 0)
    buffer = 0;
  else {
    buffer = new char[bufferlength + 2];
    assert(buffer != 0);
    for (int i = 0; i < bufferlength; i++)
      buffer[i+1] = stg[i];
    buffer[bufferlength+1] = '\0';
    *buffer = 1;
  }
}

String::~String()
   // POST: buffer<entry> is deallocated
{
  if (buffer != 0 && --*buffer == 0) delete [] buffer;
}

bool String::operator==(const String& right) const
   // POST: FCTVAL == true iff this string == right
{
  return (compare(right) == 0);
}

bool String::operator!=(const String& right) const
   // POST: FCTVAL == true iff this string == right
{
   return (!compare(right) == 0);
}

bool String::operator>(const String& right) const
   // POST: FCTVAL == true iff this string comes later (lexicographically)
   //                 than 'right'
{
   return (compare(right) == 1);
}

bool String::operator<(const String& right) const
   // POST: FCTVAL == true iff this string comes earlier (lexicographically)
   //                 than 'right'
{
   return (compare(right) == -1);
}

String& String::operator=(const String& right)
   // POST: bufferlength == right.bufferlength && buffer == right.buffer
   //       (insures that strings are copied during assignment)
   //       buffer<entry> is deallocated
{
  if (buffer != 0 && --*buffer == 0) delete [] buffer;
  bufferlength = right.bufferlength;
  if (right.buffer == 0)
    buffer = 0;
  else {
    (*right.buffer)++;
    buffer = right.buffer;
  }
  return *this;
}

void String::operator+=(const String& right)
   // POST: bufferlength == bufferlength<entry> + right.bufferlength &&
   //       buffer == buffer<entry> followed by right.buffer
{
  if (right.buffer == 0)
    return;
  if (buffer == 0) {
    (*right.buffer)++;
    buffer = right.buffer;
    bufferlength = right.bufferlength;
    return;
  }

  char* new_string = new char[bufferlength + right.bufferlength + 2];
  assert(new_string != 0);
  for (int i = 1; i < bufferlength + 1; i++)
    new_string[i] = buffer[i];
  for (int j = 1; j < right.bufferlength + 1; j++)
    new_string[bufferlength + j] = right.buffer[j];
  new_string[bufferlength + right.bufferlength + 1] = '\0';
  if (buffer != 0 && --*buffer == 0) delete [] buffer;
  buffer = new_string;
  bufferlength += right.bufferlength;
}

void String::operator+=(char c)
   // POST: bufferlength == bufferlength<entry> + 1 &&
   //       buffer == buffer<entry> followed by char c
{
  bufferlength++;
  char* new_string = new char[bufferlength + 2];
  assert(new_string != 0);
  for (int i = 1; i < bufferlength; i++)
    new_string[i] = buffer[i];
  new_string[bufferlength] = c;
  new_string[bufferlength + 1] = '\0';
  if (buffer != 0 && --*buffer == 0) delete [] buffer;
  buffer = new_string;
}

String String::operator+(const String& right) const
   // POST: FCTVAL == a new string which is this string concatenated with right
   //       (both original strings remain intact)
{
  if (right.bufferlength == 0)
    return *this;
  else if (bufferlength == 0)
    return right;
  else {
    String new_String;
    new_String.bufferlength = bufferlength + right.bufferlength;
    new_String.buffer = new char[new_String.bufferlength + 2];
    assert(new_String.buffer != 0);
    for (int i = 1; i < bufferlength + 1; i++)
      new_String.buffer[i] = buffer[i];
    for (int j = 1; j < right.bufferlength + 1; j++)
      new_String.buffer[bufferlength + j] = right.buffer[j];
    new_String.buffer[bufferlength + right.bufferlength + 1] = '\0';
    *new_String.buffer = 1;
    return new_String;
  }
}

int String::compare(const String& right) const
// POST: FCTVAL == -1 if this string precedes 'right' (lexicographically)
//                  0 if this string is the same as 'right'
//                  1 if this string follows 'right' (lexicographically)
{
   int min_length = bufferlength > right.bufferlength ? right.bufferlength
                                                      : bufferlength;
   // ASSERT: min_length == min(bufferlength, right.bufferlength)

   for (int i = 1; i < min_length + 1; i++) {
      // INV (before test) buffer[1..i-1] == right.buffer[1..i-1]
      if (buffer[i] > right.buffer[i]) return 1;
      if (buffer[i] < right.buffer[i]) return -1;
   }

   // ASSERT: buffer[1..min_length] == right.buffer[1..min_length]

   if (bufferlength > right.bufferlength) return 1;
   if (bufferlength < right.bufferlength) return -1;

   // ASSERT: buffer[1..min_length] == right.buffer[1..min_length]
   //         && bufferlength == right.bufferlength == min_length

   return 0;
}

char* reallocate(char* old_buffer, int current_length, int new_length)
// PRE:  old_buffer is either 0 or a pointer to allocated storage
// POST: FCTVAL == pointer to new_buffer (allocated) holding new_length
//                 characters
//       new_buffer[0..current_length-1] == old_buffer[0..current_length-1]
//       storage pointed to by old_buffer has been deleted
{
   char* new_buffer = new char[new_length];
   assert(new_buffer != 0);
   for (int i = 0; i < current_length; i++)
      new_buffer[i] = old_buffer[i];
   delete [] old_buffer;
   return new_buffer;
}

istream& operator>>(istream& in, String& stg)
   // POST: stg == the next string from the istream 'in' (delimited by white
   //              space)
   //       FCTVAL == 'in' with all characters of stg removed
   //       stg.buffer<entry> is deallocated
   //
   // CAUTION: end of input is not handled (fixed 4-NOV-93)
{
   char* temp_buffer = 0;
   char c;
   int length = 0;

   in >> ws;

   // ASSERT: first character of 'in' is not white space
   //         (i.e. is the first character in a legal string)

   while ((c = in.peek()) != EOF && !isspace(c)) {
      in.get();
      if (length % BUFFER_SIZE == 0)
         temp_buffer = reallocate(temp_buffer, length, length + BUFFER_SIZE);
      temp_buffer[length++] = c;
   }

   stg.bufferlength = length;
   if (stg.buffer != 0 && --(*stg.buffer) == 0) delete [] stg.buffer;

   if (length == 0) {
      stg.buffer = 0;
      return in;
   }

   stg.buffer = new char[length + 2];
   assert(stg.buffer != 0);
   for (int i = 0; i < length; i++)
      stg.buffer[i + 1] = temp_buffer[i];
   stg.buffer[length + 1] = '\0';
   *stg.buffer = 1;

   delete [] temp_buffer;
   return in;
}

ostream& operator<<(ostream& out, const String& stg)
   // POST: stg has been concatenated to 'out'
   //       FCTVAL == 'out'<entry> with stg concatenated
{
   for (int i = 1; i < stg.bufferlength + 1; i++)
      out.put(stg.buffer[i]);
   return out;
}

int length(String s)
// PRE: s is a String instance
// POST: FCTVAL == length(s)
{
   return s.bufferlength;
}

const char* PTR(String s)
// PRE: s is a String instance
// POST: FCTVAL == pointer to a null terminated string of internal
//                 representation
{
  if (s.buffer == 0) return "";
  return (s.buffer + 1);
}

