#include <metodo/metodo.h>
#include <buildinfo.h>
#include <metodo/core/scheduler.h>
 
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
	
	printf("Metodo " DUX_ARCH " " DUX_BUILDTYPE " build.\nCompiled at " __TIME__ " " __DATE__ "\nRevision " SCM_REV "\n\n");

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
