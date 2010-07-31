#ifndef CORE_SCHEDULER_H
#define CORE_SCHEDULER_H

#include <stdint.h>
#include <metodo/hal/scheduler.h>

typedef struct SchedulerProcess_s {
  int used;
  struct proc_regs registers;
} SchedulerProcess;

void CoSchedulerHandler(void);
SchedulerProcess *CoSchedulerCurProcess(void);
int64_t CoSchedulerCurProcessId(void);
int64_t CoSchedulerNumProcesses(void);
int64_t CoSchedulerNextProcessLoop(int64_t begin, int64_t end);
int64_t CoSchedulerNextProcess(void);
void CoSchedulerSetNumProcesses(int64_t num);

/* Defined here for simplicitly,
 * however the function is in hal/scheduler.c
 */
void HalSchedulerRunProcess(SchedulerProcess proc);

#endif /* end of include guard: CORE_SCHEDULER_H */
