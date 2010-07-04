#include <metodo/metodo.h>
#include <metodo/scheduler.h>

static SchedulerProcess processes[1024];

static uint32_t current_process_id = 0;
static uint8_t scheduler_firstrun = 1;
static uint32_t number_of_processes = 0;

void CoSchedulerHandler(void)
{
	if (scheduler_firstrun) {
		processes[0].used = 1;
		processes[100].used = 1;
		number_of_processes = 101;

		scheduler_firstrun = 0;
	}

	HalSchedulerRunProcess(processes[current_process_id]);

	CoSchedulerNextProcess();
}

uint32_t CoSchedulerCurProcessId(void)
{
	return current_process_id;
}

SchedulerProcess CoSchedulerCurProcess(void)
{
	return processes[current_process_id];
}

uint32_t CoSchedulerNumProcesses(void)
{
	return number_of_processes;
}

uint32_t CoSchedulerNextProcessLoop(uint32_t begin, uint32_t end)
{
	uint32_t i;

	if (end == -1) {
		end = number_of_processes-1;
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
//		printf("%d is not runnnig, checking process %d...\n", i-1, i);

		if(i > end) // If we are past the last process in the group
			return -1; // return -1

		i++;
	}

/*printf("Trying from %i to %i\n", i, end);
printf("processes[100].used == %i\n", processes[100].used);
printf("i == %i\n", i);
while(1);*/

	return i;
}

uint32_t CoSchedulerNextProcess(void)
{
	uint32_t result;
	uint32_t last_process = current_process_id;

	// Try processes current_process_id -> (number_of_processes-1)
	result = CoSchedulerNextProcessLoop(last_process+1, -1);

	// If result == -1, try again from 0 -> last_process
	if(result == -1) {
		result = CoSchedulerNextProcessLoop(0, last_process);
	}

	if(result == -1) {
		printf("\n\nNo processes");
		while(1);
	}

	return result;
}

void CoSchedulerSetNumProcesses(uint32_t num)
{
	number_of_processes = num;
}
