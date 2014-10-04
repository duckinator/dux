#include <kernel/colpa/debug.h>
#include <string.h>
#include <kernel/core/shutdown.h>

#include <init/tests.h>
#include <init/memory_map.h>

uint8_t i;
char *str;

void ColpaPrompt()
{
	i = 0;
	str[0] = '\0';
	printf(">> ");
}

char *ColpaHandleLine()
{
	str[i] = '\0';
	if(strcmp(str, "help") == 0) {
		printf("Commands:\n\
  help\n\
  info\n\
  test\n\
  mmap\n\
  panic\n\
  halt\n\
  reboot\n");
	} else if(strcmp(str, "info") == 0) {
		printf(DUX_FULLNAME "\nCompiled at " __TIME__ " " __DATE__ "\n");
	} else if(strcmp(str, "halt") == 0) {
		CoShutdown(SD_OFF);
	} else if(strcmp(str, "reboot") == 0) {
		CoShutdown(SD_REBOOT);
	} else if(strcmp(str, "panic") == 0) {
		stop(STOP_USER_INITIALIZED);
	} else if(strcmp(str, "test") == 0) {
		SystemTests();
	} else if(strcmp(str, "mmap") == 0) {
		MMapPrint();
	} else {
		printf("Unknown command: %s\n", str);
	}
	return str;
}

noreturn KernDebug()
{
	HalKeyboardEvent *event;
	str = kmalloc(1000); // 1000-char message

	printf("Initiating kernel debugger...\n");
	printf("Disabling interrupts...");
	HalDisableInterrupts();
	printf("Done.\n");
	
	printf("Masking all IRQs");

	for(i = 0; i < 32; i++) {
		HalIrqSetMask(i);
		printf(".");
	}
	printf("Done.\n");
	printf("Unmasking keyboard IRQ...");
	HalIrqUnsetMask(1);
	printf("Done.\n");
	
	printf("Re-enabling interrupts...");
	HalEnableInterrupts();
	printf("Done.\n");

	ColpaPrompt();
	while(1) {
		event = HalKeyboardGetEvent(1);
		if (event->type == HalKeyboardEventType_down) {
			switch ( event->code ) {
			// Enter
			case 0x1c:
				printf("\n");
				if(strlen(str) > 0) {
					ColpaHandleLine();
				}
				ColpaPrompt();
				break;
			// Backspace
			case 0xe:
				if(strlen(str) > 0) {
					i--;
					str[i] = '\0';
					printf("%c", event->character);
				}
				break;
			// Otherwise
			default:
				if(strlen(str) >= 1000) {
					printf("\nERROR: Line cannot be longer than 1,000 bytes due to the lack of realloc()\n");
				} else {
					str[i] = event->character;
					i++;
					printf("%c", event->character);
				}
				break;
			}
		}
	}
}
