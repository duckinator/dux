#ifndef FDD_H
#define FDD_H
#include <stdint.h>

// FDD_MOTOR_ON: Spin-up time for floppy drive, in milliseconds (300 recommended)
#define FDD_SPINUP 500
// FDD_MOTOR_OFF: Spin-down time for floppy drive, in milliseconds (2000 recommended [2 seconds])
#define FDD_SPINDOWN 2000

// standard base address of the primary floppy controller
#define FDD_BASE 0x03f0

// standard IRQ number for floppy controllers
static const int floppy_irq = 6;

// Used by floppy_dma_init and FDD_DoTrack to specify direction
typedef enum {
    floppy_dir_read = 1,
    floppy_dir_write = 2
} FloppyDir;

// The registers of interest. There are more, but we only use these here.
enum FloppyRegisters {
   FLOPPY_DOR  = 2,  // digital output register
   FLOPPY_MSR  = 4,  // master status register, read only
   FLOPPY_FIFO = 5,  // data FIFO, in DMA operation for commands
   FLOPPY_CCR  = 7   // configuration control register, write only
};

// The commands of interest. There are more, but we only use these here.
enum FloppyCommands {
   CMD_SPECIFY = 3,            // SPECIFY
   CMD_WRITE_DATA = 5,         // WRITE DATA
   CMD_READ_DATA = 6,          // READ DATA
   CMD_RECALIBRATE = 7,        // RECALIBRATE
   CMD_SENSE_INTERRUPT = 8,    // SENSE INTERRUPT
   CMD_SEEK = 15,              // SEEK
};

void FDD_install();
void FDD_SetWaiting();
void FDD_Waiting();
void FDD_Detect();
void FDD_WriteCommand(int base, char cmd);
uint8_t FDD_ReadData(int base);
void FDD_CheckInterrupt(int base, int *st0, int *cyl);
void FDD_CheckInterrupt(int base, int *st0, int *cyl);
int FDD_Calibrate(int base);
int FDD_Reset(int base);
void FDD_Motor(int base, int onoff);
void FDD_MotorKill(int base);
void FDD_Timer();
static void FDD_DMA_Init(FloppyDir dir);
int FDD_DoTrack(int base, unsigned cyl, FloppyDir dir);
int FDD_ReadTrack(int base, unsigned cyl);
int FDD_WriteTrack(int base, unsigned cyl);
#endif
