#include <readline.h>
#include <string.h>

#include <dux/mm/memory.h>
#include <dux/drivers/core/kb.h>
#include <dux/drivers/core/console.h>
#include <dux/drivers/core/screen.h>

/*void readline_print(char c, unsigned char *start_x, unsigned char *start_y, int index)
{
	if (c == 0x08) {
		if (cursor_x > 0) {
			cursor_x--;
			screen_writechar(cursor_x, cursor_y, screen_getattr().attr, ' ');
		} else {
			cursor_x = 79;
			cursor_y--;
			screen_writechar(cursor_x, cursor_y, screen_getattr().attr, ' ');
		}
	}
	else if (c == 0x09) {
		cursor_x = ((cursor_x + 8) & ~(8 - 1));
	}
	else if (c == '\r') {
		cursor_x = 0;
	}
	else if (c == '\n') {
		cursor_y++;
		cursor_x = 0;
	}
	else if (c >= 0x20) {
		screen_writechar(cursor_x, cursor_y, screen_getattr().attr, c);
		cursor_x++;
	}

	if (cursor_x > 80) {
		cursor_x = 0;
		cursor_y++;
	}

	screen_scroll(&cursor_x, &cursor_y);
	update_cursor(cursor_y, cursor_x);
}

void console_write(char *buf, unsigned int count)
{
	unsigned int i;
	for (i = 0; i < count; i++)
		console_writeb(buf[i]);
}

char console_readb()
{
	int scancode = kb_read();
	if (!(scancode & 0x80))
	{
		if (kb_ctrl())
		{
			
		}
		
		return console_resolve_scancode(scancode);
	}
	//if (scancode & 0x80)
	return 0;
}

console_resolve_scancode(int scancode)
console_set_cursor(x, y);

void print_prompta(input)
{
	printk("\r                                                                                \r[Dux]# %s", input);
}
*/

char* readline(const char *prompt)
{
	static unsigned char cursor_x, cursor_y;
	static unsigned char start_x, start_y;
	
	printk(prompt);
	start_x = console_get_cursor_x();
	start_y = console_get_cursor_y();
	
	static char input[1000];
	static int index = 0;
	
	static char history[2000];
	static int history_index = 0;
	static int history_selected = 0;
	
	int scancode;
	char chr;
	
	int tmp;
	int i;
	
	index = 0;
	input[0] = 0;
	history_selected = history_index;
	
	while (1)
	{
		scancode = kb_read();
		chr = console_resolve_scancode(scancode);
		
		if (scancode & 0x80)
			continue;
		
		if (scancode == 72 && history_selected > 0)
		{ // Up arrow
			if (history_selected >= history_index)
				strcpy(history + history_index, input);
			
			history_selected--;
			while (history_selected > 0 && history[history_selected - 1] != 0)
				history_selected--;
			
			strcpy(input, history + history_selected);
			index = strlen(input);
		}
		else if (scancode == 80 && history_selected < history_index )
		{ // Down arrow
			history_selected += strlen(history + history_selected) + 1;
			
			strcpy(input, history + history_selected);
			index = strlen(input);
		}
		
		else if (scancode == 75 && index > 0)
		{ // Left arrow
			index--;
		}
		else if (scancode == 77 && index < strlen(input) )
		{ // Right arrow
			index++;
		}
		
		else if (scancode == 71)
		{ // Home
			index = 0;
		}
		else if (scancode == 79 )
		{ // End
			index = strlen(input);
		}
		
		else if (scancode == 83 && index < strlen(input))
		{ // Delete
			for (i = index; i < strlen(input); i++)
				input[i] = input[i + 1];
		}
		
		else if (chr == 0)
		{ // Release/unknown
		}
		
		else if (chr == 8)
		{ // Backspace
			if (index == 0)
			{}
			if (index == strlen(input))
			{
				index--;
				input[index] = 0;
			}
			else
			{
				for (i = index - 1; i < strlen(input); i++)
					input[i] = input[i + 1];
				
				index--;
			}
		}
		
		else if (chr == '\n')
		{ // Enter
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
			
			break;
		}
		
		else
		{ // Char, add to string
			if (kb_ctrl())
			{
				if (chr == 'p')
				{
					stop(0x10, 0x0);
					panic("User initialized");
				}
				
				else if (chr == 'c')
				{
					update_cursor(start_y, start_x);
					printk(input);
					screen_setattr(0x0F, 0x0F);
					printk("^C\n");
					input[0] = 0;
					break;
				}
			}
			
			if (index == strlen(input))
			{
				input[index] = chr;
				index++;
				input[index] = 0;
			}
			else
			{
				for (i = strlen(input); i > index - 1; i--)
					input[i + 1] = input[i];
				
				input[index] = chr;
				index++;
			}
		}
		
		cursor_x = start_x;
		cursor_y = start_y;
		for (i = 0; i < strlen(input); i++)
		{
			chr = input[i];
			
			if (index == i)
				update_cursor(cursor_y, cursor_x);
			
			if (chr == 0x09) {
				tmp = ((cursor_x + 8) & ~(8 - 1));	
				for(; cursor_x < tmp; cursor_x++)
				{
					screen_writechar(cursor_x, cursor_y, screen_getattr().attr, ' ');
				}
			}
			else if (chr == '\r') {
				cursor_x = 0;
			}
			else if (chr == '\n') {
				cursor_y++;
				cursor_x = 0;
			}
			else if (chr >= 0x20) {
				screen_writechar(cursor_x, cursor_y, screen_getattr().attr, chr);
				cursor_x++;
			}

			if (cursor_x > 79) {
				cursor_x = 0;
				cursor_y++;
			}
			
			if (cursor_y > 24)
			{
				start_y -= (cursor_y - 24);
				
				if (index < i)
					update_cursor(console_get_cursor_y() - (cursor_y - 24), console_get_cursor_x());
			}
			screen_scroll(&cursor_x, &cursor_y);
		}
		
		if (index == strlen(input))
			update_cursor(cursor_y, cursor_x);
		
		for (; cursor_x < 80; cursor_x++)
			screen_writechar(cursor_x, cursor_y, screen_getattr().attr, ' ');
	}
	
	return input;
}
