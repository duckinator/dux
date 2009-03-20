#include <system.h>
#include <keyboard.h>

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


void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outportb(0x43, 0x36);             /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
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
		if ((c = keyboard_getchar())) {
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

#ifdef DEBUG

	printk("argc %d\n", num_spaces);
	j = 0;
	while (j <= num_spaces) {
		printk("argv[%d] %s\n", j++, *argv++);
	}

#endif

	j = 0;
	num_spaces = 0;
	memset(buf, 0x0, 160);

	run_command(num_spaces, argv);
}

struct mmap_buffer {
	unsigned int size;
	unsigned int base_addr_low;
	unsigned int base_addr_high;
	unsigned int length_low;
	unsigned int length_high;
	unsigned int type;
};

/* Main loop! */
void kmain(unsigned int *mb_info)
{
	struct mmap_buffer *mmap;
	unsigned long long base_addr;
	unsigned long long length;
	monitor_clear();
	timer_phase(100); /* 100Hz timer */
	startitem(timer_install, "timer");
	startitem(isr_install, "ISRs");
	startitem(irq_install, "IRQs");
	startitem(keyboard_install, "keyboard");
	startitem(enable_interrupts, "interrupts");

	if (*mb_info & 0x40) { /* mmem_* fields are valid */
		mmap = (struct mmap_buffer*) mb_info[12];
		while ((unsigned int) mmap < mb_info[12] + mb_info[11]) {
			base_addr = ((unsigned long long) mmap->base_addr_high << 32)
				+ mmap->base_addr_low;
			length = mmap->length_low;
			printk("0x%lx - 0x%lx (%s)\n", base_addr, base_addr+length,
					(mmap->type == 1) ? "available" : "unavailable");
			mmap = (struct mmap_buffer*) ((unsigned int)mmap +
					mmap->size + sizeof(unsigned int));
			length = 0;
			base_addr = 0;
		}
	}

	while (1);

	//detect_floppy_drives(); 
	//putch(floppy_read_data(0x3f0));
	/* This reboots, I think.
	 * outportb(0x60, 0xED);
	 * outportb(0x60, 0x00);*/
}
