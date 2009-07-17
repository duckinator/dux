/*
void print_number_width(int n, char width)
{
	static char* spaces = "        "; // 8
	if (n >= 10)       { width--; }
	if (n >= 100)      { width--; }
	if (n >= 1000)     { width--; }
	if (n >= 10000)    { width--; }
	if (n >= 100000)   { width--; }
	if (n >= 1000000)  { width--; }
	if (n >= 10000000) { width--; }
	printk("%i%s", n, spaces + (9 - width));
}
*/

void color_chart()
{
	char bgcolor, fgcolor;
	
	for (fgcolor = 0; fgcolor < 16; fgcolor++)
	{
		if (fgcolor < 2)
		{
			screen_setattr(0x70 + fgcolor, 0x70 + fgcolor);
			printk(" %i   ", fgcolor);
		}
		else if (fgcolor < 10)
		{
			screen_setattr(fgcolor, fgcolor);
			printk(" %i   ", fgcolor);
		}
		else
		{
			screen_setattr(fgcolor, fgcolor);
			printk("%i/%x ", fgcolor, fgcolor);
		}
	}
	
	for (bgcolor = 0; bgcolor < 16; bgcolor++)
	{
		printk("\n");
		
		for (fgcolor = 0; fgcolor < 16; fgcolor++)
		{
			screen_setattr(bgcolor * 16 + fgcolor, bgcolor * 16 + fgcolor);
			printk("0x%x%x ", bgcolor, fgcolor);
		}
	}
	
	screen_setattr(0x0f, 0x0f);
	printk("\n\n");
}
