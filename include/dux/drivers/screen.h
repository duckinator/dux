typedef enum {none, block} CursorStyle;

typedef struct {
	unsigned char x;
	unsigned char y;
	unsigned char attr;
	unsigned char cattr;
	CursorStyle type;
} CursorPos;

void screen_writechar(unsigned char x, unsigned char y, unsigned char attr, char c);
void screen_putchar(char c);
void screen_puts(char *s);

void screen_hidecursor();
void screen_showcursor(CursorStyle type);
void screen_drawcursor(unsigned char x, unsigned char y);

void screen_setattr(unsigned char attr, unsigned char cattr);
void screen_clear();
void screen_init();