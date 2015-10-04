#ifndef KERNEL_TESTS_H
#define KERNEL_TESTS_H

#include <kernel/core/test_framework.h>
#include <kernel.h>
#include <string.h>

void add_kernel_tests();
TestReturn *memory_allocation_test();
TestReturn *frame_allocation_test();

#endif /* end of include guard: KERNEL_TESTS_H */
