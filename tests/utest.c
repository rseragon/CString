//#define EXIT_ON_FAILURE 1

#include "utest.h"
#include "String.h"

#include <string.h>


int make() {
    String s = make_str(10);

    assert(strCapacity(s) == 11);

    str_destroy(s);

    return 0;
}

int copy() {
    String s   = str_from_cstr("This is gonna me copied");
    String cpy = str_copy(s);

    assert(strcmp(strData(s), strData(cpy)) == 0);

    str_destroy(s);
    str_destroy(cpy);

    return 0;
}

int move() {
    String s = str_from_cstr("Some random string");
    String other = str_move(NULL, s);

    assert(strcmp(strData(other), "Some random string") == 0);

    str_destroy(other);
    str_destroy(s);
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


    /* Null replace */
    String temp = str_from_cstr("Some String String String string");
    str_replace_all(temp, "String ", NULL);

    DEBUG("Final String: %s", strData(temp));

    assert(strcmp(strData(temp), "Some string") == 0);

    str_destroy(temp);

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

int replace_first() {
    String s = str_from_cstr("Some string string");
    str_replace_first(s, "string", "String");

    DEBUG("First replaced: %s", strData(s));

    assert(strcmp(strData(s), "Some String string") == 0);

    str_destroy(s);
    return 0;
}

int replace_last() {
    String s = str_from_cstr("Some string string");
    str_replace_last(s, "string", "String");

    DEBUG("First replaced: %s", strData(s));

    assert(strcmp(strData(s), "Some string String") == 0);

    str_destroy(s);
    return 0;
}

int main(void) {
    
    RUN_TEST(make);
    RUN_TEST(copy);
    RUN_TEST(move);
    RUN_TEST(slice);
    RUN_TEST(from_cstr);
    RUN_TEST(truncate);
    RUN_TEST(replace_all);
    RUN_TEST(insert_char);
    RUN_TEST(replace_first);
    RUN_TEST(replace_last);

    TEST_STATUS();

}
