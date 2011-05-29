#include <stdint.h>
#include <metodo/metodo.h>
#include <hal/task.h>

// FIXME: Why wont HalSwitchToUserMode() actually enable interrupts?
void HalSwitchToUserMode()
{
	// Set up a stack structure for switching to user mode.
	__asm__ volatile("cli");
	HalGDTLoadEsp0IntoTSS();
	__asm__ volatile(
		//"cli;"
		"mov $0x23, %ax;"  // Store user mode data selector in ax register
		"mov %ax, %ds;"    // Set ds, es, fs, and gs to user mode data selector
		"mov %ax, %es;"
		"mov %ax, %fs;"
		"mov %ax, %gs;"
		
		"mov %esp, %eax;"
		"pushl $0x23;"
		"pushl %eax;"
		"pushf;"
		
		// The next 3 lines are the same as `sti`
		"pop %eax;"        // Get EFLAGS back into EAX. The only way to read EFLAGS is to pushf then pop.
		"or $0x200, %eax;" // Set the IF flag.
		"push %eax;"       // Push the new EFLAGS value back onto the stack.
		"pushl $0x1B;"
		
		"push $1f;"        // $1f means "the address of the next label '1:', looking forward
		"iret;"
		"1:"
	);
}

void HalSetTSS(tss_entry_t *entry, int32_t num, uint16_t sso, uint32_t esp0)
{
	// calculate base and limit of entry
	uint32_t base = (uint32_t) entry;
	uint32_t limit = base + sizeof(entry);

	// add TSS descriptor address to GDT
	//HalGDTSetGate(num, base, limit, 0xE9, 0x00);

	// ensure descriptor is initially zero
	memset(&entry, 0, sizeof(entry));

	// Here we set the cs, ss, ds, es, fs and gs entries in the TSS. These specify what
	// segments should be loaded when the processor switches to kernel mode. Therefore
	// they are just our normal kernel code/data segments - 0x08 and 0x10 respectively,
	// but with the last two bits set, making 0x0b and 0x13. The setting of these bits
	// sets the RPL (requested privilege level) to 3, meaning that this TSS can be used
	// to switch to kernel mode from ring 3.
	entry->cs   = 0x0b;
	entry->ss = entry->ds = entry->es = entry->fs = entry->gs = 0x13;
}
