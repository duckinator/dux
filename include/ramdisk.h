#ifndef __RAMDISK_H  
#define __RAMDISK_H

/* drivers/ramdisk.c */

typedef struct {
  char name[8];
  char data[152];
  /* total size is 160 */
} ramdisk_file;

typedef struct {
  ramdisk_file files[32];
} ramdisk;

ramdisk *new_ramdisk(void);

#endif /* end of include guard: __RAMDISK_H */
