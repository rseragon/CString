#ifndef _UTESTS
#define _UTESTS

#include <stdio.h>
#include "colors.h"

#ifdef assert
  #undef assert
#endif


#if defined (NDEBUG)
  #define assert(EXPR) 

#elif defined(EXIT_ON_FAILURE) // assert with exit
  #define assert(EXPR) if(!(EXPR)) {\
    fprintf(stderr, RED "[FAILED]     \"" #EXPR "\" in Function %s:%d\n" COLOR_RESET, __func__, __LINE__);\
    TEST_STATUS();\
    exit(__LINE__);\
  }

#else  // assert without exit
  #define assert(EXPR) if(!(EXPR)) {\
    fprintf(stderr, RED "[FAILED]     \"" #EXPR "\" in Function %s:%d\n" COLOR_RESET, __func__, __LINE__);\
    return __LINE__;\
  }
#endif /* assert macro */


/* Runs the function */
#define RUN_TEST(FUNC) fprintf(stderr, "[Running]    " #FUNC "\n");\
    TESTS_RUN++;\
    if(FUNC() != 0) {\
        fprintf(stderr, RED "[ERROR]    " #FUNC "\n" COLOR_RESET);\
    }\
    else {\
        TESTS_PASSED++;\
        fprintf(stderr, GREEN "[Passsed]    " #FUNC "\n" COLOR_RESET);\
    }

#define TEST_STATUS() fprintf(stdout, YELLOW "Tests run:    %d\n" GREEN \
                                             "Tests Passed: %d\n" RED\
                                             "Tests Failed: %d\n" COLOR_RESET,\
                                              TESTS_RUN, TESTS_PASSED, (TESTS_RUN - TESTS_PASSED))

/* Helpful debug macros */

#define DEBUG(MSG, ...) fprintf(stdout, "  [DEBUG] (%s:%s:%d) " MSG "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)


/* GLOBAL VARS */
int TESTS_RUN = 0;
int TESTS_PASSED = 0;

#endif /* _UTESTS */
