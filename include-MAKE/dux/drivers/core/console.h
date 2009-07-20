void console_writeb(char c);
void console_write(char *buf, unsigned int count);
char console_readb();

void console_tab_start(char start);

void console_init();
void console_clear();

unsigned int console_get_cursor_x(); 
unsigned int console_get_cursor_y();
void console_set_cursor(unsigned int x, unsigned int y);

char console_resolve_scancode(int scancode);
