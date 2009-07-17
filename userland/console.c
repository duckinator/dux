/* This is the user console.
 * At the moment, it is not truly in userland -- nothing is.
 * This is the console for the user to use (think 'bash'/'sh'),
 * as opposed to the console driver (think 'VT' [virtual terminal] on Linux)
 */

void user_console()
{
	char c;
	char input[2000];
	int index = 0;
	char tmp[2000];
	int tmp_index = 0;
	
	console_init();
	screen_setattr(0x0a, 0x0a);
	screen_clear();
	printk("Dux OS terminal\n\n");
	
	while (1)
	{
		index = 0;
		input[0] = 0;
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
				input[index] = 0;
				if (index > 0)
					index--;
				else
					c = 0;
				
			}
			else if (c == '\n')
			{
				printk("\n");
				if (input[0] == 0)
				{}
				else if (input[0] == 'p' && input[1] == 'a' && input[2] == 'n' && input[3] == 'i' && input[4] == 'c' && input[5] == 0)
				//else if( strcmp(input, "panic") )
				{
					stop(0x10, 0x0);
					panic("User initialized");
				}
				else if (input[0] == 'b' && input[1] == 'e' && input[2] == 'e' && input[3] == 'p' && input[4] == 0)
					HalBeep();
				else if (input[0] == 't' && input[1] == 'i' && input[2] == 'c' && input[3] == 'k' && input[4] == 's' && input[5] == 0)
					printk("Ticks: %i\n\n", HalGetTicks());
				else if (input[0] == 'c' && input[1] == 'l' && input[2] == 'e' && input[3] == 'a' && input[4] == 'r' && input[5] == 0)
					console_clear();
				else if (input[0] == 'h' && input[1] == 'e' && input[2] == 'l' && input[3] == 'p' && input[4] == 0)
									printk("Help:\
	panic: User initialized kernel panic\n\
	beep: HalBeep();\n\
	ticks: Echo number of ticks since system start\n\
	clear: Clear the screen\n\
	help: This help message\n\n");
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
						
			if (c != 0)
				console_writeb(c);
		}
	}
}
