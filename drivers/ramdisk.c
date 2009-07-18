#include <ramdisk.h>
#include <dux/mm/memory.h>

ramdisk *new_ramdisk(void)
{
  ramdisk *rd;
  rd = kmalloc_int(sizeof(ramdisk), 0);
  return rd;
}

