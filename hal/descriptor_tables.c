#include <descriptor_tables.h>

//extern void memset();

extern void HalGdtFlush(int);

// Internal function prototypes.
/*static void HalGdtInstall();*/
static void HalGdt_SetGate(int num, int base, int limit, int access, int gran);

HalGdtEntry_t gdt_entries[5];
HalGdtPointer_t	gdt_ptr;
HalIdtEntry_t idt_entries[256];
HalIdtPointer_t	idt_ptr;

// Lets us access our ASM functions from our C code.
extern void HallTssFlush();
// Internal function prototypes.
//static void HalWriteTss(int num,int ss0,int esp0);

HalTssEntry_t tss_entry;

void HalGdtInstall()
{
	gdt_ptr.limit = (sizeof(HalGdtEntry_t) * 5) - 1;
	gdt_ptr.base  = (int)&gdt_entries;

	HalGdt_SetGate(0, 0, 0, 0, 0);					 // Null segment
	HalGdt_SetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	HalGdt_SetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	HalGdt_SetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	HalGdt_SetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	HalGdtFlush((int)&gdt_ptr);
}

// Set the value of one GDT entry.
static void HalGdt_SetGate(int num, int base, int limit, int access, int gran)
{
	gdt_entries[num].base_low	 = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high	= (base >> 24) & 0xFF;

	gdt_entries[num].limit_low	= (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access		= access;
}

// Initialise our task state segment structure.
/*static void HalWriteTss(int num, int ss0, int esp0)
{
	// Firstly, let's compute the base and limit of our entry into the GDT.
	int base = (int) &tss_entry;
	int limit = base + sizeof(tss_entry);

	// Now, add our TSS descriptor's address to the GDT.
	HalGdt_SetGate(num, base, limit, 0xE9, 0x00);

	// Ensure the descriptor is initially zero.
	memset(&tss_entry, 0, sizeof(tss_entry));

	tss_entry.ss0  = ss0;  // Set the kernel stack segment.
	tss_entry.esp0 = esp0; // Set the kernel stack pointer.

	// Here we set the cs, ss, ds, es, fs and gs entries in the TSS. These specify what
	// segments should be loaded when the processor switches to kernel mode. Therefore
	// they are just our normal kernel code/data segments - 0x08 and 0x10 respectively,
	// but with the last two bits set, making 0x0b and 0x13. The setting of these bits
	// sets the RPL (requested privilege level) to 3, meaning that this TSS can be used
	// to switch to kernel mode from ring 3.
	tss_entry.cs	= 0x0b;
	tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
}*/

void HalSetKernelStack(int stack)
{
	tss_entry.esp0 = stack;
}
