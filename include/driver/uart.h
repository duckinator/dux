#ifndef DRIVER_UART_H
#define DRIVER_UART_H

#include <driver/driver.h>

#define COM1			0x3f8
#define UART_BASE_REGISTER	COM1

/* 115200 Baud */
#define UART_BAUDRATE_DIVISOR	0x01
/* 8N1 */
#define UART_LCR		0x1b

/* Line Control Register values */
enum UART_LCR_Values {
	DLAB		= 0x80,
};

/* Line Status Register values */
enum UART_LSR_Values {
	THRE		= 0x20, /* Transmitter Holding Register Empty */
};

enum UART_Registers {
	LineControl	= 0x03,
	ModemControl	= 0x04,
	LineStatus	= 0x05,
};

void UartSend(char c);
void UartSendString(const char *str);
static void UartSend_int(char c);
int UartInit();

#endif /* end of include guard: HAL_UART_H */
