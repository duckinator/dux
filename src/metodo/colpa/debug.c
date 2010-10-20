#include <metodo/colpa/debug.h>

noreturn KernDebug()
{
	HalKeyInfo *keyinfo;
	panic("Kernel debugger not implemented.");
	/*printf("Initiating kernel debugger...\n>> ");
	while(1) {
		if ( HalKeyboardHasInput() ) {
			keyinfo = HalKeyboardReadLetter();
			if ( keyinfo->action == 0 ) {
				switch ( keyinfo->scancode ) {
				// Enter
				case 0x9c:
					printf("\n>> ");
					break;
				// Otherwise
				default:
					printf("%c", keyinfo->key);
					break;
				}
			}
		}
	}*/
}
