#include "utest.h"
#include "CString/String.h"

int simple_str_format() {

	String s = str_from_fmtstr("test: %d", 1, NULL);

	printf("%s\n", s->data);
	assert(strcmp(strData(s), "test: 1") == 0);
	assert(strLength(s) == 7);

	return 0;
}

int another_small_format() {
	String s = str_from_fmtstr("This string %s", "might get truncated");

	printf("%s\n", s->data);
	assert(strcmp(strData(s),  "This string might get truncated") == 0);

	return 0;
}


int main(void) {

	RUN_TEST(simple_str_format);
	RUN_TEST(another_small_format);

	TEST_STATUS();
}
