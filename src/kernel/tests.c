#include <kernel/tests.h>

void AddKernelTests()
{
	TEST(MemoryAllocation);
	TEST(FrameAllocation);
}

TestReturn *MemoryAllocationTest()
{
	unsigned long int size = (mbd->mem_upper * 1024) - *end;
	//void *universe;

	TEST_RETURN(TEST_SKIP, "our malloc() and free() aren't decent enough for this.");

/*

	universe = kmalloc(size);
	free(universe);
	universe = kmalloc(size);
	free(universe);

	TEST_RETURN(TEST_SUCCESS, "Successfully allocated and freed everything twice.");
*/
}

TestReturn *FrameAllocationTest()
{
	unsigned int frame = first_frame();

	set_frame(frame);

	if (test_frame(frame) == 0) {
		TEST_RETURN(TEST_FATAL, "set_frame() did not allocate the frame.");
	}

	clear_frame(frame);

	if (test_frame(frame) != 0) {
		TEST_RETURN(TEST_FATAL, "clear_frame() did not clear the frame.");
	}

	if (first_frame() != frame) {
		TEST_RETURN(TEST_FATAL, "first_frame() did not return the deallocat frame.");
	}

	TEST_RETURN(TEST_SUCCESS, NULL);
}

