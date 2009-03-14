/*Floppy driver for Dux. Copyright 2008 Baddog :P*/

/*A few definitions to start off*/

#include <system.h>

static const int floppy_base = 0x03f0; //Standard base address for floppy

static const int floppy_irq = 6; //Can you guess what this one is? =P

//Main registers. There are more, but they're not as important or exciting
enum floppy_registers
{
	FLOPPY_DOR = 2, 	//Digital output
	FLOPPY_MSR = 4,		//Master status (read-only)
	FLOPPY_FIFO = 5,	//Data FIFO, in DMA operation
	FLOPPY_CCR = 7		//Config control (write-only)
};

//Main commands. Again, there are more, but they're not as useful. The names are fairly self-explanatory here
enum floppy_commands
{
	CMD_SPECIFY = 3,	
	CMD_WRITE_DATA = 5,
	CMD_READ_DATA = 6,
	CMD_RECALIBRATE = 7,
	CMD_SENSE_INTERRUPT = 8,
	CMD_SEEK = 15
};

//Drive types
static const char * drive_types[8] = {
    "none",
    "360kB 5.25\"",
    "1.2MB 5.25\"",
    "720kB 3.5\"",

    "1.44MB 3.5\"",
    "2.88MB 3.5\"",
    "unknown type",
    "unknown type"
};

void detect_floppy_drives()
{
	outportb(0x70, 0x10);
	unsigned drives = inportb(0x71);
	puts( (char *)drive_types[drives >> 4] );
}

//
// The MSR byte: [read-only]
// -------------
//
//  7   6   5    4    3    2    1    0
// MRQ DIO NDMA BUSY ACTD ACTC ACTB ACTA
//
// MRQ is 1 when FIFO is ready (test before read/write)
// DIO tells if controller expects write (1) or read (0)
//
// NDMA tells if controller is in DMA mode (1 = no-DMA, 0 = DMA)
// BUSY tells if controller is executing a command (1=busy)
//
// ACTA, ACTB, ACTC, ACTD tell which drives position/calibrate (1=yes)
//
//

void floppy_write_cmd(int base, char cmd) {
    int i; // do timeout, 60 seconds
    for(i = 0; i < 600; i++) {
        timer_sleep(1); // sleep 10 ms
        if(0x80 & inportb(base+FLOPPY_MSR)) {
            return (void) outportb(base+FLOPPY_FIFO, cmd);
        }
    }
    panic("floppy_write_cmd: timeout");   
}

unsigned char floppy_read_data(int base)
{
	int i; //For timeout
	for (i = 0; i < 600; i++)
	{
		timer_sleep(1);
		if(0x80 & inportb(base+FLOPPY_MSR)) {
			return inportb(base+FLOPPY_FIFO);
		}
	}
	return 0;
}

//
// The DOR byte: [write-only]
// -------------
//
//  7    6    5    4    3   2    1   0
// MOTD MOTC MOTB MOTA DMA NRST DR1 DR0
//
// DR1 and DR0 together select "current drive" = a/00, b/01, c/10, d/11
// MOTA, MOTB, MOTC, MOTD control motors for the four drives (1=on)
//
// DMA line enables (1 = enable) interrupts and DMA
// NRST is "not reset" so controller is enabled when it's 1
//
enum { floppy_motor_off = 0, floppy_motor_on, floppy_motor_wait };
static volatile int floppy_motor_ticks = 0;
static volatile int floppy_motor_state = 0;

void floppy_motor(int base, int onoff) {

    if(onoff) {
        if(!floppy_motor_state) {
            // need to turn on
            outportb(base + FLOPPY_DOR, 0x1c);
            timer_sleep(50); // wait 500 ms = hopefully enough for modern drives
        }
        floppy_motor_state = floppy_motor_on;
    } else {
        if(floppy_motor_state == floppy_motor_wait) {
            puts("floppy_motor: strange, fd motor-state already waiting..\n");
        }
        floppy_motor_ticks = 300; // 3 seconds, see floppy_timer() below
        floppy_motor_state = floppy_motor_wait;
    }
}

void floppy_motor_kill(int base) {
    outportb(base + FLOPPY_DOR, 0x0c);
    floppy_motor_state = floppy_motor_off;
}

//
// THIS SHOULD BE STARTED IN A SEPARATE THREAD.
//
//
void floppy_timer() {
    while(1) {
        // sleep for 500ms at a time, which gives around half
        // a second jitter, but that's hardly relevant here.
        timer_sleep(50);
        if(floppy_motor_state == floppy_motor_wait) {
            floppy_motor_ticks -= 50;
            if(floppy_motor_ticks <= 0) {
                floppy_motor_kill(floppy_base);
            }
        }
    }
}

void floppy_check_interrupt(int base, int *st0, int *cyl)
{
	floppy_write_cmd(base, CMD_SENSE_INTERRUPT);

	*st0 = floppy_read_data(base);
	*cyl = floppy_read_data(base);
}

// Move to cylinder 0, which calibrates the drive..
int floppy_calibrate(int base) {

    int i, st0, cyl = -1; // set to bogus cylinder

    floppy_motor(base, floppy_motor_on);

    for(i = 0; i < 10; i++) {
        // Attempt to positions head to cylinder 0
        floppy_write_cmd(base, CMD_RECALIBRATE);
        floppy_write_cmd(base, 0); // argument is drive, we only support 0

        irq_wait(floppy_irq);
        floppy_check_interrupt(base, &st0, &cyl);
       
        if(st0 & 0xC0) {
            static const char * status[] =
            { 0, "error", "invalid", "drive" };
            continue;
        }

        if(!cyl) { // found cylinder 0 ?
            floppy_motor(base, floppy_motor_off);
            return 0;
        }
    }

    puts("floppy_calibrate: 10 retries exhausted\n");
    floppy_motor(base, floppy_motor_off);
    return -1;
}

int floppy_reset(int base) {

    outportb(base + FLOPPY_DOR, 0x00); // disable controller
    outportb(base + FLOPPY_DOR, 0x0C); // enable controller

    irq_wait(floppy_irq); // sleep until interrupt occurs

    {
        int st0, cyl; // ignore these here..
        floppy_check_interrupt(base, &st0, &cyl);
    }

    // set transfer speed 500kb/s
    outportb(base + FLOPPY_CCR, 0x00);

    //  - 1st byte is: bits[7:4] = steprate, bits[3:0] = head unload time
    //  - 2nd byte is: bits[7:1] = head load time, bit[0] = no-DMA
    //
    //  steprate    = (8.0ms - entry*0.5ms)*(1MB/s / xfer_rate)
    //  head_unload = 8ms * entry * (1MB/s / xfer_rate), where entry 0 -> 16
    //  head_load   = 1ms * entry * (1MB/s / xfer_rate), where entry 0 -> 128
    //
    floppy_write_cmd(base, CMD_SPECIFY);
    floppy_write_cmd(base, 0xdf); /* steprate = 3ms, unload time = 240ms */
    floppy_write_cmd(base, 0x02); /* load time = 16ms, no-DMA = 0 */

    // it could fail...
    if(floppy_calibrate(base)) return -1;
   
}



	
