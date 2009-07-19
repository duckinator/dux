#include <hal.h>
#include <system.h>
#include <buildnum.h>

#include <dux/drivers/core/screen.h>
#include <dux/drivers/core/console.h>

#define INTRO_DELAY 3

void dux_intro()
{
	char lines[6][30] = {
		"    ####                    \n",
		"    ## ##                   \n",
		"    ##  ##                  \n",
		"    ##  ##  ##  ##  ## ##   \n",
		"    ## ##   ##  ##   ##     \n",
		"    ####     ####   ## ##   \n"
	};
	
	int row, column;
	unsigned char attr = screen_getattr().attr;
	char chr;
	
	console_clear();
	for ( row = 5; row >= 0; row-- )
	{
		for ( column = 29; column > 0; column-- )
		{
			
			chr = lines[row][column];
			if (chr == ' ' || chr == '\n')
				continue;

			screen_writechar(column, row, attr, chr);
			usleep(INTRO_DELAY);
			
		}
	}

	printk("\n\n\n\n\n\n\nDux OS Build %d %d\n", BUILDNUM);

}
