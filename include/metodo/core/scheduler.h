#ifndef CORE_SCHEDULER_H
#define CORE_SCHEDULER_H

#include <buildinfo.h>

#include <stdint.h>

#ifdef DUX_I386
  #include <metodo/hal/i386/scheduler.h>
#elif defined DUX_X86_64
  #include <metodo/hal/x86_64/scheduler.h>
#endif

typedef struct SchedulerProcess_s {
     uint32_t id;
     int used;
     struct proc_regs registers;
     struct SchedulerProcess_s *prev;
     struct SchedulerProcess_s *next;
} SchedulerProcess;

void CoSchedulerHandler(void);
SchedulerProcess *CoSchedulerCurProcess(void);
int32_t CoSchedulerNumProcesses(void);
SchedulerProcess *CoSchedulerPrevProcess(void);
SchedulerProcess *CoSchedulerNextProcess(void);
SchedulerProcess *CoSchedulerAllocateProcess();

/* Defined here for simplicitly,
 * however the function is in hal/scheduler.c
 */
void HalSchedulerRunProcess(SchedulerProcess *proc);

#endif /* end of include guard: CORE_SCHEDULER_H */
