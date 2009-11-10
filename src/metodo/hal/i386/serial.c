
/*
 * This code is based on information from
 * http://www.nondot.org/sabre/os/files/Communication/ser_port.txt
 */

#include <metodo/metodo.h>

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

void UartSend(char c)
{
	if (c == '\n')
		UartSend_int('\r');
	UartSend_int(c);
}

static void UartSend_int(char c)
{
	/* wait until UART is ready to send */
	while ((HalInPort(UART_BASE_REGISTER + LineStatus) & THRE) == 0);

	HalOutPort(UART_BASE_REGISTER, c);
}

int UartInit()
{
	HalOutPort(UART_BASE_REGISTER + LineControl, DLAB);
	HalOutPortWord(UART_BASE_REGISTER, UART_BAUDRATE_DIVISOR);
	HalOutPort(UART_BASE_REGISTER + LineControl, UART_LCR);
	HalOutPort(UART_BASE_REGISTER + ModemControl, 0);
}

struct DisplayDevice UartDisplayDevice = {
	.Init		= UartInit,
	.DisplayChar	= UartSend,
	.DisplayClear	= NULL,	/* nothing, for now */
};
