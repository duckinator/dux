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
  while(1) {
    if ( HalKeyboardHasInput() ) {
      keyinfo = HalKeyboardReadLetter();
      if ( keyinfo.action == 0 ) {
	switch ( keyinfo.scancode ) {
	  // Enter
	  case 0x9c:
	    printf("\n>> ");
	    break;
	  // Otherwise
	  default:
	    printf("%c", keyinfo.key);
            break;
	}
      }
    }
  }
}
