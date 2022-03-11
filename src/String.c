#include "String.h"
#include <string.h> // strncpy, memset, strlen
#include <ctype.h>  // toupper, tolower
#include <stdlib.h> // abs, malloc

// An error state string return type
String STR_ERROR = &(struct _string) {0, 0, 0, strError};


/* 
 * Allocates memory for the string
 * Returns strCode
 */
static int _str_allocator(String str, size_t size)
{

    if(str == NULL) 
        return strError;

    if(size + 1 <= str->capacity) // Nothing to change
        return (str->state = strOk); 

    char *prev_data = str->data;

    size_t curr_len = strLength(str);
    size_t curr_cap = strCapacity(str);

    char *temp = (char *) malloc(size + 1); // Create a new char array, +1 for \0

    if(temp == NULL) 
        return (str->state = strError);

    // Default attributes
    str->length   = 0;
    str->capacity = size + 1;
    str->state    = strOk;

    // If a string already exists in the given String
    // copy it to the new string
    if(curr_len != 0) {
        size_t copy_size = (curr_len >= size) ? size : curr_len;

        strncpy(temp, str->data, copy_size);

        temp[copy_size] = '\0';  // terminate the string

        str->length = copy_size;
        str->capacity = size;
    }
    else {
        memset(temp, '\0', size);
    }

    str->data = temp; // Assign the new string

    free(prev_data); // free up previous data

    return (str->state = strOk);
}


String make_str(size_t size) {
    if(size < 0)
        return STR_ERROR;

    String string = (String) malloc(sizeof(struct _string));
    if(!string)
        return STR_ERROR;

    string->length   = 0;
    string->capacity = 0;
    string->data     = NULL;
    string->state    = strOk;

    if(_str_allocator(string, size) == strOk) 
        return string;
    else
        str_destroy(string);

    return STR_ERROR;
}

String str_from_cstr(const char *cstr)
{
    if(cstr == NULL)
        return STR_ERROR;

    size_t len = strlen(cstr);

    String string = make_str(len);

    if(string == STR_ERROR)
        return STR_ERROR;

    strncpy(string->data, cstr, len);

    string->data[len] = '\0';
    string->length    = len;

    return string;
}


String str_copy(const String str) {

    String temp = make_str(strCapacity(str));

    if(strInvalid(temp))
        return STR_ERROR;

    for(size_t i = 0; i < strLength(str); ++i) {
        temp->data[i] = str->data[i];
    }

    return temp;
}

String str_move(String dest, String src) {
    if(!src && strInvalid(src))
        return STR_ERROR;

    if(!dest)
        dest = (String) malloc(sizeof(struct _string)); 
    else if(dest->data)
        free(dest->data);

    dest->length   = src->length;
    dest->capacity = src->capacity;
    dest->data     = src->data;
    dest->state    = src->state;

    src->length   = 0;
    src->capacity = 0;
    src->data     = NULL; 
    src->state    = strOk;

    return dest;
}

String str_slice(const String str, long int start, long int end) {
    size_t len = end - start;

    String temp = make_str(len);

    for(size_t i = start; i < end; ++i) {
        temp->data[i - start] = str->data[i];
    }
    temp->data[len] = '\0';
    temp->length    = len;
    temp->state     = strOk;

    return temp;
}


String str_set(String str, char fill, size_t size) {
    _str_allocator(str, size); 

    for(size_t idx = 0; idx < size; ++idx) {
        strData(str)[idx] = fill;
    }

    return str;
}


// TODO: Memory leaks?
String str_insert_char(String str, const char c, size_t insert_idx) {

    if(insert_idx > strLength(str)) {
        str->state = strError;
        return str;
    }

    _str_allocator(str, strLength(str) + 2);

    for(size_t curr_idx = strLength(str); curr_idx >= insert_idx; --curr_idx) {
        strData(str)[curr_idx] = strData(str)[curr_idx-1];
    }
    strData(str)[insert_idx] = c;
    strLength(str) += 1;
    strData(str)[strLength(str)] = '\0';

    return str;
}

String str_insert_cstr(String str, const char* ins, size_t idx) {

    String temp = str_slice(str, 0, idx);
    str_concat_cstr(temp, ins);

    //String slice_temp = str_slice(str, idx, strLength(str));

    // TODO: Check working
    temp = str_concat_cstr(temp, strData(str) + idx);

    //str_destroy(slice_temp);

    return temp;
}

// Return a new string?
String str_concat_char(String str, const char c) {
    // Error checking?

    _str_allocator(str, strLength(str)+1); // Tho it's guranteed by me that the string
                                           // will have always an extra char space,
                                           // but still 
                                           // The above statement is false

    strData(str)[strLength(str)]   = c;
    strData(str)[strLength(str)+1] = '\0';
    strLength(str) += 1;


    return str;
}

String str_concat_cstr(String str, const char *cstr) {

    if(!str || !cstr)
        return STR_ERROR;

    int cstrlen = strlen(cstr);

    long int total_length = cstrlen + strLength(str);

    if(_str_allocator(str, total_length + STR_DEFAULT_CAPACITY_INCREMENT) == strError)
        return str;

    for(size_t i = 0; i < cstrlen; i++) {
        str->data[strLength(str) + i] = cstr[i];
    }
    str->data[total_length] = '\0';

    str->length = total_length;
    str->state  = strOk;
    return str;
}

String str_concat_str(String str1, const String str2)  {

    if(!str1 || !str2)
        return STR_ERROR;

    size_t total_length = strLength(str1) + strLength(str2);

    if(_str_allocator(str1, total_length + STR_DEFAULT_CAPACITY_INCREMENT) == strError)
        return str1;

    for(size_t i = 0; i < strLength(str2); i++) {
        str1->data[i + strLength(str1)] = str2->data[i];
    }
    str1->data[total_length] = '\0';

    str1->state = strOk;
    return str1;
}

int str_cmp_str(const String str1, const String str2) {

    if(!str1 || !str2)
        return 0;

    /* Doesn't give total no. eq chars */
    /* Create a compare func, which gives the total no.
     * of equal chars from the given point? */
    if(strLength(str1) != strLength(str2))
        return 0;

    /*
       char *s1 = strData(str1);
       char *s2 = strData(str2);

       int eq = 0; // Total number of equal characters

       while((*s1++ == *s2++) != '\0')
       eq++;

       return eq;
       */

    return str_cmp_slice(str1, str2, 0, 0, strLength(str1));
}

int strn_cmp_str(const String str1, const String str2, size_t n) {
    return str_cmp_slice(str1, str2, 0, 0, n);
}

int str_cmp_slice(const String str1, const String str2, 
        size_t start1    , size_t start2    , size_t len) {

    if(!str1 || !str2)
        return 0;

    if(strLength(str1) < start1+1 || strLength(str2) < start2+1)
        return 0;

    size_t eq = 0; // No. of equal chars

    char *s1 = strData(str1) + start1;
    char *s2 = strData(str2) + start2;

    for(; eq <= len && (*s1 != '\0' && *s1 != '\0' && (*s1++ == *s2++)); ++eq) {

    }
    while(*s1 != '\0' && *s1 != '\0' && (*s1++ == *s2++)) 
        eq++;


    return (eq == len);
}


int str_cmp_slice_caseless(const String str1, const String str2,
        size_t start1    , size_t start2    , size_t len) {

    if(!str1 || !str2)
        return 0;

    if(strLength(str1) < start1+1 || strLength(str2) < start2+2)
        return 0;

    size_t eq = 0;

    char *s1 = strData(str1) + start1;
    char *s2 = strData(str2) + start2;

    while(*s1 != '\0' && *s2 != '\0') {
        if(!(tolower(*s1) - tolower(*s2))) 
            return (eq == len);
        ++eq;
    }

    return (eq == len);
}

// TODO: better algo?
long int str_find_first(String str, const char* pattern) {

    int patLen = strlen(pattern);

    int strIdx = 0;

    while(strIdx < strLength(str)) {
        if(strData(str)[strIdx] == pattern[0]) {
            int eqLen = 0;
            int tempsIdx = strIdx;

            for(int pidx = 0; tempsIdx < strLength(str) && pidx < patLen; ++tempsIdx, ++pidx) {
                if(strData(str)[tempsIdx] != pattern[pidx])
                    break;
                eqLen++;
            }

            if(eqLen == patLen)
                return strIdx;
        }
        strIdx++;
    }

    return -1;

}

// TODO: better algo?
long int str_find_last(String str, const char* pattern) {

    int patLen = strlen(pattern);

    int strIdx = strLength(str)-1;

    while(strIdx >= 0) {

        if(strData(str)[strIdx] == pattern[patLen-1]) {
            int eqLen = 0;
            int tempsIdx = strIdx;

            for(int pidx = patLen-1; tempsIdx >= 0 && pidx >= 0; --tempsIdx, --pidx) {
                if(strData(str)[tempsIdx] != pattern[pidx])
                    break;
                eqLen++;
            }

            if(eqLen == patLen)
                return tempsIdx+1;
        }
        strIdx--;
    }

    return -1;
}

// TODO: Better algo?
// Regex?
String str_replace_all(String str, const char* pattern, const char* replace) {

    int pat_len = strlen(pattern);
    if(pat_len < 1)
        return str;

    //int rep_len = strlen(replace);
    if(!replace)
        replace = "";

    size_t final_len = 0;

    String s = make_str(strLength(str));

    int idx = 0;

    while(idx < strLength(str)) {

        if(idx < strLength(str) - pat_len + 1 && // matches and lesser than length of pattern
                strData(str)[idx] == pattern[0]) {

            int pat_idx = 0;
            for(;pat_idx < pat_len && 
                    strData(str)[idx + pat_idx] == pattern[pat_idx];
                    ++pat_idx) {}

            if(pat_idx == pat_len) {
                str_concat_cstr(s, replace);
                idx += pat_len-1;
                final_len += pat_len;
            }
            else {
                str_concat_char(s, strData(str)[idx]);
                ++final_len;
            }
        }
        else {
            str_concat_char(s, strData(str)[idx]);
            ++final_len;
        }
        ++idx;
    }
    strData(s)[final_len] = '\0';
    strLength(s) = final_len;
    s->state = strOk; 

    str = str_move(str, s);
    str_destroy(s);
    return str;

}

String str_replace_first(String str, const char * pattern, const char* replace) {
    if(!pattern)
        return str;

    int idx = str_find_first(str, pattern);

    if(idx == -1) // Pattern not found
        return str;

    int pat_len = strlen(pattern);
    int rep_len = strlen(replace);

    // delete the pattern
    if(!replace)
        replace = "";

    int len_diff = abs(rep_len - pat_len);

    // In string opeartion: apply the replace in the same string
    if(strLength(str) + len_diff + 1 < strCapacity(str)) { // +1 for \0

        // Move the current string
        for(size_t curr_idx = strLength(str); curr_idx >= idx+pat_len; --curr_idx) 
            strData(str)[curr_idx+len_diff] = strData(str)[curr_idx];   

        // pastie wastie the replace
        for(size_t curr_patidx = 0; curr_patidx < rep_len; ++curr_patidx) 
            strData(str)[curr_patidx + idx] = replace[curr_patidx];

    }
    else { // Create a new string; operate on it; move it to prev string
        String temp = str_slice(str, 0, idx);  
        str_concat_cstr(temp, replace);

        str_concat_cstr(temp, strData(str) + idx + pat_len);

        str = str_move(str, temp);
        str_destroy(temp);
    }

    strLength(str) += len_diff;
    str->state = strOk;
    strData(str)[strLength(str)+1] = '\0';

    return str;
}

String str_replace_last(String str, const char * pattern, const char* replace) {
    if(!pattern)
        return str;

    int idx = str_find_last(str, pattern);

    if(idx == -1)
        return str;

    int pat_len = strlen(pattern);
    int rep_len = strlen(replace);

    // Delete the pattern
    if(!replace)
        replace = "";

    int len_diff = abs(pat_len - rep_len);

    /* Copie Pastie from the above function */
    // In string opeartion: apply the replace in the same string
    if(strLength(str) + len_diff + 1 < strCapacity(str)) { // +1 for \0

        // Move the current string
        for(size_t curr_idx = strLength(str); curr_idx >= idx+pat_len; --curr_idx) 
            strData(str)[curr_idx+len_diff] = strData(str)[curr_idx];   

        // pastie wastie the replace
        for(size_t curr_patidx = 0; curr_patidx < rep_len; ++curr_patidx) 
            strData(str)[curr_patidx + idx] = replace[curr_patidx];

    }
    else { // Create a new string; operate on it; move it to prev string
        String temp = str_slice(str, 0, idx);  
        str_concat_cstr(temp, replace);

        str_concat_cstr(temp, strData(str) + idx + pat_len);

        str = str_move(str, temp);
        str_destroy(temp);
    }

    strLength(str) += len_diff;
    str->state = strOk;
    strData(str)[strLength(str)+1] = '\0';

    return str;
}

String str_foreach(String str, int (*apply)(int)) {

    if(!str)
        return STR_ERROR;

    for(int idx = 0; idx < strLength(str); ++idx) 
        strData(str)[idx] = apply(strData(str)[idx]);

    return str;

}

String str_upper(String str) {
    return str_foreach(str, toupper);
}

String str_lower(String str) {
    return str_foreach(str, tolower);
}

String str_reverse(String str) {
    int len = strLength(str);

    for(int idx = 0; idx < len/2; ++idx) {
        char temp = strData(str)[idx];
        strData(str)[idx] = strData(str)[len-idx-1];
        strData(str)[len-idx-1] = temp;
    }

    strData(str)[len] = '\0';

    return str;
}

String str_truncate(String str, size_t size) {
    if(strLength(str) == size)
        return str;

    _str_allocator(str, size);

    return str;
}

void str_delete(String str) {

    if(!str) // NULL string
        return;

    str->length   = 0;
    str->data[0]  = '\0';
    str->state    = strOk;
    // Capacity will remain the same
}

void str_destroy(String str) {

    if(!str) // NULL string
        return;

    if(str->data)
        free(str->data);

    free(str);
}
