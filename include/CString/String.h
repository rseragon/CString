#ifndef __String_h
#define __String_h

#include <string.h> // For string functions
#include <stdlib.h> // For malloc 

#if !(__STDC_VERSION__ >= 201112L || __cplusplus >= 199900L)
    #pragma message("Compiling in older versions of C/C++")
    typedef enum bool {FALSE, TRUE};
#else
    #include <stdbool.h>
#endif

typedef enum {strError = -1, strOk = 1} strCode;

struct _string {
  size_t length;    // String length, without \0
  size_t capacity;  // String capacity
  char*  data;      // Character array
  strCode  state;   // Current State of string
};

typedef struct _string *String;

// An error string return type
extern String STR_ERROR;

/* General Macros */

/* Macro define check */
#if defined (strData) || defined (strLenth) || defined (strCapacity) \
  || defined (strState) || defined (strInvalid)
  #error "Macro already defined"
#endif // macro define check end

#define STR_DEFAULT_SIZE 15 // default string size

#define STR_DEFAULT_CAPACITY_INCREMENT 5 // Default increment size

// TODO
//#define STR_CAPACITY_INCREMENT(S) ((S->capacity) + (S->capacity >> 2))

#define strData(S) (S->data)

#define strLength(S) (S->length)

#define strCapacity(S) (S->capacity)

#define strState(S) (S->state)

#define strInvalid(S) (!S || S->state == strError)

/* General Macros End */

/* 
 * Makes a default string with no data
 * Takes in size of string to make
 * returns new String
 */
String make_str(size_t size);

/* Makes a String from char array 
 * Takes in const char *
 * returns new String
 */
String str_from_cstr(const char *str);

/* 
 * copipes a string 
 * returns a copy of another string
 */
String str_copy(const String str);

/*
 * Moves the contents from the second string
 * into the first string, and leaves the seconds
 * string in a undefined valid state 
 *
 * if dest is NULL, then it'll create a new string
 * and move into it
 *
 * Returns the moved string 
 */
String str_move(String dest, String src);

/*
 * Copy only a part of string
 * returns a new sliced string
 */
String str_slice(const String str, long int start, long int end);



/*
 * Sets the given string with the value
 *
 * if the string size is small, it will
 * be automatically increased to meet the required
 * size
 *
 * returns the same string
 */
String str_set(String str, char fill, size_t size);

/*
 * Inserts the char at the given index
 * returns the same string 
 */
String str_insert_char(String str, const char c, size_t idx);

/*
 * Inserts the given string at the given index
 * returns the same? string with inserted string
 *
 * eg:
 * String:   "This is a"
 * toInsert: " string"
 * insert at len-1 = "This is  stringa"
 * insert at len   = "This is a string"
 *
 * RETURN NEW STRING??
 * TODO
 */
String str_insert_cstr(String str, const char* ins, size_t idx);

/*
 * Append a char to current string
 * returns the same string with the appended char
 */
String str_concat_char(String str, const char c);

/* 
 * Append to current string 
 * takes in String and charater array
 * returns concated string String i.e. `str`
 */
String str_concat_cstr(String str, const char * cstr);

/* 
 * Concats the data from str2 into str1
 */
String str_concat_str(String str1, const String str2);

/* Helper functions start */ // wdym by helper func?

/*
 * Compares 2 Strings
 *
 * returns 
 * 0 - unequal 
 * 1 - equal
 */
int str_cmp_str(const String str1, const String str2);

/* compares 2 Strings till n
 *
 * returns 
 * 0 - unequal 
 * 1 - equal
 */
int strn_cmp_str(const String str1, const String str2, size_t n);


/* 
 * Compares the strings for a given len, and from start index
 * str1 indexed with offset of start1
 * str2 indexed with offset of start2
 * len is total amount of string to compare
 *
 * returns
 * 0 - unequal
 * 1 - equal
 */
int str_cmp_slice(const String str1, const String str2, size_t start1, size_t start2, size_t len);

/*
 * Compare strings caselessly
 *
 * returns
 * 0 - unequal
 * 1 - equal
 */
int str_cmp_caseless(const String str1, const String str2);

/*
 * Compare till nth index
 *
 * returns
 * 0 - unequal
 * 1 - equal
 */
int strn_cmp_caseless(const String str1, const String str2, size_t len);

/*
 * Compares a slice
 *
 * returns
 * 0 - unequal
 * 1 - equal
 */
int str_cmp_slice_caseless(const String str1, const String str2,
                           size_t start1    , size_t start2    , size_t len);


/* 
 * Checks if the string starts with the given 
 * sequence
 * returns 1 for true and 0 for false
 */
bool str_starts_with(const String str, const char* pattern);


/* 
 * Checks if the string starts with the given 
 * sequence
 * returns 1 for true and 0 for false
 */
bool str_ends_with(const String str, const char* pattern);


/*
 * returns the index of first of the string
 */
long int str_find_first(String str, const char* pattern);

/*
 * returns the index of the last occurance of the string
 */
long int str_find_last(String str, const char* pattern);


/* replaces the all the occurances with the given string(does it in a new string, 
 * and then moves it into the current string)
 * if replace is NULL, it just removes the pattern from the string
 * returns a the final string
 */
String str_replace_all(String str, const char* pattern, const char* replace);


/* Replaces the first occurance of the pattern
 * returns the same replaced string
 */
String str_replace_first(String str, const char* pattern, const char* replace);

/* Replaces the last occurance of the pattern
 * returns the same replaced string
 */
String str_replace_last(String str, const char* pattern, const char* replace);



/* Applies the fucntion to every character in the string
 * returns the same string
 */
String str_foreach(String str1, int (*apply)(int));

/* 
 * Converts all the charcter in str
 * to upper case characters
 *
 * returns the same string with upper case chars
 */
String str_upper(String str);

/*
 * similar to upper, converts to lower case chars
 *
 * returns the same string with lower case chars
 */
String str_lower(String str);

/*
 * Reverses the given string
 * returns the same string
 */
String str_reverse(String str);


/* Truncates the given string to the length to save space
 * returns a new string if it is truncated
 */
String str_truncate(String str, size_t size);

/* Helper functions end */

/* 
 * Deletes the string (doesn't deallocate it)
 */
void str_delete(String str);

/*
 * Destroys the string
 */
void str_destroy(String str);


#endif // __String_h
