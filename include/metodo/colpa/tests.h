#ifndef COLPA_TESTS_H
#define COLPA_TESTS_H

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

extern unsigned int start_tests;
extern unsigned int end_tests;

extern unsigned int start;
extern unsigned int end;

static TestCase *firsttest = NULL;
static TestCase *lasttest = NULL;

static const char *test_status_messages[3] = {
	"passed",
	"failed",
	"failed (FATAL)"
};

void ColpaInit();
void ColpaRunTests();
TestCase *ColpaAddTest(const char *n, TestReturn* (*fn)());

#define TEST(NAME) ColpaAddTest(#NAME, (void*)Test##NAME)

#define TEST_SUCCESS 0
#define TEST_FAIL    1
#define TEST_FATAL   2

#define TEST_RETURN(STATUS, MESSAGE) return ({                                                              \
                                                TestReturn *ret = (TestReturn*)kmalloc(sizeof(TestReturn)); \
                                                ret->status = STATUS;                                       \
                                                ret->message = MESSAGE;                                    \
                                                ret;                                                        \
                                            })

#endif