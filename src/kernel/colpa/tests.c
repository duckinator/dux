#include <kernel.h>
#include <kernel/colpa/tests.h>
#include <string.h>

/*
 * Colpa (Italian for "fault"):
 *   Test suite for the kernel kernel.
 * 
 * How to add a test:
 *    Assume for this example your test is named "cow"
 * 
 *    TestReturn *TestCow()
 *    {
 *       TEST_RETURN(status, message);
 *    }
 *
 *    status is one of the TEST_* variables in include/kernel/colpa/test.h:
 *     - TEST_SUCCESS (test passed)
 *     - TEST_FAIL    (test failed, nonfatal)
 *     - TEST_FATAL   (test failed, fatal - will not let the system boot)
 *
 *    message is a string containing a normal string/character array
 *    ("Colpa lives!" with quotes in TestColpa())
 * 
 *    If message is an empty string, as in two double-quotes (""), no
 *    message is printed
 */

TestReturn *TestColpa()
{
	TEST_RETURN(TEST_SUCCESS, "Colpa lives!");
}

void ColpaInit()
{
	printf("Initializing Colpa system tests...\n\n");
	TEST(Colpa);
	ColpaRunTests();
}

TestCase *ColpaAddTest(const char *n, TestReturn* (*fn)())
{
	TestCase *t = (TestCase*)kmalloc(sizeof(TestCase));
	TestCase *tmp;
	t->name = n;
	t->func = fn;
	if(firsttest == NULL) {
		firsttest = t;
		firsttest->prev = NULL;
		firsttest->next = NULL;
	}
	if(lasttest == NULL) {
		lasttest = t;
		for(tmp = firsttest; tmp->next != NULL; tmp = tmp->next)
			;
		if(tmp != lasttest) {
			lasttest->prev = tmp;
			tmp->next = lasttest;
		}
	} else {
		lasttest->next = t;
		lasttest->prev = lasttest;
		lasttest = t;
		lasttest->next = NULL;
	}
	return t;
}

void ColpaRunTests()
{
	TestCase *test;
	TestReturn *ret;
	int fatal = 0;
	size_t total_tests_ran = 0;
	size_t total_tests_passed = 0;
	size_t total_tests_failed = 0;
	for(test = firsttest; test != NULL; test=test->next) {
		total_tests_ran++;
		ret = test->func();
		if(ret->status == TEST_SUCCESS) {
			total_tests_passed++;
		} else if(ret->status == TEST_FAIL) {
			total_tests_failed++;
		} else if(ret->status == TEST_FATAL) {
			total_tests_failed++;
			fatal++;
		}
		printf("(%i, %i, %i): `%s' %s", total_tests_ran, total_tests_passed, total_tests_failed, test->name, test_status_messages[ret->status]);
		if(strcmp(ret->message, "") != 0) {
			printf(" with message \"%s\"", ret->message);
		}
		printf("\n");
	}
	printf("Total tests: %i\n"
	       "     Passed: %i\n"
	       "     Failed: %i\n\n", total_tests_ran, total_tests_passed, total_tests_failed, test->name);
	if(fatal) {
		printf("Test encountered a fatal error, not booting.");
		HalShutdown();
	} else if(total_tests_failed > total_tests_passed) {
		printf("Majority of tests failed, not booting.");
		HalShutdown();
	}
}
