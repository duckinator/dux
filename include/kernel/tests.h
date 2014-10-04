#ifndef KERNEL_TESTS_H
#define KERNEL_TESTS_H

#include <kernel/core/test_framework.h>
#include <kernel.h>
#include <string.h>

void AddKernelTests();
TestReturn *MemoryAllocationTest();
TestReturn *FrameAllocationTest();
TestReturn *UsedFrameTest();

#endif /* end of include guard: KERNEL_TESTS_H */
