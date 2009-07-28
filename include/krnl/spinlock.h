#ifndef SPINLOCK_CA3J3MAT

#define SPINLOCK_CA3J3MAT

#include <stdint.h>

typedef struct spinlock_t {
	uint8_t locked;
} spinlock_t;

void KrnlInitializeSpinlock(spinlock_t *lock);
void KrnlWaitForSpinlock(spinlock_t *lock);
void KrnlLockSpinlock(spinlock_t *lock);
void KrnlUnlockSpinlock(spinlock_t *lock);

#endif /* end of include guard: SPINLOCK_CA3J3MAT */
