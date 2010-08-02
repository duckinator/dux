#include <metodo/metodo.h>
#include <buildid.h>
#include <metodo/core/scheduler.h>
#include <metodo/hal/mm/memory.h>
 
void StartInitializer(const char *name, void (*func)())
{
	printf("Initializing %s...", name);
	func();
	printf("Done.\n");
}

void HalInit(void)
{
	HalInitGDT();
	HalInitDisplay();
	
	printf("Metodo " __DATE__ " " __TIME__ " " SCM_REV "\n\n");

	StartInitializer("IDT", &HalInitIDT);
	StartInitializer("ISRs", &HalIsrInstall);
	StartInitializer("IRQs", &HalIrqInstall);
	StartInitializer("system timer", &HalTimerInit);
	StartInitializer("syscalls", &HalInitializeSyscalls);
	StartInitializer("memory management", &init_mm);
	StartInitializer("keyboard", &HalKeyboardInit);
	//StartInitializer("scheduler", &HalSchedulerEnable);

	init_mm();
	
	printf("Enabling interrupts...");
	asm volatile ("sti");
	printf("Done.\n");
}
