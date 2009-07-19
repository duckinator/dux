#include <dux/drivers/fdd.h>
#include <hal.h>

/*
 * Big thanks to http://forum.osdev.org/viewtopic.php?t=13538
 */

enum { floppy_motor_off = 0, floppy_motor_on, floppy_motor_wait };
static volatile int floppy_motor_ticks = 0;
static volatile int floppy_motor_state = 0;
int fdd_waiting = 0;

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


void FDD_install()
{
	HalIrqHandler_Install(6, FDD_SetWaiting);
}

void FDD_SetWaiting()
{
	fdd_waiting = 1;
}

void FDD_Waiting()
{
	while(!fdd_waiting);
	fdd_waiting = 0;
}

// Obviously you'd have this return the data, start drivers or something.
void FDD_Detect()
{

   HalOutPort(0x70, 0x10);
   uint8_t drives = HalInPort(0x71);

   printk(" - Floppy drive 0: %s\n", drive_types[drives >> 4]);
   printk(" - Floppy drive 1: %s\n", drive_types[drives & 0xf]);

}

//
// The MSR byte: [read-only]
// -------------
//
//  7   6   5	4	3	2	1	0
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
void FDD_WriteCommand(int base, char cmd)
{
	int i; // do timeout, 60 seconds
	for(i = 0; i < 600; i++) {
		usleep(10); // sleep 10 ms
		if(0x80 & HalInPort(base+FLOPPY_MSR)) {
			HalOutPort(base+FLOPPY_FIFO, cmd);
			return;
		}
	}
	panic("FDD_WriteCommand: timeout");
}

uint8_t FDD_ReadData(int base)
{

	int i; // do timeout, 60 seconds
	for(i = 0; i < 600; i++) {
		usleep(10); // sleep 10 ms
		if(0x80 & HalInPort(base+FLOPPY_MSR)) {
			return HalInPort(base+FLOPPY_FIFO);
		}
	}
	panic("FDD_ReadData: timeout");
	return 0; // not reached
}

void FDD_CheckInterrupt(int base, int *st0, int *cyl)
{
	FDD_WriteCommand(base, CMD_SENSE_INTERRUPT);
	*st0 = FDD_ReadData(base);
	*cyl = FDD_ReadData(base);
}

// Move to cylinder 0, which calibrates the drive..
int FDD_Calibrate(int base)
{

	int i, st0, cyl = -1; // set to bogus cylinder

	FDD_Motor(base, floppy_motor_on);

	for(i = 0; i < 10; i++) {
		// Attempt to positions head to cylinder 0
		FDD_WriteCommand(base, CMD_RECALIBRATE);
		FDD_WriteCommand(base, 0); // argument is drive, we only support 0

		FDD_Waiting();
		FDD_CheckInterrupt(base, &st0, &cyl);
	   
		if(st0 & 0xC0) {
			static const char * status[] =
			{ 0, "error", "invalid", "drive" };
			printk("floppy_calibrate: status = %s\n", status[st0 >> 6]);
			continue;
		}

		if(!cyl) { // found cylinder 0 ?
			FDD_Motor(base, floppy_motor_off);
			return 0;
		}
	}

	printk("floppy_calibrate: 10 retries exhausted\n");
	FDD_Motor(base, floppy_motor_off);
	return -1;
}


int FDD_Reset(int base)
{

	HalOutPort(base + FLOPPY_DOR, 0x00); // disable controller
	HalOutPort(base + FLOPPY_DOR, 0x0C); // enable controller

	FDD_Waiting();

	{
		int st0, cyl; // ignore these here..
		FDD_CheckInterrupt(base, &st0, &cyl);
	}
	
	// set transfer speed 500kb/s
	HalOutPort(base + FLOPPY_CCR, 0x00);

	//  - 1st byte is: bits[7:4] = steprate, bits[3:0] = head unload time
	//  - 2nd byte is: bits[7:1] = head load time, bit[0] = no-DMA
	//
	//  steprate	= (8.0ms - entry*0.5ms)*(1MB/s / xfer_rate)
	//  head_unload = 8ms * entry * (1MB/s / xfer_rate), where entry 0 -> 16
	//  head_load   = 1ms * entry * (1MB/s / xfer_rate), where entry 0 -> 128
	//
	FDD_WriteCommand(base, CMD_SPECIFY);
	FDD_WriteCommand(base, 0xdf); /* steprate = 3ms, unload time = 240ms */
	FDD_WriteCommand(base, 0x02); /* load time = 16ms, no-DMA = 0 */

	// it could fail...
	if(FDD_Calibrate(base)) return -1;
   
}

//
// The DOR byte: [write-only]
// -------------
//
//  7	6	5	4	3   2	1   0
// MOTD MOTC MOTB MOTA DMA NRST DR1 DR0
//
// DR1 and DR0 together select "current drive" = a/00, b/01, c/10, d/11
// MOTA, MOTB, MOTC, MOTD control motors for the four drives (1=on)
//
// DMA line enables (1 = enable) interrupts and DMA
// NRST is "not reset" so controller is enabled when it's 1
//

void FDD_Motor(int base, int onoff)
{

	if(onoff) {
		if(!floppy_motor_state) {
			// need to turn on
			HalOutPort(base + FLOPPY_DOR, 0x1c);
			usleep(FDD_SPINUP); // wait FDD_SPINUP ms = hopefully enough for modern drives
		}
		floppy_motor_state = floppy_motor_off;
	} else {
		if(floppy_motor_state == floppy_motor_wait) {
			printk("floppy_motor: strange, fd motor-state already waiting..\n");
		}
		floppy_motor_ticks = 300; // 3 seconds, see floppy_timer() below
		floppy_motor_state = floppy_motor_wait;
	}
}

void FDD_MotorKill(int base)
{
	HalOutPort(base + FLOPPY_DOR, 0x0c);
	floppy_motor_state = floppy_motor_off;
	FDD_Timer();
}

void FDD_Timer()
{
	while(1) {
		// sleep for 500ms at a time, which gives around half
		// a second jitter, but that's hardly relevant here.
		usleep(500);
		if(floppy_motor_state == floppy_motor_wait) {
			floppy_motor_ticks -= 50;
			if(floppy_motor_ticks <= 0) {
				FDD_MotorKill(FDD_BASE);
				return;
			}
		}
	}
}

// Seek for a given cylinder, with a given head
int FDD_Seek(int base, unsigned cyli, int head) {

	unsigned i, st0, cyl = -1; // set to bogus cylinder

	FDD_Motor(base, floppy_motor_on);

	for(i = 0; i < 10; i++) {
		// Attempt to position to given cylinder
		// 1st byte bit[1:0] = drive, bit[2] = head
		// 2nd byte is cylinder number
		FDD_WriteCommand(base, CMD_SEEK);
		FDD_WriteCommand(base, head<<2);
		FDD_WriteCommand(base, cyli);

		FDD_Waiting();
		FDD_CheckInterrupt(base, &st0, &cyl);

		if(st0 & 0xC0) {
			static const char * status[] =
			{ "normal", "error", "invalid", "drive" };
			printk("FDD_Seek: status = %s\n", status[st0 >> 6]);
			continue;
		}

		if(cyl == cyli) {
			FDD_Motor(base, floppy_motor_off);
			return 0;
		}

	}

	printk("FDD_Seek: 10 retries exhausted\n");
	FDD_Motor(base, floppy_motor_off);
	return -1;
}

// we statically reserve a totally uncomprehensive amount of memory
// must be large enough for whatever DMA transfer we might desire
// and must not cross 64k borders so easiest thing is to align it
// to 2^N boundary at least as big as the block
#define floppy_dmalen 0x4800
static const char floppy_dmabuf[floppy_dmalen]
				  __attribute__((aligned(0x8000)));

static void FDD_DMA_Init(FloppyDir dir)
{

	union {
		unsigned char b[4]; // 4 bytes
		unsigned long l;	// 1 long = 32-bit
	} a, c; // address and count

	a.l = (unsigned) &floppy_dmabuf;
	c.l = (unsigned) floppy_dmalen - 1; // -1 because of DMA counting

	// check that address is at most 24-bits (under 16MB)
	// check that count is at most 16-bits (DMA limit)
	// check that if we add count and address we don't get a carry
	// (DMA can't deal with such a carry, this is the 64k boundary limit)
	if((a.l >> 24) || (c.l >> 16) || (((a.l&0xffff)+c.l)>>16)) {
		panic("floppy_dma_init: static buffer problem\n");
	}

	unsigned char mode;
	switch(dir) {
		// 01:0:0:01:10 = single/inc/no-auto/to-mem/chan2
		case floppy_dir_read:  mode = 0x46; break;
		// 01:0:0:10:10 = single/inc/no-auto/from-mem/chan2
		case floppy_dir_write: mode = 0x4a; break;
		default: panic("floppy_dma_init: invalid direction");
			return; // not reached, please "mode user uninitialized"
	}

	HalOutPort(0x0a, 0x06);   // mask chan 2

	HalOutPort(0x0c, 0xff);   // reset flip-flop
	HalOutPort(0x04, a.b[0]); //  - address low byte
	HalOutPort(0x04, a.b[1]); //  - address high byte

	HalOutPort(0x81, a.b[2]); // external page register

	HalOutPort(0x0c, 0xff);   // reset flip-flop
	HalOutPort(0x05, c.b[0]); //  - count low byte
	HalOutPort(0x05, c.b[1]); //  - count high byte

	HalOutPort(0x0b, mode);   // set mode (see above)

	HalOutPort(0x0a, 0x02);   // unmask chan 2
}

// This monster does full cylinder (both tracks) transfer to
// the specified direction (since the difference is small).
//
// It retries (a lot of times) on all errors except write-protection
// which is normally caused by mechanical switch on the disk.
//
int FDD_DoTrack(int base, unsigned cyl, FloppyDir dir)
{
   
	// transfer command, set below
	unsigned char cmd;

	// Read is MT:MF:SK:0:0:1:1:0, write MT:MF:0:0:1:0:1
	// where MT = multitrack, MF = MFM mode, SK = skip deleted
	//
	// Specify multitrack and MFM mode
	static const int flags = 0xC0;
	switch(dir) {
		case floppy_dir_read:
			cmd = CMD_READ_DATA | flags;
			break;
		case floppy_dir_write:
			cmd = CMD_WRITE_DATA | flags;
			break;
		default:

			panic("FDD_DoTrack: invalid direction");
			return 0; // not reached, but pleases "cmd used uninitialized"
	}

	// seek both heads
	if(FDD_Seek(base, cyl, 0)) return -1;
	if(FDD_Seek(base, cyl, 1)) return -1;

	int i;
	for(i = 0; i < 20; i++) {
		FDD_Motor(base, floppy_motor_on);

		// init dma..
		FDD_DMA_Init(dir);

		usleep(100); // give some time (100ms) to settle after the seeks

		FDD_WriteCommand(base, cmd);  // set above for current direction
		FDD_WriteCommand(base, 0);	// 0:0:0:0:0:HD:US1:US0 = head and drive
		FDD_WriteCommand(base, cyl);  // cylinder
		FDD_WriteCommand(base, 0);	// first head (should match with above)
		FDD_WriteCommand(base, 1);	// first sector, strangely counts from 1
		FDD_WriteCommand(base, 2);	// bytes/sector, 128*2^x (x=2 -> 512)
		FDD_WriteCommand(base, 18);   // number of tracks to operate on
		FDD_WriteCommand(base, 0x1b); // GAP3 length, 27 is default for 3.5"
		FDD_WriteCommand(base, 0xff); // data length (0xff if B/S != 0)
	   
		FDD_Waiting(); // don't SENSE_INTERRUPT here!

		// first read status information
		unsigned char st0, st1, st2, rcy, rhe, rse, bps;
		st0 = FDD_ReadData(base);
		st1 = FDD_ReadData(base);
		st2 = FDD_ReadData(base);
		/*
		 * These are cylinder/head/sector values, updated with some
		 * rather bizarre logic, that I would like to understand.
		 *
		 */
		rcy = FDD_ReadData(base);
		rhe = FDD_ReadData(base);
		rse = FDD_ReadData(base);
		// bytes per sector, should be what we programmed in
		bps = FDD_ReadData(base);

		int error = 0;

		if(st0 & 0xC0) {
			static const char * status[] =
			{ 0, "error", "invalid command", "drive not ready" };
			printk("FDD_DoTrack: status = %s\n", status[st0 >> 6]);
			error = 1;
		}
		if(st1 & 0x80) {
			printk("FDD_DoTrack: end of cylinder\n");
			error = 1;
		}
		if(st0 & 0x08) {
			printk("FDD_DoTrack: drive not ready\n");
			error = 1;
		}
		if(st1 & 0x20) {
			printk("FDD_DoTrack: CRC error\n");
			error = 1;
		}
		if(st1 & 0x10) {
			printk("FDD_DoTrack: controller timeout\n");
			error = 1;
		}
		if(st1 & 0x04) {
			printk("FDD_DoTrack: no data found\n");
			error = 1;
		}
		if((st1|st2) & 0x01) {
			printk("FDD_DoTrack: no address mark found\n");
			error = 1;
		}
		if(st2 & 0x40) {
			printk("FDD_DoTrack: deleted address mark\n");
			error = 1;
		}
		if(st2 & 0x20) {
			printk("FDD_DoTrack: CRC error in data\n");
			error = 1;
		}
		if(st2 & 0x10) {
			printk("FDD_DoTrack: wrong cylinder\n");
			error = 1;
		}
		if(st2 & 0x04) {
			printk("FDD_DoTrack: uPD765 sector not found\n");
			error = 1;
		}
		if(st2 & 0x02) {
			printk("FDD_DoTrack: bad cylinder\n");
			error = 1;
		}
		if(bps != 0x2) {
			printk("FDD_DoTrack: wanted 512B/sector, got %d", (1<<(bps+7)));
			error = 1;
		}
		if(st1 & 0x02) {
			printk("FDD_DoTrack: not writable\n");
			error = 2;
		}

		if(!error) {
			FDD_Motor(base, floppy_motor_off);
			return 0;
		}
		if(error > 1) {
			printk("FDD_DoTrack: not retrying..\n");
			FDD_Motor(base, floppy_motor_off);
			return -2;
		}
	}

	printk("FDD_DoTrack: 20 retries exhausted\n");
	FDD_Motor(base, floppy_motor_off);
	return -1;

}

int FDD_ReadTrack(int base, unsigned cyl)
{
	return FDD_DoTrack(base, cyl, floppy_dir_read);
}

int FDD_WriteTrack(int base, unsigned cyl)
{
	return FDD_DoTrack(base, cyl, floppy_dir_write);
}
