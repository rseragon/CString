#ifndef _UTESTS
#define _UTESTS

#include <stdio.h>
#include "colors.h"

#ifdef assert
  #undef assert
#endif


#if defined (NDEBUG)
  #define assert(EXPR) 

#elif defined (EXIT_ON_FAILURE) // assert with exit
  #define assert(EXPR) if(!(EXPR)) {\
    fprintf(stderr, RED "[FAILED]     \"" #EXPR "\" in Function %s:%ld\n" WHITE, __func__, __LINE__);\
    exit(__LINE__);\
  }

#else  // assert without exit
  #define assert(EXPR) if(!(EXPR)) {\
    fprintf(stderr, RED "[FAILED]     \"" #EXPR "\" in Function %s:%ld\n" WHITE, __func__, __LINE__);\
    return __LINE__;\
  }
#endif /* assert macro */



#define RUN_TEST(FUNC) fprintf(stderr, "[Running]    " #FUNC "\n");\
  if(FUNC() != 0) {\
    fprintf(stderr, RED "[ERROR]    " #FUNC "\n" WHITE);\
    exit(__LINE__);\
  }\
  else {\
    fprintf(stderr, GREEN "[Passsed]    " #FUNC "\n" WHITE);\
  }


#endif /* _UTESTS */
