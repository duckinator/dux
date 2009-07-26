void _start(void)
{
	const char *argv[1] = {
		"user"
	};
	main(1, argv);
	while (1)
		;
}

int main(int argc, char const* argv[])
{
	/*
	__asm__ __volatile__ (" \
			mov $1, %%eax; \
			mov $1024, %%ebx; \
			int $0x80; \
			" : : : "eax");

	char *a = "a";
	__asm__ __volatile__ (" \
			mov $0, %%eax; \
			mov %0, %%ebx; \
			int $0x80; \
			" : : "m" (a) : "eax", "ebx");
	*/
	puthex(1024);
	puts("\n");
	putdec(1024);
	puts("\n");
	puts("ohi");
	return 0;
}
