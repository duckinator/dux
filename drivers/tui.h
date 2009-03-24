#ifndef TUI_H
#define TUI_H

void tui_init();
void tui_set_attr(unsigned char a);
void tui_write_char(unsigned char c);
void tui_update_hw();

#endif
