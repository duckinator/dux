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

ramdisk *RD_new(void);
void RD_write_file(ramdisk *rd, int index, char *name, char *data);
char *RD_read_file(ramdisk *rd, int index);

#endif /* end of include guard: __RAMDISK_H */
