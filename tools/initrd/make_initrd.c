#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct initrd_header
{
	unsigned char magic; // The magic number is there to check for consistency.
	char name[64];
	unsigned int offset; // Offset in the initrd the file starts.
	unsigned int length; // Length of the file.
};

int main(char argc, char **argv)
{
	FILE *stream, *wstream;
	int i;
	int nheaders = argc-1;
	struct initrd_header headers[64];
	unsigned int off = sizeof(struct initrd_header) * 64 + sizeof(int);

	printf("Writing %i files to initrd\n", nheaders);
	printf("size of header: %d\n", sizeof(struct initrd_header));

	for(i = 1; i <= nheaders; i++) {
		printf("writing file %s at 0x%x\n", argv[i], off);
		strcpy(headers[i].name, argv[i]);
		printf("file name: %s\n", headers[i].name);
		headers[i].offset = off;
		stream = fopen(argv[i], "r");
		if(stream == 0) {
			printf("Error: file not found: %s\n", argv[i]);
			return 1;
		}
		fseek(stream, 0, SEEK_END);
		headers[i].length = ftell(stream);
		off += headers[i].length;
		fclose(stream);
		headers[i].magic = 0xBF;
	}

	wstream = fopen("./initrd.img", "w");
	unsigned char *data = (unsigned char *)malloc(off);
	fwrite(&nheaders, sizeof(int), 1, wstream);
	fwrite(headers, sizeof(struct initrd_header), 64, wstream);

	for(i = 1; i <= nheaders; i++) {
		stream = fopen(argv[i], "r");
		unsigned char *buf = (unsigned char *)malloc(headers[i].length);
		fread(buf, 1, headers[i].length, stream);
		fwrite(buf, 1, headers[i].length, wstream);
		fclose(stream);
		free(buf);
	}

	fclose(wstream);
	free(data);

	return 0;
}
