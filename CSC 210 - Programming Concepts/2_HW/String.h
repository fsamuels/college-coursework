//: String.h - definition of an abstract data type String
//             (adapted from "Classic Data Structures in C++"
//              by Timothy A. Budd)
// 11-11-93 modification for use with X11 procedure in Xpackage.C by J.T.Cohen
// Version 0.2 (11-18-93):
//     - handles end of file correctly with >> operator
//     - handles assignment operator correctly for x = x and x = y = z
//     - allows conversion to 'const char*' via the PTR function
//     - length implemented only as a friend function
// 11-4-94 modification to get rid of unnecessary char* handling
//         (M. Stallmann)

#ifndef String_H
#define String_H

#include <iostream.h>

class String {
   //           CLASSINV: automatic string instances are safe
   //           from dangling pointer and inaccessible object problems.
   //           (this is true as long as the PTR function is used only
   //            to pass const char* parameters to other functions).
   //
   //           Individual characters of strings may not be modified.

public:
   // various constructors

   String();
   // POST: length() == 0 && this string is empty 

   String(const String& stg);
   // POST: length() == stg.length() && this string is a copy of stg
   //       (copy constructor, used implicitly during parameter passing and
   //       returns from functions)

   String(const char* stg);
   // POST: length(this string) == length of stg
   //       && this string is a copy of stg

   // the destructor
   ~String();

   bool operator==(const String& right) const;
   // POST: FCTVAL == true iff this string == right

   bool operator!=(const String& right) const;
   // POST: FCTVAL == false iff this string == right

   bool operator>(const String& right) const;
   // POST: FCTVAL == true iff this string comes later (lexicographically)
   //                 than 'right'

   bool operator<(const String& right) const;
   // POST: FCTVAL == true iff this string comes earlier (lexicographically)
   //                 than 'right'

   String& operator=(const String& right);
   // POST: length(this string) == length(right) && this string is a copy
   //       of right (ensures that strings are copied during assignment)

   void operator+=(const String& right);
   // POST: length(this string) == length(this string)<entry> + length(right)
   //       && this string has right concatenated to it

   void operator+=(char c);
   // POST: length(this string) == length(this string)<entry> + 1 &&
   //       this string has c concatenated to it

   String operator+(const String& right) const;
   // POST: FCTVAL == a new string which is this string concatenated with right
   //       (both original strings remain intact)

   friend istream& operator>>(istream& in, String& stg);
   // POST: stg == the next string from the istream 'in' (delimited by white
   //              space)
   //       FCTVAL == 'in' with all characters of stg removed

   friend ostream& operator<<(ostream& out, const String& stg);
   // POST: stg has been concatenated to 'out'
   //       FCTVAL == 'out'<entry> with stg concatenated

   // The following are designed to be used with X11 routines or any
   // other libraries that require char* input parameters (friend
   // functions rather than class methods are used to make the syntax
   // easier to read).

   friend int length(String s);
   // PRE: s is a String instance
   // POST: FCTVAL == number of non-null characters in s

   friend const char* PTR(String s);
   // PRE: s is a String instance
   // POST: FCTVAL == pointer to a non-null character buffer of contents
   //                 of String instance's buffer

private:
   int compare(const String& right) const;
   int bufferlength;
   char* buffer;
};
#endif
