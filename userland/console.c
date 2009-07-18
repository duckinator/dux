/* This is the user console.
 * At the moment, it is not truly in userland -- nothing is.
 * This is the console for the user to use (think 'bash'/'sh'),
 * as opposed to the console driver (think 'VT' [virtual terminal] on Linux)
 */

#include <string.h>
#include <dux/mm/memory.h>
#include <dux/drivers/fdd.h>

void user_console()
{
	char c;
	char input[2000];
	int index = 0;
	char tmp[2000];
	int tmp_index = 0;
	
	printk("\nDux OS terminal\n\n");
	console_tab_start(6);
	
	while (1)
	{
		index = 0;
		input[0] = 0;
		screen_setattr(0x0a, 0x0a);
		printk("[");
		screen_setattr(0x09, 0x09);
		printk("Dux");
		screen_setattr(0x0a, 0x0a);
		printk("]# ");
		
		while (1)
		{
			c = console_readb();
			
			if (c == 0)
			{
				// Release?
			}
			else if (c == 8)
			{
				if (index > 0)
					index--;
				
				c = 0;
				input[index] = 0;
				
				printk("\x08\r[");
				screen_setattr(0x09, 0x09);
				printk("Dux");
				screen_setattr(0x0a, 0x0a);
				printk("]# %s", input);
				
			}
			else if (c == '\n')
			{
				printk("\n");
				if (input[0] == 0)
				{}
				else if( strcmp(input, "panic") == 0 )
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
				else if( strcmp(input, "help") == 0 )
					printk("Help:\
\tpanic:\t(or ctrl-p) User initialized kernel panic\n\
\tbeep:\tHalBeep();\n\
\tticks:\tPrint number of ticks since system start\n\
\tclear:\tClear the screen\n\
\tpong:\tA nice, relaxing game of Pong\n\
\tcolors:\tDisplays a color chart (useful for picking colors)\n\
\tfirstframe:\tPrints address of the first free frame\n\
\tallocframe:\tAllocates and prints the address of the first free frame\n\
\tfddtest:\tTest the floppy disk drive driver\n\
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
