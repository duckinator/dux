#include <assert.h>
#include <stdint.h>
#if DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/uio.h>

#include <fcntl.h>
#include <unistd.h>

struct bootinfo {
	uint32_t bi_pvd;
	uint32_t bi_file;
	uint32_t bi_length;
	uint32_t bi_csum;
	uint32_t bi_reserved[10];
};

int getbootfilelen(const char *file)
{
	int fd, len;
	fd = open(file, O_RDONLY);
	assert(fd != -1);
	len = lseek(fd, 0, SEEK_END);
	close(fd);
	return len;
}

int getbootfilecsum(const char *file)
{
	/* Checksum is all 32-bit parts of bootfile after 64 byte offset
	   added together. */
	uint32_t b, csum;
	int fd;
	fd = open(file, O_RDONLY);
	assert(fd != -1);
	lseek(fd, 64, SEEK_SET);
	csum = 0;
	while (read(fd, &b, 4) == 4) {
		csum += b;
	}
	close(fd);
	return csum;
}

int getbootfilelocation(const char *file, const char *iso)
{
	/* This is arguably wrong; we should parse the ISO tables
	   to find the location. */
	uint32_t searchb[8], b[8];
	int ffd, ifd;
	int i, all, loc;

	/* Pull first 32 bytes from bootfile. */
	ffd = open(file, O_RDONLY);
	assert(ffd != -1);
	assert(read(ffd, &searchb, 32) == 32);
	close(ffd);

	/* Find 32 matching bytes in ISO. ifd's offset will be the
	   location + 32. */
	ifd = open(iso, O_RDONLY);
	assert(ifd != -1);
	while (read(ifd, &b, 32) == 32) {
		all = 1;
		for (i = 0; i < 8; i++)
			if (searchb[i] != b[i])
				all = 0;
		if (all)
			break;
	}

	loc = (lseek(ifd, 0, SEEK_CUR)-32)/2048;
	close(ifd);
	return loc;
}

int main(int argc, const char **argv)
{
#if DEBUG
	int i;
#endif
	int fd;
	struct bootinfo bi;

	/* argv[1] is bootfile
	   argv[2] is isofile, which will be modified. */

	memset(&bi, 0, sizeof(struct bootinfo));
	bi.bi_pvd = 0x10; /* XXX: We should get this value from ISO tables. */
	bi.bi_file = getbootfilelocation(argv[1], argv[2]);
	bi.bi_length = getbootfilelen(argv[1]);
	bi.bi_csum = getbootfilecsum(argv[1]);

#if DEBUG
	for (i = 0; i < sizeof(struct bootinfo); i++) {
		putchar(((uint8_t*)(&bi))[i]);
	}
#endif

	fd = open(argv[2], O_WRONLY);
	assert(fd != -1);
	assert(lseek(fd, bi.bi_file*2048+8, SEEK_SET) == bi.bi_file*2048+8);
	assert(write(fd, &bi, sizeof(struct bootinfo))
		== sizeof(struct bootinfo));
	close(fd);
	return 0;
}
