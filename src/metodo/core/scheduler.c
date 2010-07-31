#include <metodo/metodo.h>
#include <metodo/core/scheduler.h>

SchedulerProcess *processes = NULL;

static int64_t current_process_id = 0;
static uint8_t scheduler_firstrun = 1;
static int64_t number_of_processes = 0;

void CoSchedulerHandler(void)
{
	if (processes == NULL) {
		processes = kmalloc(sizeof(SchedulerProcess)*1024);
	}

	if (scheduler_firstrun) {
		processes[0].used = 1;
		processes[100].used = 1;
		number_of_processes = 101;

		scheduler_firstrun = 0;
	}

	HalSchedulerRunProcess(processes[current_process_id]);

	current_process_id = CoSchedulerNextProcess();
}

int64_t CoSchedulerCurProcessId(void)
{
	return current_process_id;
}

SchedulerProcess CoSchedulerCurProcess(void)
{
	return processes[current_process_id];
}

int64_t CoSchedulerNumProcesses(void)
{
	return number_of_processes;
}

int64_t CoSchedulerNextProcessLoop(int64_t begin, int64_t end)
{
	int64_t i;

	if (end == -1) {
		end = number_of_processes;
	}

	if (begin == end) {
		if(end > number_of_processes) {
			end = number_of_processes;
		} else {
			begin = 0;
			end = number_of_processes;
		}
	}

	i = begin;

	// Try processes with ids from begin to end
	while(!processes[i].used) {
		if(i > end) // If we are past the last process in the group, return -1
			return -1;
		i++;
	}

	return i;
}

int64_t CoSchedulerNextProcess(void)
{
	int64_t result;
	int64_t last_process = current_process_id;

	// Try processes current_process_id -> (number_of_processes-1)
	result = CoSchedulerNextProcessLoop(last_process+1, -1);

	// If result == -1, try again from 0 -> last_process
	if(result == -1) {
		result = CoSchedulerNextProcessLoop(0, last_process);
	}

	// If result is still -1, either something exploded or there's no processes
	if(result == -1) {
		printf("\n\nNo processes");
		while(1);
	}

	return result;
}

void CoSchedulerSetNumProcesses(int64_t num)
{
	number_of_processes = num;
}
