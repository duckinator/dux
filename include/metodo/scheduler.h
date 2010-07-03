#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <metodo/hal/scheduler.h>

typedef struct SchedulerProcess_s {
  int used;
  int id;
  struct proc_regs registers;
} SchedulerProcess;

void CoSchedulerHandler(void);
SchedulerProcess CoSchedulerCurProcess(void);
uint32_t CoSchedulerNumProcesses(void);
void CoSchedulerFirstRun(void);
uint32_t CoSchedulerNextProcessLoop(int begin, int end);
uint32_t CoSchedulerNextProcess(void);
void CoSchedulerSetNumProcesses(uint32_t num);

void HalSchedulerRunProcess(SchedulerProcess proc);

#endif
