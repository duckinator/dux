#ifndef INITRD_H
#define INITRD_
#include <stdint.h>
#include <vfs/vfs.h>

typedef struct 
{
	uint32_t filecount; 
} InitRd_Header_t;

typedef struct
{
	uint8_t magic; //Magic number, for error checking
	char name[64];
	uint32_t offset; //Offset from the start of the ramdisk where the file is located
	uint32_t size;
} InitRd_File_Header_t;

fs_node_t *initialise_initrd(uint32_t location);

#endif
