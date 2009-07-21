// A struct describing an interrupt gate.
struct HalIdtEntry_struct
{
   unsigned short base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   unsigned short sel;                 // Kernel segment selector.
   unsigned char always0;             // This must always be zero.
   unsigned char flags;               // More flags. See documentation.
   unsigned short base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct HalIdtEntry_struct HalIdtEntry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct HalIdtPointer_struct
{
   unsigned short limit;
   unsigned short base;                // The address of the first element in our HalIdtEntry_t array.
} __attribute__((packed));
typedef struct HalIdtPointer_struct HalIdtPointer_t;

struct HalGdtEntry_struct
{
   unsigned short limit_low;           // The lower 16 bits of the limit.
   unsigned short base_low;            // The lower 16 bits of the base.
   unsigned short base_middle;         // The next 8 bits of the base.
   unsigned short access;              // Access flags, determine what ring this segment can be used in.
   unsigned short granularity;
   unsigned short base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct HalGdtEntry_struct HalGdtEntry_t;

struct HalGdtPointer_struct
{
   unsigned short limit;               // The upper 16 bits of all selector limits.
   unsigned short base;                // The address of the first HalGdtEntry_t struct.
}
 __attribute__((packed));
typedef struct HalGdtPointer_struct HalGdtPointer_t; 

// Initialisation function is publicly accessible.
void HalInitDescriptorTables();

// A struct describing a Task State Segment.
struct HalTssEntry_struct 
{
   unsigned short prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
   unsigned short esp0;       // The stack pointer to load when we change to kernel mode.
   unsigned short ss0;        // The stack segment to load when we change to kernel mode.
   unsigned short esp1;       // Unused...
   unsigned short ss1;
   unsigned short esp2;
   unsigned short ss2;
   unsigned short cr3;
   unsigned short eip;
   unsigned short eflags;
   unsigned short eax;
   unsigned short ecx;
   unsigned short edx;
   unsigned short ebx;
   unsigned short esp;
   unsigned short ebp;
   unsigned short esi;
   unsigned short edi;
   unsigned short es;         // The value to load into ES when we change to kernel mode.
   unsigned short cs;         // The value to load into CS when we change to kernel mode.
   unsigned short ss;         // The value to load into SS when we change to kernel mode.
   unsigned short ds;         // The value to load into DS when we change to kernel mode.
   unsigned short fs;         // The value to load into FS when we change to kernel mode.
   unsigned short gs;         // The value to load into GS when we change to kernel mode.
   unsigned short ldt;        // Unused...
   unsigned short trap;
   unsigned short iomap_base;
} __attribute__((packed));

typedef struct HalTssEntry_struct HalTssEntry_t; 
