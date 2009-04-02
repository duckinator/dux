#include <system.h>
#include <keyboard.h>
#include <console.h>
#include <serial.h>
#include <tui.h>
#include <detect.h>

extern unsigned int timer_install();
extern unsigned int isr_install();
extern unsigned int irq_install();
extern unsigned int gdt_install();
extern void detect_floppy_drives();
extern unsigned char floppy_read_cmd();

static unsigned int enable_interrupts(void){
	__asm__ __volatile__ ("sti");
	return 0;
}

static void startitem(unsigned int (*func)(void), char *what)
{
	puts("Initializing ");
	puts(what);
	puts("... ");
 
	switch (func()) {
		case 0:
			puts("Done\n");
			return;
		default:
			puts("Failure\n");
			while (1);
	}
}

void run_command(int argc, char *argv[])
{
	unsigned int i;
	char *reboots = "reboot";

	argc=argc;

	for (i = 0; i < (unsigned int)strlen(argv[0]); i++) {
		if (*argv[0]++ == *reboots++) {
			printk("%c", *reboots);
		} else {
			return;
		}
	}

	outportb(0x60, 0xed);
	outportb(0x60, 0x00);
}

void prompt() {
	char buf[160];
	int buf_len;
	char c;
	int i = 0, j = 0, num_spaces = 0;
	char **argv;

	printk(" > ");

	while (1) {
		if ((c = conrecv())) {
			if (c == 0x08) {
				i--;
				buf[i] = 0x0;
			}
			if (c >= ' ')
				buf[i++] = c;
			printk("%c", c);
			if (c == '\n')
				break;
		}
	}

	buf_len = strlen(buf);

	/* count the number of spaces */
	for (i = 0; i < strlen(buf); i++)
		if (buf[i] == ' ') {
			num_spaces++;
			while (buf[i] == ' ')
				i++;
		}

	argv = malloc(sizeof(void*)*(num_spaces+2));

	argv[j++] = buf;
	/* count the number of spaces */
	for (i = 0; i < buf_len; i++)
		if (buf[i] == ' ') {
			buf[i] = 0x0;
			while (buf[i] == ' ') {
				buf[i] = 0x0;
				i++;
			}
			argv[j++] = &buf[i+1];
		}

	argv[j] = NULL;

	printk("argc %d\n", num_spaces);
	j = 0;
	while (j <= num_spaces) {
		printk("argv[%d] %s\n", j++, *argv++);
	}

	j = 0;
	num_spaces = 0;
	memset(buf, 0x0, 160);

	run_command(num_spaces, argv);
}

/* Main loop! */
void kmain(multiboot_info_t *mb_info)
{
	serial_serial();
	tui_init();
	startitem(timer_install, "timer");
	startitem(isr_install, "ISRs");
	startitem(irq_install, "IRQs");
	startitem(keyboard_install, "keyboard");
	startitem(enable_interrupts, "interrupts");

	mm_detect_grub(mb_info);

	while (1) {
		asm volatile ("cli");
		asm volatile ("hlt");
	}

	//detect_floppy_drives(); 
	//putch(floppy_read_data(0x3f0));
	/* This reboots, I think.
	 * outportb(0x60, 0xED);
	 * outportb(0x60, 0x00);*/
}
