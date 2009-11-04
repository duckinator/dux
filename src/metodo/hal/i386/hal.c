#include <metodo/metodo.h>
#include <buildid.h>
 
void StartInitializer(char *name, void (*func)())
{
	printf("Initializing %s...", name);
	func();
	printf("Done.\n");
}

void HalInit(void)
{
	PIDTG idt;

	HalInitGDT();
	HalInitDisplay();
	
	printf("Metodo " __DATE__ " " __TIME__ " " ARCH " " SCM_REV "\n\n");
	/*HalInitIDT();
	HalIsrInstall();
	HalIrqInstall();
	HalKeyboardInit();
	HalTimerInit();
	init_mm();*/

	StartInitializer("IDT", &HalInitIDT);
	StartInitializer("ISRs", &HalIsrInstall);
	StartInitializer("IRQs", &HalIrqInstall);
	StartInitializer("system timer", &HalTimerInit);
	StartInitializer("syscalls", &HalInitializeSyscalls);
	StartInitializer("memory management", &init_mm);
	StartInitializer("keyboard", &HalKeyboardInit);	
	
	printf("Enabling interrupts...");
	asm volatile ("sti");
	printf("Done.\n");
}
