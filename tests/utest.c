#include "utest.h"
#include "String.h"

#include <string.h>

//#define EXIT_ON_FAILURE 1

int copy() {
  String s   = str_from_cstr("This is gonna me copied");
  String cpy = str_copy(s);

  assert(strcpy(strData(s), strData(cpy)));

  str_destroy(s);
  str_destroy(cpy);

  return 0;
}

int slice() {
  String s = str_from_cstr("Some String");
  String slice = str_slice(s, 5, 11);

  DEBUG("Sliced String: %s", strData(slice));
  assert(strcmp(strData(slice), "String") == 0)

  str_destroy(s);
  str_destroy(slice);

  return 0;
}

int from_cstr() {

  String s = str_from_cstr("String");

  assert(strcmp(strData(s), "String") == 0);
  
  assert(strLength(s) == 6);

  str_destroy(s);

  return 0;
}

int truncate() {
  String s = str_from_cstr("Some String");
  str_truncate(s, 4);

  assert(strcmp(strData(s), "Some"));

  str_destroy(s);
  return 0;
}

int replace_all() {
  String s = str_from_cstr("abc This is abc string abc");

  str_replace_all(s, "abc", "bcd");

  DEBUG("Final String: %s", strData(s));
  DEBUG("String state: %d", s->state);
  assert(strcmp(strData(s), "bcd This is bcd string bcd") == 0);

  str_destroy(s);

  return 0;
}

int insert_char() {
  String s = str_from_cstr("Strin");
  str_insert_char(s, 'g', 5);

  DEBUG("Inserted char string: %s", strData(s));

  assert(strcmp(strData(s), "String") == 0);

  str_destroy(s);

  return 0;
}

int main(void) {

  RUN_TEST(copy);
  RUN_TEST(slice);
  RUN_TEST(from_cstr);
  RUN_TEST(truncate);
  RUN_TEST(replace_all);
  RUN_TEST(insert_char);
  
}
