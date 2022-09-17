#include "utest.h"
#include "CString/String.h"
#include <stdio.h>
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

int str_insert_first() {

	String s = str_from_cstr("is a string");

	String res = str_insert_cstr(s, "This ", 0);

	assert(strcmp(strData(res), "This is a string") == 0);

	return 0;
}

int str_insert_middle() {

	String s = str_from_cstr("This a string");

	String res = str_insert_cstr(s, "is ", 5);

	assert(strcmp(strData(res), "This is a string") == 0);

	return 0;
}

int str_insert_last() {

	String s = str_from_cstr("This is a");

	String res = str_insert_cstr(s, " string", strLength(s));

	printf("%s\n", strData(res));
	assert(strcmp(strData(res), "This is a string") == 0);

	return 0;
}

String _str_insert_cstr(String str, const char* insert_str, size_t insert_idx);
int str_insert_first_newapi() {

	String s = str_from_cstr("is a string");

	_str_insert_cstr(s, "This ", 0);

	assert(strcmp(strData(s), "This is a string") == 0);
	assert(strLength(s) == 16);

	return 0;
}

int str_insert_middle_newapi() {

	String s = str_from_cstr("This a string");

	_str_insert_cstr(s, "is ", 5);

	assert(strcmp(strData(s), "This is a string") == 0);
	assert(strLength(s) == 16);

	return 0;
}

int str_insert_last_newapi() {

	String s = str_from_cstr("This is a");

	_str_insert_cstr(s, " string", strLength(s));

	assert(strcmp(strData(s), "This is a string") == 0);
	assert(strLength(s) == 16);

	return 0;
}

int main(void) {

	RUN_TEST(char_insert_middle);
	RUN_TEST(char_insert_first);
	RUN_TEST(char_insert_last);

	RUN_TEST(str_insert_first);
	RUN_TEST(str_insert_middle);
	RUN_TEST(str_insert_last);

	RUN_TEST(str_insert_first_newapi);
	RUN_TEST(str_insert_middle_newapi);
	RUN_TEST(str_insert_last_newapi);
	
	TEST_STATUS();
}
