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

void start_initializer(const char *name, void (*func)())
{
	start_service("Initializing", name, func);
}

void hal_init(void) {
	HalInitGDT();
	DisplayInit();
	printf(DUX_FULL_NAME "\nCompiled at " __TIME__ " " __DATE__ "\n\n\n");

	start_initializer("IDT", &HalInitIDT);
	start_initializer("ISRs", &HalIsrInstall);
	start_initializer("IRQs", &HalIrqInstall);
	start_initializer("system timer", &HalTimerInit);
	start_initializer("syscalls", &HalInitializeSyscalls);
	start_initializer("memory management", &HalMMInit);
	//start_initializer("keyboard", &HalKeyboardInit);
	//start_initializer("scheduler", &HalSchedulerEnable);

	start_service("Enabling", "interrupts", &HalEnableInterrupts);
}
