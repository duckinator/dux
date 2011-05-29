#include <metodo/colpa/debug.h>
#include <string.h>
#include <metodo/core/shutdown.h>
#include <api/cpu.h>

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
	} else if(strcmp(str, "cpu") == 0) {
		// Ow :(
		char  *brand      = CPUBrand(),
		      *shortbrand = CPUShortBrand(),
		      *family     = CPUFamily(),
		      *model      = CPUModel();
		size_t count      = CPUCount(),
		       cachesize  = CPUCacheSize(),
		       serial     = CPUSerial();
		printf("\
Full  Brand: %s\n\
Short Brand: %s\n\
Family:  %s\n\
Model:   %s\n\
CPU  count: %u\n\
Cache size: %u\n\
Serial no.: %u\n",
               brand, shortbrand, family, model, count, cachesize, serial);
		printf("Maximum supported standard level: 0x%x\n", CPUIDMaxStandardLevel());
		free(brand);
		free(shortbrand);
		free(family);
		free(model);
	} else {
		printf("Unknown command: %s\n", str);
	}
	return str;
}

noreturn KernDebug()
{
	// FIXME: Dummy KernDebug()
	//panic("Kernel debugger not implemented.");
	HalKeyInfo *keyinfo;
	str = kmalloc(1000); // 1000-har message

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

	// Empty the buffer
	if(HalKeyboardHasInput())
		HalKeyboardReadLetter();

	ColpaPrompt();
	while(1) {
		keyinfo = HalKeyboardReadLetter();
		if (keyinfo->action == 0) {
			switch ( keyinfo->scancode ) {
			// Enter
			case 0x9c:
				printf("\n");
				if(strlen(str) > 0) {
					ColpaHandleLine();
				}
				ColpaPrompt();
				break;
			// Otherwise
			default:
				if(strlen(str) >= 1000) {
					printf("YOU TYPE TOO MUCH D:\n");
				} else {
					str[i] = keyinfo->key;
					i++;
					printf("%c", keyinfo->key);
				}
				break;
			}
		}
	}
}
