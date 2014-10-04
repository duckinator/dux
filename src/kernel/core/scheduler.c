#include <config.h>
#include <kernel.h>
#include <kernel/core/scheduler.h>

SchedulerProcess *first_process;
SchedulerProcess *last_process;

SchedulerProcess *current_process;
uint8_t scheduler_firstrun = 1;
uint32_t number_of_processes = 0;

void CoSchedulerHandler(void)
{
	if (scheduler_firstrun) {
		first_process = CoSchedulerAllocateProcess();
		first_process->next = first_process;
		first_process->prev = first_process;

		last_process = first_process;
		current_process = first_process;

		CoSchedulerAllocateProcess();

		scheduler_firstrun = 0;
	}

	HalSchedulerRunProcess(current_process);
	current_process = CoSchedulerNextProcess();
}

SchedulerProcess *CoSchedulerCurProcess(void)
{
	return current_process;
}

uint32_t CoSchedulerNumProcesses(void)
{
	return number_of_processes;
}

SchedulerProcess *CoSchedulerPrevProcess(void)
{
	current_process = current_process->prev;
	return current_process;
}

SchedulerProcess *CoSchedulerNextProcess(void)
{
	current_process = current_process->next;
	return current_process;
}

SchedulerProcess *CoSchedulerAllocateProcess()
{
	SchedulerProcess *old_last;
	SchedulerProcess *new = kmalloc(sizeof(SchedulerProcess));
	memset(new, 0, sizeof(SchedulerProcess));

	old_last = last_process;
	last_process = new;
	old_last->next = last_process;
	last_process->prev = old_last;
	last_process->next = first_process;
	new->used = 0;

	number_of_processes++;
	new->id = number_of_processes;
	return new;
}

int CoSchedulerDestroyProcess(SchedulerProcess *proc)
{
	if((proc == first_process) && (proc == last_process)) {
		panic("No processes running.");
	} else if(proc == first_process) {
		first_process = first_process->next;
	} else if(proc == last_process) {
		last_process = last_process->prev;
	}
	proc->next->prev = proc->prev;
	proc->prev->next = proc->next;
	free(proc);

	if(((SchedulerProcess*)proc)->used == 1)
		return -1;
	else
		return 0;
}
