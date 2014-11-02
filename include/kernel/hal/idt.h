#ifndef HAL_IDT_H
#define HAL_IDT_H

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
} IDTG, *PIDTG;

#define IDT_TASK 0x5
#define IDT_INTR16 0x6
#define IDT_INTR32 0xe
#define IDT_TRAP16 0x7
#define IDT_TRAP32 0xf

void HalInitGDT(void);
void HalInitIDT(void);
void HalSetIDTGate(IN size_t n, IN uint32_t offset, IN uint16_t selector, IN uint8_t priv, IN uint8_t sys, IN uint8_t gatetype);

#endif /* end of include guard: HAL_IDT_H */

