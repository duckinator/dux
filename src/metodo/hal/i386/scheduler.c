#include <metodo/metodo.h>
#include <metodo/scheduler.h>

void HalSchedulerRunProcess(SchedulerProcess proc)
{
	printf("Switch process %i\n", CoSchedulerCurProcess());
}

void HalSchedulerEnable()
{
	scheduler_enabled = 1;
}

void HalSchedulerDisable()
{
	scheduler_enabled = 0;
}
