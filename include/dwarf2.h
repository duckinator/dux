#ifndef DWARF_H
#define DWARF_H

#include <stdint.h>

typedef struct {
  uint32_t length;
  uint16_t version;
  uint32_t offset;
  uint8_t size;
} __attribute__((packed)) DWARF_Compilation_Unit_H;

#endif
