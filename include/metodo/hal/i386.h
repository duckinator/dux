#ifndef I386_TBY8VD0E

#define I386_TBY8VD0E

/* Exceptions */
void isr0(void);
void isr1(void);
void isr2(void);
void isr3(void);
void isr4(void);
void isr5(void);
void isr6(void);
void isr7(void);
void isr8(void);
void isr9(void);
void isr10(void);
void isr11(void);
void isr12(void);
void isr13(void);
void isr14(void);
void isr15(void);
void isr16(void);
void isr17(void);
void isr18(void);
void isr19(void);
void isr20(void);
void isr21(void);
void isr22(void);
void isr23(void);
void isr24(void);
void isr25(void);
void isr26(void);
void isr27(void);
void isr28(void);
void isr29(void);
void isr30(void);
void isr31(void);

/* IDT */
typedef struct IDTD {
	uint16_t size;
	uint32_t offset;
} __attribute__((packed)) IDTD, *PIDTD;

typedef struct IDTG {
	uint16_t offset_1;
	uint16_t selector;
	uint8_t zero;
	uint8_t type;
	uint16_t offset_2;
} __attribute__((packed)) IDTG, *PIDTG;

#define IDT_TASK 0x5
#define IDT_INTR16 0x6
#define IDT_INTR32 0xe
#define IDT_TRAP16 0x7
#define IDT_TRAP32 0xf

void HalInitGDT(void);
void HalInitIDT(void);
void HalSetIDTGate(IN size_t n, IN uint32_t offset, IN uint16_t selector, IN uint8_t priv, IN uint8_t sys, IN uint8_t gatetype);

/* Ports */
void HalOutPort(uint16_t port, uint8_t val);
uint8_t HalInPort(uint16_t port);
void HalOutPortWord(uint16_t port, uint16_t val);
uint16_t HalInPortWord(uint16_t port);
void HalOutPortLong(uint16_t port, uint32_t val);
uint32_t HalInPortLong(uint16_t port);

static inline void HalIOWait(void);

/* Interrupts */
void HalDisableInterrupts(void);
void HalEnableInterrupts(void);

void HalDisableNMI(void);
void HalEnableNMI(void);

#endif /* end of include guard: I386_TBY8VD0E */
