#include <krnl/spinlock.h>

void KrnlInitializeSpinlock(spinlock_t *lock)
{
	lock->locked = 0;
}

void KrnlWaitForSpinlock(spinlock_t *lock)
{
	while (lock->locked != 0)
		;
}

void KrnlLockSpinlock(spinlock_t *lock)
{
	lock->locked = 1;
}

void KrnlUnlockSpinlock(spinlock_t *lock)
{
	lock->locked = 0;
}
