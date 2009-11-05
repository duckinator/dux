#include <initrd/initrd.h>
#include <vfs/vfs.h>
#include <system.h>
#include <string.h>
#include <lib/krnllib.h>

InitRd_Header_t *initrd_header;
InitRd_File_Header_t *file_headers;
fs_node_t *initrd_root;
fs_node_t *initrd_dev;
fs_node_t *root_nodes;
int nroot_nodes;

struct dirent dirent;

uint32_t initrd_read(fs_node_t *node, uint32_t offset, uint32_t size, char *buffer)
{
	InitRd_File_Header_t header = file_headers[node->inode];
	if(offset > header.size) //We have a fail
		return 0;
	if(offset+size > header.size)
		size = header.size-offset;
	memcpy(buffer, (char *) (header.offset+offset), size);
	return size;
}

static struct dirent *initrd_readdir(fs_node_t *node, uint32_t index)
{
	if(node == initrd_root && index == 0)
	{
		//strcpy(dirent.name, "dev");
		dirent.name[3] = 0;
		dirent.ino = 0;
		return &dirent;
	}

	if (index-1 >= nroot_nodes)
		return 0;
	//strcpy(dirent.name, root_nodes[index-1].name);
	dirent.name[strlen(root_nodes[index-1].name)] = 0; //Null terminate.
	dirent.ino = root_nodes[index-1].inode;
	return &dirent;
}

static fs_node_t *initrd_finddir(fs_node_t  *node,  char *name)
{
   if (node == initrd_root &&
       !strcmp(name, "dev") )
       return initrd_dev;

   int i;
   for (i = 0; i < nroot_nodes; i++)
       if (!strcmp(name, root_nodes[i].name))
           return &root_nodes[i];
   return 0;
}

fs_node_t *initialise_initrd(uint32_t location)
{
	initrd_header = (InitRd_Header_t *)location;
	file_headers = (InitRd_File_Header_t *) (location+sizeof(InitRd_File_Header_t));
	initrd_root = (fs_node_t *)malloc(sizeof(fs_node_t));
	//strcpy(initrd_root->name, "INITRD");
	initrd_root->inode = initrd_root->length = 0;
   	initrd_root->flags = FS_DIRECTORY;
   	initrd_root->read = 0;
   	initrd_root->write = 0;
   	initrd_root->open = 0;
   	initrd_root->close = 0;
	initrd_root->readdir = &initrd_readdir;
	initrd_root->finddir = &initrd_finddir;
	initrd_root->ptr = 0;

	initrd_dev = (fs_node_t*)malloc(sizeof(fs_node_t));
   	//strcpy(initrd_dev->name, "dev");
   	initrd_dev->inode = initrd_dev->length = 0;
   	initrd_dev->flags = FS_DIRECTORY;
   	initrd_dev->read = 0;
   	initrd_dev->write = 0;
   	initrd_dev->open = 0;
   	initrd_dev->close = 0;
   	initrd_dev->readdir = &initrd_readdir;
   	initrd_dev->finddir = &initrd_finddir;
   	initrd_dev->ptr = 0;
	root_nodes = (fs_node_t*)malloc(sizeof(fs_node_t) * initrd_header->filecount);
	nroot_nodes = initrd_header->filecount;
	int i;
	for (i = 0; i < initrd_header->filecount; i++)
	{
		file_headers[i].offset += location;
		//strcpy(root_nodes[i].name, file_headers[i].name);
	       	root_nodes[i].length = file_headers[i].size;
	       	root_nodes[i].inode = i;
	       	root_nodes[i].flags = FS_FILE;
	       	root_nodes[i].read = &initrd_read;
	       	root_nodes[i].write = 0;
	       	root_nodes[i].readdir = 0;
	       	root_nodes[i].finddir = 0;
	       	root_nodes[i].open = 0;
	       	root_nodes[i].close = 0;

	}
	return initrd_root;
}
