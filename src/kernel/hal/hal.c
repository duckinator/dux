#include <kernel.h>
#include <kernel/core/scheduler.h>
#include <string.h>

void start_service(const char *msg, const char *name, void (*func)())
{
	size_t i;
	printf("%s %s", msg, name);
	for(i = 0; i < (50 - strlen(msg) - strlen(name)); i++)
		printf(" ");
	printf(" [BUSY]");
	//printf("%s %s\n\b\b\b\b\b\b\b[BUSY]", msg, name);
	func();
	printf("\b\b\b\b\bDONE]\n");
}

void start_initializerr(const char *name, void (*func)())
{
	start_service("Initializing", name, func);
}

void hal_init(void) {
	HalInitGDT();
	DisplayInit();
	printf(DUX_FULLNAME "\nCompiled at " __TIME__ " " __DATE__ "\n\n\n");

	start_initializerr("IDT", &HalInitIDT);
	start_initializerr("ISRs", &HalIsrInstall);
	start_initializerr("IRQs", &HalIrqInstall);
	start_initializerr("system timer", &HalTimerInit);
	start_initializerr("syscalls", &HalInitializeSyscalls);
	start_initializerr("memory management", &HalMMInit);
	//start_initializerr("keyboard", &HalKeyboardInit);
	//start_initializerr("scheduler", &HalSchedulerEnable);

	start_service("Enabling", "interrupts", &HalEnableInterrupts);
}
