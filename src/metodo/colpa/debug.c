#include <metodo/colpa/debug.h>

void dprint(const char *msg, debug_type type)
{
	if (DEBUG_MODE == NONE)
		return;

	if (DEBUG_MODE == ALL || type == DEBUG_MODE)
		printf(msg);
}

void set_debug_mode(debug_type type)
{
	DEBUG_MODE = type;
}

debug_type get_debug_mode(void)
{
	return DEBUG_MODE;
}


void KernDebug()
{
	HalKeyInfo keyinfo;
	printf("Initiating kernel debugger...\n>> ");
	while(1)
	{
		if ( HalKeyboardHasInput() ) {
			keyinfo = HalKeyboardReadLetter();
			if ( keyinfo.action == 0 ) {
				/*
				 * TODO: Figure out what make/break code to use for pause/break
				 * So, pause/break outputs 4 keycodes - no clue which is which.
				 * 0xe1 (make)
				 * 0xe1 (make)
				 * 0xc5 (make)
				 * 0x9d (make)
				 * 0x45 (break)
				 * 0x1d (break)
				 * In no apparent order
				 * 
				 */
        switch ( keyinfo.scancode ) {
          // Enter
          case 0x9c:
            printf("\n>> ");
            break;
          // Pause/break
          case 0xc5:
            HalBreak();
            break;
          // Otherwise
          default:
            printf("%c", keyinfo.key);
            break;
        }
				/*if ( keyinfo.scancode == 0xc5 ) {
					HalBreak();
				} else {
					printf("%c", keyinfo.key);
				}*/
			}
		}
	}
}
