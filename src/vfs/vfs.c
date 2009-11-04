#include <vfs/vfs.h>

fs_node_t *fs_root = 0;

uint32_t read_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
	
	return 0;
}

uint32_t write_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
	
	return 0;
}
void open_fs(fs_node_t *node, uint8_t read, uint8_t write)
{
	
}

void close_fs(fs_node_t *node)
{
	
}

struct dirent *readdir_fs(fs_node_t *node, uint32_t index)
{
	
}

fs_node_t *finddir_fs(fs_node_t *node, char *name)
{
	
}
