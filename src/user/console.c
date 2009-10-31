/* This is the user console.
 * At the moment, it is not truly in userland -- nothing is.
 * This is the console for the user to use (think 'bash'/'sh'),
 * as opposed to the console driver (think 'VT' [virtual terminal] on Linux)
 */

#include <string.h>
#include <readline.h>

#include <krnl/stop.h>

#include <dux/mm/memory.h>
#include <dux/shutdown.h>
#include <dux/drivers/fdd.h>
#include <dux/drivers/ramdisk.h>
#include <dux/drivers/core/kb.h>

void user_console()
{
	char* input;
	
	printf("\nDux OS terminal\n\n");
	//console_tab_start(6);
	
	while (1)
	{
		screen_setattr(0x0a, 0x0a);
		printf("[");
		screen_setattr(0x09, 0x09);
		printf("Dux");
		screen_setattr(0x0a, 0x0a);
		printf("]# ");
		
		input = readline("");

		if( input[0] == 0 )
		{} // Empty
		else if( strcmp(input, "panic") == 0 )
		{
			KrnlEasyStop(STOP_UNKNOWN);
		}
		else if( strcmp(input, "pong") == 0 )
			pong();
		else if( strcmp(input, "beep") == 0 )
			HalBeep();
		else if( strcmp(input, "ticks") == 0 )
			printf("Ticks: %i\n\n", HalGetTicks());
		else if( strcmp(input, "clear") == 0 )
			console_clear();
		else if( strcmp(input, "colors") == 0 )
			color_chart();
		/*else if( strcmp(input, "history") == 0 )
		{
			for (tmp = 0; tmp < history_index; tmp += strlen(history + tmp) + 1)
			{
				printf("%i %i: %s\n", tmp, strlen(history + tmp), history + tmp);
			}
		}*/
		else if (strcmp(input, "firstframe") == 0)
		{
			printf("%i\n", first_frame());
		}
		else if (strcmp(input, "allocframe") == 0)
		{
			printf("Setting frame at %i\n", first_frame());
			set_frame(first_frame());
		}
		else if (strcmp(input, "fddtest") == 0)
		{
			FDD_Reset(FDD_BASE);
			FDD_Detect();
			//printf("%c", FDD_ReadData(FDD_BASE));
			printf("%c", FDD_ReadTrack(FDD_BASE, 1));
		}
		else if (strcmp(input, "ramdisktest") == 0)
		{
			char *test_data = "this is a test data!";

			ramdisk *rd = RD_new();
			RD_write_file(rd, 0, "test", "this is a test data!");

			char *data = RD_read_file(rd, 0);

			printf("Content of file: ");
			printf(data);
			printf("\nYou should have seen: ");
			printf(test_data);
			printf("\n");
		}
		else if (strcmp(input, "keycodes") == 0)
		{
			printf("Press any key to log info about it, and hit Ctrl-C to exit\n\n");
			
			int scancode;
			char c;
			
			while (1)
			{
				scancode = kb_read();
				c = console_resolve_scancode(scancode);
				
				if (kb_ctrl() && c == 'c')
				{
					printf("Byebye. (caught Ctrl-C)\n");
					break;
				}
				
				if ( !(scancode & 0x80) )
					printf("scancode: %i\tcharactor: %s\tshift: %i\talt: %i\tctrl: %i\n", scancode, c, kb_shift(), kb_alt(), kb_ctrl());
			}
		}
		else if( strcmp(input, "help") == 0 )
			printf("Help:\
\tpanic:\t(or ctrl-p) User initialized kernel panic\n\
\tshutdown:\t Shutdown the system\n\
\tbeep:\tHalBeep();\n\
\tticks:\tPrint number of ticks since system start\n\
\tclear:\tClear the screen\n\
\tcolors:\tDisplays a color chart (useful for picking colors)\n\
\thistory:\tShows the recent console commands\n\
\tfirstframe:\tPrints address of the first free frame\n\
\tallocframe:\tAllocates and prints the address of the first free frame\n\
\tfddtest:\tTest the floppy disk drive driver\n\
\tramdisktest:\tTest the ram disk driver\n\
\tkeycodes:\tDisplay keycodes and scancodes for pressed keys\n\
\thelp:\tThis help message\n");
		else if (strcmp(input, "shutdown") == 0) {
			DuxShutdown();
		} else
			printf("dux: no such command: %s\n", input);

	}
}
