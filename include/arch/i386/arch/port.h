#ifndef PORT_67M5ZDYL

#define PORT_67M5ZDYL

#include <stdint.h>
#include <arch/arch.h>

inline void ArchOutPort(uint16_t port, uint8_t data);
inline uint8_t ArchInPort(uint16_t port);

#endif /* end of include guard: PORT_67M5ZDYL */
