#include "utest.h"
#include "CString/String.h"
#include <stdio.h>

int set_string() {
	String s = make_str(10);

	str_set(s, 'A', 0, 11); // Makes 11 A's

	assert(strcmp(strData(s), "AAAAAAAAAAA") == 0);
	assert(strLength(s) == 11);

	return 0;
}

int apply(int c) {
	return 'B';
}

int for_each() {

	String s = make_str(10);

	str_set(s, 'A', 0, 11); // Makes 11 A's
	
	str_foreach(s, apply);

	assert(strcmp(strData(s), "BBBBBBBBBBB") == 0);
	assert(strLength(s) == 11);
	return 0;
}

int delete_str() {
	String s = make_str(10);

	assert(strLength(s) == 0);
	assert(strCapacity(s) == 11); // for \0
	assert(strData(s));

	str_delete(s);
	
	assert(strLength(s) == 0);
	assert(strCapacity(s) == 11);
	assert(*strData(s) == '\0');

	return 0;
}

int main() {

	RUN_TEST(set_string);
	RUN_TEST(for_each);
	RUN_TEST(delete_str);

	TEST_STATUS();
}
