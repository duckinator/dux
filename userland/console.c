/* This is the user console.
 * At the moment, it is not truly in userland -- nothing is.
 * This is the console for the user to use (think 'bash'/'sh'),
 * as opposed to the console driver (think 'VT' [virtual terminal] on Linux)
 */

#include <string.h>
#include <dux/mm/memory.h>
#include <dux/drivers/fdd.h>
#include <dux/drivers/core/kb.h>

void print_prompt(input)
{
	printk("\r                                                                                \r[");
	screen_setattr(0x09, 0x09);
	printk("Dux");
	screen_setattr(0x0a, 0x0a);
	printk("]# %s", input);
}

void user_console()
{
#if defined(__FreeBSD__)
	char built_os[8] = "FreeBSD";
#elif defined(__NetBSD__)
	char built_os[7] = "NetBSD";
#elif defined(__OpenBSD__)
	char built_os[8] = "OpenBSD";
#elif defined(BSD)
	char built_os[4] = "BSD";
#elif defined(__MACOSX__)
	char built_os[9] = "Mac OS X";
#elif defined(macintosh)
	char built_os[10] = "Macintosh";
#elif defined(linux) || defined(__linux) || defined(__linux__)
	char built_os[6] = "Linux";
#elif defined(__CYGWIN__ )
	char built_os[7] = "CYGWin";
#elif defined(WIN32) || defined(_WIN32)
	char built_os[15] = "Windows 32-bit";
#elif defined(_WIN64)
	char built_os[15] = "Windows 64-bit";
#elif defined(MSDOS)
	char built_os[6] = "MS-DOS";
#else
	char built_os[8] = "Unknown";
#endif

#if defined(__i386__)
	char built_platform[5] = "i386";
#elif defined(__i486__)
	char built_platform[5] = "i486";
#elif defined(__i586__)
	char built_platform[5] = "i586";
#elif defined(__i686__)
	char built_platform[5] = "i586";
	
#elif defined(__powerpc)
	char built_platform[8] = "PowerPC";
	
#elif defined(__X86__)
	char built_platform[4] = "x86";
#elif defined(__x86_64__)
	char built_platform[7] = "x86 64";
	
#else
	char built_platform[1] = "";
#endif
	
	char c;
	char input[2000];
	int index = 0;
	char history[4000];
	int history_index = 0;
	int history_selected = -1;
	int tmp = 0;
	int scancode;
	
	printk("\nDux OS terminal\nBuilt on %s %s\n\n", built_os, built_platform);
	console_tab_start(6);
	
	while (1)
	{
		index = 0;
		input[0] = 0;
		history_selected = history_index;
		
		screen_setattr(0x0a, 0x0a);
		printk("[");
		screen_setattr(0x09, 0x09);
		printk("Dux");
		screen_setattr(0x0a, 0x0a);
		printk("]# ");
		
		while (1)
		{
			scancode = kb_read();
			c = console_resolve_scancode(scancode);
			
			if (scancode & 0x80)
				continue;
			
			if (scancode == 72 && history_selected > 0)
			{
				if (history_selected >= history_index)
					strcpy(history + history_index, input);
				
				history_selected--;
				for (; history[history_selected - 1] != 0; history_selected--);
				
				strcpy(input, history + history_selected);
				print_prompt(input);
			}
			else if (scancode == 80 && history_selected < history_index )
			{
				history_selected += strlen(history + history_selected) + 1;
				
				strcpy(input, history + history_selected);
				print_prompt(input);
			}
			else if (c == 0)
			{
				// Release/unknown
			}
			else if (c == 8)
			{
				if (index > 0)
					index--;
				
				c = 0;
				input[index] = 0;
				
				print_prompt(input);
			}
			else if (c == '\n')
			{
				printk("\n");
				if (input[0] == 0)
					break;
				
				while (strlen(input) + history_index > 4000)
				{
					history_index -= strlen(history) + 1;
					memcpy(history, history + strlen(history) + 1, history_index + strlen(history) + 1);
				}
				strcpy(history + history_index, input);
				history_index += strlen(input) + 1;
				
				if( strcmp(input, "panic") == 0 )
				{
					stop(0x10, 0x0);
					panic("User initialized");
				}
				else if( strcmp(input, "pong") == 0 )
					pong();
				else if( strcmp(input, "beep") == 0 )
					HalBeep();
				else if( strcmp(input, "ticks") == 0 )
					printk("Ticks: %i\n\n", HalGetTicks());
				else if( strcmp(input, "clear") == 0 )
					console_clear();
				else if( strcmp(input, "colors") == 0 )
					color_chart();
				else if( strcmp(input, "history") == 0 )
				{
					for (tmp = 0; tmp < history_index; tmp += strlen(history + tmp) + 1)
					{
						printk("%i %i: %s\n", tmp, strlen(history + tmp), history + tmp);
					}
				}
				else if (strcmp(input, "firstframe") == 0)
				{
					printk("%i\n", first_frame());
				}
				else if (strcmp(input, "allocframe") == 0)
				{
					printk("Setting frame at %i\n", first_frame());
					set_frame(first_frame());
				}
				else if (strcmp(input, "fddtest") == 0)
				{
					FDD_Reset(FDD_BASE);
					FDD_Detect();
					//printk("%c", FDD_ReadData(FDD_BASE));
					printk("%c", FDD_ReadTrack(FDD_BASE, 1));
				}
				else if (strcmp(input, "keycodes") == 0)
				{
					printk("Press any key to log info about it, and hit Ctrl-C to exit\n\n");
					
					while (1)
					{
						scancode = kb_read();
						c = console_resolve_scancode(scancode);
						
						if (kb_ctrl() && c == 'c')
						{
							printk("Byebye. (caught Ctrl-C)\n");
							break;
						}
						
						if ( !(scancode & 0x80) )
							printk("scancode: %i\tcharactor: %s\tshift: %i\talt: %i\tctrl: %i\n", scancode, c, kb_shift(), kb_alt(), kb_ctrl());
					}
				}
				else if( strcmp(input, "help") == 0 )
					printk("Help:\
\tpanic:\t(or ctrl-p) User initialized kernel panic\n\
\tbeep:\tHalBeep();\n\
\tticks:\tPrint number of ticks since system start\n\
\tclear:\tClear the screen\n\
\tpong:\tA nice, relaxing game of Pong\n\
\tcolors:\tDisplays a color chart (useful for picking colors)\n\
\thistory:\tShows the recent console commands\n\
\tfirstframe:\tPrints address of the first free frame\n\
\tallocframe:\tAllocates and prints the address of the first free frame\n\
\tfddtest:\tTest the floppy disk drive driver\n\
\tkeycodes:\tDisplay keycodes and scancodes for pressed keys\n\
\thelp:\tThis help message\n");
				else
					printk("dux: no such command: %s\n", input);
				c = 0;
				break;
			}
			else
			{
				input[index] = c;
				index++;
				input[index] = 0;
			}
			
			if (kb_ctrl())
			{
				if (c == 'p')
				{
					stop(0x10, 0x0);
					panic("User initialized");
				}
				if (c == 'c')
				{
					screen_setattr(0x0F, 0x0F);
					printk("^C\n");
					break;
				}
			}
				
			if (c != 0)
				console_writeb(c);
		}
	}
}
