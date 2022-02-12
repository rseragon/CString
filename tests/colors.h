#ifndef __COLORS_H
#define __COLORS_H

// TODO Make it cross compatable

#ifndef ANSI_TERMINAL
  #ifdef _WIN32
    #define ANSI_TERMINAL 0
  #else
    #define ANSI_TERMINAL 1
  #endif
#endif

#if ANSI_TERMINAL
  #define WHITE "\033[0;37m"
  #define RED "\033[0;31m"
  #define GREEN "\033[0;32m"
  #define YELLOW "\033[0;33m"
  #define COLOR_RESET "\x1b[0m"
#else
  #define WHITE ""
  #define RED ""
  #define GREEN ""
  #define YELLOW ""
  #define COLOR_RESET ""
#endif /* ANSI_TERMIAL */

#endif /* __COLORS_H */
