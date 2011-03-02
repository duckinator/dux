#include <metodo/metodo.h>
#include <metodo/core/scheduler.h>
 
void StartInitializer(const char *name, void (*func)())
{
	printf("Initializing %s [BUSY]", name);
	func();
	printf("\b\b\b\b\bDONE]\n");
}


void HalInit(void) {
    HalInitGDT();
    DisplayInit();
    printf(DUX_FULLNAME "\nCompiled at " __TIME__ " " __DATE__ "\n\n\n");

	StartInitializer("IDT", &HalInitIDT);
	StartInitializer("ISRs", &HalIsrInstall);
	StartInitializer("IRQs", &HalIrqInstall);
	StartInitializer("system timer", &HalTimerInit);
	StartInitializer("syscalls", &HalInitializeSyscalls);
	StartInitializer("memory management", &init_mm);
	StartInitializer("keyboard", &HalKeyboardInit);
	//StartInitializer("scheduler", &HalSchedulerEnable);
	
	printf("Enabling interrupts...");
	HalEnableInterrupts();
	printf("Done.\n");
}
