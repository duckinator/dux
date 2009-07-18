#include <dux/drivers/fdd.h> 
#include <hal.h>

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

// Obviously you'd have this return the data, start drivers or something.
void floppy_detect_drives() {

   HalOutPort(0x70, 0x10);
   uint8_t drives = HalInPort(0x71);

   printk(" - Floppy drive 0: %s\n", drive_types[drives >> 4]);
   printk(" - Floppy drive 1: %s\n", drive_types[drives & 0xf]);

}
