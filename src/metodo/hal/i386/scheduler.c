#include <metodo/metodo.h>
#include <metodo/scheduler.h>

void HalSchedulerRunProcess(SchedulerProcess proc)
{
	printf("Switch process %i\n", CoSchedulerCurProcess());
}
