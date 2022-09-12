#define EXIT_ON_FAILURE 1

#include "utest.h"
#include <string.h>
#include "CString/String.h"

int starts_with() {

	String s = str_from_cstr("This is a string");
	char* ptn1 = "This";
	char* ptn2 = "This ";
	char* ptn3 = "Thsi";

	assert(str_starts_with(s, ptn1) == 1);
	assert(str_starts_with(s, ptn2) == 1);
	assert(str_starts_with(s, ptn3) == 0);

	return 0;
}

int ends_with() {
	String s = str_from_cstr("This is another string");
	char* ptn1 = "string";
	char* ptn2 = " string";
	char* ptn3 = "strina";

	assert(str_ends_with(s, ptn1) == 1);
	assert(str_ends_with(s, ptn2) == 1);
	assert(str_ends_with(s, ptn3) == 0);

	return 0;
}

int main(void) {
	RUN_TEST(starts_with);
	RUN_TEST(ends_with);

	TEST_STATUS();
}
