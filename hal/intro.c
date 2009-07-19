#include <hal.h>
#include <system.h>
#include <buildnum.h>

#define INTRO_DELAY 10

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
	
	int i,n,column;
	console_clear();
	for ( i = 5; i >= 0; i-- ){ // Line
		for ( column = 29; column > 0; column-- ) {
			if(strcmp(lines[i][column], " ") == 0) continue;

			console_clear();
			for ( n = 0; n < i; n++ ) printk("\n");

			for ( n = 0; n < column; n++ ) printk(" ");
			for ( n = column; n < 30; n++) printk("%c", lines[i][n]);
			for ( n = (i+1); n <= 6; n++ ) printk("%s", lines[n]);
			usleep(INTRO_DELAY);
		}
	}
	
	sleep(10);

/*
	printk("\
    ####                    \n\
    ## ##                   \n\
    ##  ##                  \n\
    ##  ##  ##  ##  ## ##   \n\
    ## ##   ##  ##   ##	    \n\
    ####     ####   ## ##   \n\
");
*/
	printk("\n\nDux OS Build %d %d\n\n", BUILDNUM);

}
