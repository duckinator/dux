#include <hal.h>
#include <system.h>
#include <buildnum.h>

#include <dux/drivers/core/screen.h>
#include <dux/drivers/core/console.h>

#include <build_info.h>

void dux_intro()
{
	screen_hidecursor();

	char lines[6][30] = {
		"   ####                     ",
		"   ## ##                    ",
		"   ##  ##                   ",
		"   ##  ##  ##  ##  ##  ##   ",
		"   ## ##   ##  ##    ##     ",
		"   ####     ####   ##  ##   "
	};
	
	int row, column, i;
	unsigned char attr = screen_getattr().attr;
	char chr;
	
	screen_setattr(0x0b, 0x0b);
	console_clear();
	screen_setattr(0x0f, 0x0f);
	
	console_set_cursor(0, 22);
	printk("built %s using gcc %s", __DUX_BUILT_DATE__, __VERSION__);
	console_set_cursor(0, 23);
	printk("by %s running %s %s on %s", __DUX_BUILT_NAME__, __DUX_BUILT_OS__, __DUX_BUILT_VERSION__, __DUX_BUILT_ARCH__);
	
	screen_setattr(0x0b, 0x0b);
	
	for ( row = 5; row >= 0; row-- )
	{
		for ( column = 29; column > 0; column-- )
		{
			chr = lines[row][column];
			if (chr == ' ')
				continue;

			screen_writechar(25 + column, 9 + row, attr, chr);
			usleep(5);
		}
	}
	
	for ( row = 0; row < 6; row++ )
	{
		console_set_cursor(25, 9 + row);
		printk(lines[row]);
	}
	usleep(150);
	
	for ( i = 9; i >= 0; i-- )
	{
		for ( row = 0; row < 6; row++ )
		{
			console_set_cursor(25, i + row);
			printk(lines[row]);
		}
		console_set_cursor(25, i + 6);
		printk("                            ");
		console_set_cursor(0, 0);
		usleep(10);
	}
	
	for ( i = 25; i >= 0; i-- )
	{
		for ( row = 0; row < 6; row++ )
		{
			console_set_cursor(i, row);
			printk(lines[row]);
		}
		console_set_cursor(0, 0);
		usleep(5);
	}
	
	usleep(50);
	
	screen_setattr(0x0a, 0x0a);
	console_clear(); // remove the infoz
	screen_setattr(0x0b, 0x0b);
	
	for ( row = 0; row < 6; row++ )
	{
		console_set_cursor(0, row);
		printk(lines[row]);
	}
	console_set_cursor(0, 0);

	screen_setattr(0x0a, 0x0a);
	printk("\n\n\n\n\n\n\n\nDux OS Build %d\nbuilt %s on %s (%s)\n", BUILDNUM, __DUX_BUILT_DATE__, __DUX_BUILT_NAME__, __DUX_BUILT_OS__);
	
	screen_showcursor(block);
}
