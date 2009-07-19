#include <dux/drivers/ramdisk.h>
#include <dux/mm/memory.h>

ramdisk *RD_new(void)
{
  ramdisk *rd;
  rd = kmalloc(sizeof(ramdisk));
  return rd;
}

void RD_write_file(ramdisk *rd, int index, char *name, char *data)
{

  strncpy(rd->files[index].name, name, 8);
  strncpy(rd->files[index].data, data, 152);
}

char *RD_read_file(ramdisk *rd, int index)
{
  char *data;
  strncpy(data, rd->files[index].data, 152);
}
