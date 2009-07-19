#include <hal.h>
#include <system.h>
#include <buildnum.h>

#include <dux/drivers/core/screen.h>
#include <dux/drivers/core/console.h>

#define INTRO_DELAY 3

void dux_intro()
{
	screen_hidecursor();

	char lines[6][30] = {
		"    ####                    ",
		"    ## ##                   ",
		"    ##  ##                  ",
		"    ##  ##  ##  ##  ## ##   ",
		"    ## ##   ##  ##   ##     ",
		"    ####     ####   ## ##   "
	};
	
	int row, column, i;
	unsigned char attr = screen_getattr().attr;
	char chr;
	
	console_clear();
	for ( row = 5; row >= 0; row-- )
	{
		for ( column = 29; column > 0; column-- )
		{
			
			chr = lines[row][column];
			if (chr == ' ')
				continue;

			screen_writechar(25 + column, 9 + row, attr, chr);
			usleep(INTRO_DELAY);
		}
	}
	
	for ( i = 9; i >= 0; i-- )
	{
		for ( row = 0; row < 6; row++ )
		{
			console_set_cursor(25, i + row);
			printk(lines[row]);
		}
		console_set_cursor(25, i + 6);
		printk("                            ");
		usleep(10);
	}
	
	for ( i = 25; i >= 0; i-- )
	{
		for ( row = 0; row < 6; row++ )
		{
			console_set_cursor(i, row);
			printk(lines[row]);
		}
		usleep(5);
	}

	printk("\n\nDux OS Build %d %d\n", BUILDNUM);
	
	screen_showcursor(block);
}
