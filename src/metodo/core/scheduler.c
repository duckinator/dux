#include <metodo/metodo.h>
#include <metodo/scheduler.h>

static SchedulerProcess processes[1024];

static uint32_t current_process = 0;
static uint8_t scheduler_firstrun = 1;
static uint32_t number_of_processes = 0;

void CoSchedulerHandler(void)
{
	if (CoSchedulerFirstRun()) {
		processes[0].used = 1;
		processes[100].used = 1;
		number_of_processes = 101;
	}
	if (!processes[current_process].used) {
		while (!processes[current_process].used) {
			CoSchedulerNextProcess();
		}
	}

	HalSchedulerRunProcess(processes[current_process]);

	if (scheduler_firstrun)
		scheduler_firstrun = 0;

	CoSchedulerNextProcess();
}

uint32_t CoSchedulerCurProcess(void)
{
	return current_process;
}

uint32_t CoSchedulerNumProcesses(void)
{
	return number_of_processes;
}

uint8_t CoSchedulerFirstRun(void)
{
	return scheduler_firstrun;
}

void CoSchedulerNextProcess(void)
{
	current_process++;

	if (current_process >= number_of_processes)
		current_process = 0;
}

void CoSchedulerSetNumProcesses(uint32_t num)
{
	number_of_processes = num;
}
