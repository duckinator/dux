#ifndef KERNEL_CORE_TEST_FRAMEWORK_H
#define KERNEL_CORE_TEST_FRAMEWORK_H

#include <stdlib.h>

typedef struct {
	int status;
	const char *message;
} TestReturn;

typedef struct TestCase_s {
	const char *name;
	TestReturn* (*func) ();
	struct TestCase_s *next;
	struct TestCase_s *prev;
} TestCase;

void test_init();
void test_run_all();
TestCase *test_add(const char *n, TestReturn* (*fn)());

#define TEST(NAME) test_add(#NAME, (TestReturn* (*)())NAME##_test)

#define TEST_SUCCESS 0
#define TEST_FAIL    1
#define TEST_FATAL   2
#define TEST_SKIP    3

#define TEST_RETURN(STATUS, MESSAGE) TestReturn *ret = (TestReturn*)kmalloc(sizeof(TestReturn)); \
                                     ret->status = STATUS;                                       \
                                     ret->message = MESSAGE;                                    \
                                     return ret;

#endif /* end of include guard: KERNEL_CORE_TEST_FRAMEWORK_H */
