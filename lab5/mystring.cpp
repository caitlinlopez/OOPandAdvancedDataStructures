#include <iostream>
#include <cassert>
#include <string.h>
#include "mystring.h"
#include <cctype>                                                       

using namespace std;

namespace coen79_lab5 {
    
    // CONSTRUCTORS
    
    // makes a string with the sequence of characters from str[]
    string::string(const char str[]) {
        current_length = strlen(str);                                   // get length of str
        allocated = current_length + 1;                                 // allocate space for length + 1
        characters = new char[allocated];                               // create dynamic memory
        strncpy(characters, str, allocated);                            // copy characters to destination from str
    }

    // makes a string with the character c and null character
    string::string(char c) {
        current_length = 1;                                             // set size to 1 character
        allocated = current_length + 1;                                 // allocate space for length + 1
        characters = new char[allocated];                               // create dynamic memory
        characters[0] = c;                                              // put c into characters[]
        characters[1] = '\0';                                           // add NULL CHAR
    }
    
    // makes a copy of the source string
    string::string(const string& source) {
        current_length = source.current_length;                         // length = size of source
        allocated = source.allocated;                                   
        characters = new char[source.current_length];                   // create a new array with same size
        strncpy(characters, source.characters, source.current_length);  // copy from source to new array
    }

    // destructor: destroys characters[] array on heap
    string::~string() {
        current_length = 0;                                             // all variables = 0
        allocated = 0;
        delete[] characters;                                            // delete characters array on heap
    }

    // MODIFICATION MEMBER FUNCTIONS

    // string obj is concatenated to the end of string `this`
    void string::operator+=(const string& addend) {
        current_length = current_length + addend.current_length;        // add lengths of strings  
        allocated = current_length + 1;                                 // allocated = length + 1
        reserve(allocated);                                             // reserve space
        strncat(characters, addend.characters, addend.current_length);  // then concatenate addend to current string
    }
    
    // array of chars is concatenated to end of string `this`
    void string::operator+=(const char addend[]) {
        current_length = current_length + strlen(addend);               // add lengths of string and char[]
        allocated = current_length + 1;                                 // allocated = length + 1
        reserve(allocated);                                             // reserve space
        strncat(characters, addend, strlen(addend));                    // concatenate addend[] to current string
    }

    // single char is concatenated to end of string `this`
    void string::operator+=(char addend) {
        current_length += 1;                                            // increase size of length by one
        allocated = current_length + 1;                                 // increase allocated by one
        reserve(allocated);                                             // reserve space
        characters[current_length] = addend;                            // add character to end of string
    }

    // all functions work until n characters are in the string
    void string::reserve(size_t n) {
        char* tmp = new char[n];                                        // create new heap array with size n
        if (characters != NULL) {                                       // check that calling string isn't empty
            strncpy(tmp, characters, current_length);                   // copy characters -> tmp
            delete[] characters;                                        // delete old characters array
        }
        characters = tmp;                                               // character <- tmp
    }

    // assigns source to a pointer of changed string `this`
    string& string::operator=(const string& source) {
        this->dlt(0, current_length);                                   // delete all characters in `this` string
        if (current_length != source.current_length) {                  // check if we need to change size of `this` string
            allocated = source.allocated;                               // adjust allocated to source's allocated
            reserve(allocated);                                         // then reserve more/less size to source's size
        }
        strncpy(characters, source.characters, source.current_length);  // copy source-->this
        current_length = source.current_length;                         // update length with source's length
        return *this;                                                   // return the dereferenced `this`
    }
    
    // inserts a source string into `this` string at given index `position` [no replacement]
    void string::insert(const string& source, unsigned int position) {
        assert(position <= length());                                   // check that we're not inserting outside of length of array   
        size_t total_length = current_length + source.current_length;   // used to hold total length of both strings
        if (allocated < (total_length) )                                // check if we need to reserve more array size
            reserve(total_length);                                      // reserve more array size
        for(int i = length(); i > position; i--)                        // shift right half of string to insert characters in
            characters[i] = characters[i-1];
        for(int i = 0; i < source.length(); i++)                        // for each character in source.length()
            characters[position+i] = source.characters[i];              // input source characters starting at position in characters[]
        current_length = total_length;                                  // update current_length
    }
    
    // deletes `num` amount of characters starting at index `position`
    void string::dlt(unsigned int position, unsigned int num) {
        assert( (position + num) <= length() );                         // check that we're not deleting past length of array
        for(int i = position; i < length(); i++)                        // start at position, and increment
            characters[i] = characters[i+num];                          // to-be-deleted substring replaced one by one by substring after t-b-d substring
        current_length = current_length -num;                           // change size of length
    }
    
    // the characters in `this` string starting at index `position` replaced by character c in `this`
    void string::replace(char c, unsigned int position) {
        assert(position < length());                                    // check that replacing position isn't past the array length
        characters[position] = c;                                       // just replace character at position with char c
    }
    
    // the characters in `this` string are replaced by source string at index `position`
    void string::replace(const string& source, unsigned int position) {
        assert( (position + source.length() ) <= length() );            // check that we're not replacing past length of array
        int i, j;
        for(i = position, j = 0; i < (position + source.length()); i++) // start i at position, j is for iterating through source
            characters[i] = source[j++];                                // replace character at i with source[j]
    }
    
    // CONSTANT MEMBER FUNCTIONS

    // returns the character at specified position of string
    char string::operator[](size_t position) const {
        assert(position < length());                                    // check that we're not looking past length of array
        return characters[position];                                    // return the character at position
    }

    // return index of first instance of character c in `this` string
    int string::search(char c) const {
        for(int i = 0; i < length(); i++) {                             // loop through entire array
            if (characters[i] == c)                                     // if we find the character
                return i;                                               // return the index where it is at
        }
        return -1;                                                      // if we don't find character, return -1
    }

    // returns index of first instance of substring in `this` string
    int string::search(const string& substring) const {
        char* temp = strstr(characters, substring.characters);          // strstr returns a pointer to where substring starts in string
        if(temp != NULL) {                                              // check that pointer isn't null (strstr didn't fail)
            return temp[0] - characters[0];                             // take location of temp subtract location of characters
        }
        return -1;                                                      // if strstr failed (aka substring doesn't exist), return -1
    }
    
    // returns how many occurances of character c exists in `this` string
    unsigned int string::count(char c) const {
        unsigned int counter = 0;
        for(int i = 0; i < length(); i++) {                             // loop through array
            if(characters[i] == c)                                      // if we find character c
                counter++;                                              // increment counter
        }
        return counter;
    }

    // NON-MEMBER FUNCTIONS
    // returns the concatenation of string s1 and s2
    string operator+(const string& s1, const string& s2) {
        string temp;                                                    // create temporary string
        temp.reserve(s1.length()+s2.length()+1);                        // reserve/allocate s1+s2+1 size
        temp += s1;                                                     // call overloaded += operator
        temp += s2;                                                     // call overloaded += operator
        return temp;                                                    // return our temporary string
    }

    // returns the concatenation of string s1 and char array addend[]
    string operator +(const string& s1, const char addend[ ]) {
        string temp;                                                    // same code as above
        temp.reserve(s1.length()+strlen(addend)+1);                     // use strlen on char array
        temp += s1;                                                     // call overloaded += operator
        temp += addend;                                                 // call overloaded += operator
        return temp;                                                    // return our temporary string
    }

    // a string has been read from istream ins and returns a new istream object with the
    // sequence of characters without whitespace (no blanks, newlines, tabs)
    std::istream& operator >> (std::istream& ins, string& target) {
        char* buffer = new char[100];                                   // create new buffer
        while(ins && isspace(ins.peek()))                               // this while loop is a two-liner
            ins.ignore();                                               // code to ignore all whitespace
        ins >> buffer;                                                  // write newly no-whitespaced input to buffer
        target = string(buffer);                                        // buffer is written to target
        return ins;                                                     // return istream object
    }

    // FRIEND FUNCTIONS
    // returns a new ostream object that contains the sequence of characters from source
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        outs << source.characters;                                      // put the sequence source.characters into outs
        return outs;                                                    // return ostream object
    }

    bool operator ==(const string& s1, const string& s2)                // checks if the two strings are the same
        { return (strcmp(s1.characters, s2.characters) == 0); }

    bool operator !=(const string& s1, const string& s2)                // checks if the two strings are not the same
        { return (strcmp(s1.characters, s2.characters) != 0); }
    
    bool operator > (const string& s1, const string& s2)                // checks if string s1 has the higher ascii values
        { return (strcmp(s1.characters, s2.characters) > 0); }
    
    bool operator < (const string& s1, const string& s2)                // checks if string s2 has the higher ascii values
        { return (strcmp(s1.characters, s2.characters) < 0); }
    
    bool operator >=(const string& s1, const string& s2)                // checks if equal or if s1 is larger
        { return ((s1 > s2) || (s1 == s2)); }                           // reuse our > and == operator
    
    bool operator <=(const string& s1, const string& s2)                // checks if equal or if s2 is larger
        { return ((s1 < s2) || (s1 == s2)); }                           // reuse our < and == operator
}