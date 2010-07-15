#ifndef CORE_SCHEDULER_H
#define CORE_SCHEDULER_H

#include <stdint.h>
#include <metodo/hal/scheduler.h>

typedef struct SchedulerProcess_s {
  int used;
  struct proc_regs registers;
} SchedulerProcess;

void CoSchedulerHandler(void);
SchedulerProcess CoSchedulerCurProcess(void);
uint32_t CoSchedulerCurProcessId(void);
uint32_t CoSchedulerNumProcesses(void);
uint32_t CoSchedulerNextProcessLoop(uint32_t begin, uint32_t end);
uint32_t CoSchedulerNextProcess(void);
void CoSchedulerSetNumProcesses(uint32_t num);

#endif /* end of include guard: CORE_SCHEDULER_H */
