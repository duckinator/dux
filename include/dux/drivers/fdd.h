#ifndef FDD_H
#define FDD_H
extern void detect_floppy_drives();
extern unsigned char floppy_read_cmd();

// FDD_MOTOR_ON: Spin-up time for floppy drive, in milliseconds (300 recommended)
#define FDD_MOTOR_ON 300
// FDD_MOTOR_OFF: Spin-down time for floppy drive, in milliseconds (2000 recommended [2 seconds])
#define FDD_MOTOR_OFF 2000

enum FloppyRegisters {
	STATUS_REGISTER_A		= 0x3F0, // read-only
	STATUS_REGISTER_B		= 0x3F1, // read-only
	DIGITAL_OUTPUT_REGISTER  = 0x3F2,
	TAPE_DRIVE_REGISTER	  = 0x3F3,
	MAIN_STATUS_REGISTER	 = 0x3F4, // read-only
	DATA_RATE_SELECT_REGISTER= 0x3F4, // write-only
	DATA_FIFO				= 0x3F5,
	DIGITAL_INPUT_REGISTER   = 0x3F7, // read-only
	CONFIGURATION_CONTROL_REGISTER = 0x3F7, //write only
};

enum FloppyCommands {
	READ_TRACK = 2,
	SPECIFY = 3,
	SENSE_DRIVE_STATUS = 4,
	WRITE_DATA = 5,
	READ_DATA = 6,
	RECALIBRATE = 7,
	SENSE_INTERRUPT = 8,
	WRITE_DELETED_DATA = 9,
	READ_ID = 10,
	READ_DELETED_DATA = 12,
	FORMAT_TRACK = 13,
	SEEK = 15,
	VERSION = 16,
	SCAN_EQUAL = 17,
	PERPENDICULAR_MODE = 18,
	CONFIGURE = 19,
	VERIFY = 22,
	SCAN_LOW_OR_EQUAL = 25,
	SCAN_HIGH_OR_EQUAL = 29,
};

#endif
