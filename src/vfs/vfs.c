#include <vfs/vfs.h>
 
fs_node_t *fs_root = 0;
 
uint32_t read_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
	if(node->read != 0 && node->type != FS_DIRECTORY)
		return node->read(node, offset, size, buffer);
	else	
		return 0;
}
 
uint32_t write_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
	if (node->write != 0 && node-> type != FS_DIRECTORY)
		return node->write(node, offset, size, buffer);
	else
		return 0;
}
void open_fs(fs_node_t *node, uint8_t read, uint8_t write)
{
	if (node->open != 0 && node->type != FS_DIRECTORY)
		node->open(node, read, write);
	else
		return;
}
 
void close_fs(fs_node_t *node)
{
	if(node->close != 0 && node->type != FS_DIRECTORY)
		node->close(node);
	else 
		return;
}
 
struct dirent *readdir_fs(fs_node_t *node, uint32_t index)
{
 
}
 
fs_node_t *finddir_fs(fs_node_t *node, char *name)
{
 
}
