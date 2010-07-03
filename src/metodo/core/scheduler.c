#include <metodo/metodo.h>
#include <metodo/scheduler.h>

static SchedulerProcess processes[1024];

static uint32_t current_process = 0;
static uint8_t scheduler_firstrun = 1;
static uint32_t number_of_processes = 0;

void CoSchedulerHandler(void)
{
	printf("CoSchedulerHandler\n");
	if (scheduler_firstrun) {
		CoSchedulerFirstRun();

		processes[0].used = 1;
		processes[100].used = 1;
		number_of_processes = 101;

		scheduler_firstrun = 0;
	}

	HalSchedulerRunProcess(processes[current_process]);

	CoSchedulerNextProcess();
}

uint32_t CoSchedulerCurProcessId(void)
{
	return current_process;
}

SchedulerProcess CoSchedulerCurProcess(void)
{
	return processes[current_process];
}

uint32_t CoSchedulerNumProcesses(void)
{
	return number_of_processes;
}

void CoSchedulerFirstRun(void)
{
	uint32_t i;
	printf("Updating process ids: ");
	for(i = 0; i < sizeof(processes); i++) {
		processes[i].id = i;
	}
}

uint32_t CoSchedulerNextProcessLoop(int begin, int end)
{
	uint32_t i = 0;
	
	if (end == -1) {
		end = sizeof(processes)-1;
	}

	// Try processes with ids from begin to end
	while(!processes[i].used) {
		printf("%d is not runnnig, checking process %d...", i-1, i);
		// Break if we're past the last process
		if(i >= sizeof(end)) {
			return -1; // Return -1 if no process found in the group
		}
		i++;
	}
	return i;
}

uint32_t CoSchedulerNextProcess(void)
{
	uint32_t result;
	uint32_t last_process = current_process;

	// Try processes current_process -> (sizeof(processes)-1)
	result = CoSchedulerNextProcessLoop(current_process, -1);

	// If result == -1, try again from 0 -> last_process
	if(result == -1) {
		result = CoSchedulerNextProcessLoop(0, last_process);
	}

	return result;
}

void CoSchedulerSetNumProcesses(uint32_t num)
{
	number_of_processes = num;
}
