void _start(void)
{
	const char **argv = {
		"user"
	};
	main(1, argv);
	while (1)
		;
}

int main(int argc, char const* argv[])
{
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
	return 0;
}
