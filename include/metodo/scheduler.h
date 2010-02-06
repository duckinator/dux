#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <metodo/hal/scheduler.h>

typedef struct SchedulerProcess_s {
  int used;
  struct proc_regs registers;
} SchedulerProcess;

void CoSchedulerHandler(void);
uint32_t CoSchedulerCurProcess(void);
uint32_t CoSchedulerNumProcesses(void);
uint8_t CoSchedulerFirstRun(void);
void CoSchedulerNextProcess(void);
void CoSchedulerSetNumProcesses(uint32_t num);

void HalSchedulerRunProcess(SchedulerProcess proc);

#endif
