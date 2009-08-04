#ifndef I386_TBY8VD0E

#define I386_TBY8VD0E

/* IDT */
typedef struct IDTD {
	uint16_t size;
	uint32_t offset;
} IDTD, *PIDTD;

typedef struct IDTG {
	uint16_t offset_1;
	uint16_t selector;
	uint8_t zero;
	uint8_t type;
	uint16_t offset_2;
} IDTG, *PIDTG;

#define IDT_TASK 0x5
#define IDT_INTR16 0x6
#define IDT_INTR32 0x7
#define IDT_TRAP16 0xe
#define IDT_TRAP32 0xf

void HalInitIDT(void);
void HalLoadIDT(void);
void HalSetIDTGate(OUT PIDTG idtg, IN uint32_t offset, IN uint16_t selector, IN uint8_t priv, IN uint8_t sys, IN uint8_t gatetype);

/* Ports */
inline void HalOutPort(uint16_t port, uint8_t val);
inline uint8_t HalInPort(uint16_t port);

#endif /* end of include guard: I386_TBY8VD0E */
