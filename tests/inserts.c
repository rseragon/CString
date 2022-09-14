#include "utest.h"
#include "CString/String.h"
#include <string.h>


int char_insert_middle() {

	String s = str_from_cstr("ACD");
	char c = 'B';

	str_insert_char(s, c, 1);

	assert(!strInvalid(s));
	assert(strcmp(strData(s), "ABCD") == 0);
	assert(strLength(s) == 4);

	return 0;
}


int char_insert_first() {

	String s = str_from_cstr("BCD");
	char c = 'A';

	str_insert_char(s, c, 0);

	assert(!strInvalid(s));
	assert(strcmp(strData(s), "ABCD") == 0);
	assert(strLength(s) == 4);

	return 0;
}

int char_insert_last() {

	String s = str_from_cstr("ABC");
	char c = 'D';

	str_insert_char(s, c, 3);

	assert(!strInvalid(s));
	assert(strcmp(strData(s), "ABCD") == 0);
	assert(strLength(s) == 4);

	return 0;
}

int main(void) {

	RUN_TEST(char_insert_middle);
	RUN_TEST(char_insert_first);
	RUN_TEST(char_insert_last);
	
	TEST_STATUS();
}
