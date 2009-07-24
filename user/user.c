void _start(void)
{
	main();
	while (1)
		;
}

int main(int argc, char const* argv[])
{
	__asm__ __volatile__ (" \
			mov $1, %eax; \
			mov $1024, %ebx; \
			int $0x80; \
			");

	char *a = "a";
	__asm__ __volatile__ ("mov $0, %eax");
	__asm__ __volatile__ ("mov %0, %%eax" : : "m"(&a[0]) : "eax");
	__asm__ __volatile__ ("int $0x80");
	return 0;
}
