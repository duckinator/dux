#ifndef CORE_SCHEDULER_H
#define CORE_SCHEDULER_H

#include <stdint.h>

#if I386
  #include <metodo/hal/i386/scheduler.h>
#endif

typedef struct SchedulerProcess_s {
  int used;
  struct proc_regs registers;
} SchedulerProcess;

void CoSchedulerHandler(void);
SchedulerProcess *CoSchedulerCurProcess(void);
int32_t CoSchedulerCurProcessId(void);
int32_t CoSchedulerNumProcesses(void);
int32_t CoSchedulerNextProcessLoop(int32_t begin, int32_t end);
int32_t CoSchedulerNextProcess(void);
void CoSchedulerSetNumProcesses(int32_t num);

/* Defined here for simplicitly,
 * however the function is in hal/scheduler.c
 */
void HalSchedulerRunProcess(SchedulerProcess *proc);

#endif /* end of include guard: CORE_SCHEDULER_H */
