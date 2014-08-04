#include "main.h"

/* Serial port config */
//Serial serial(USART1, PB7, PB6);
//Serial serial(USART1, PA10, PA9);
Serial serial(USART2, PA3, PA2);

int main(void)
{
	char buffer[255];
	int length;
	
  Systick_Init();
	
	/* Change baudrate (default: 9600) */
	serial.baud(115200);
	
  while (1)
  {
		/* echo mode */
		length = serial.read(buffer);
		
		if(length > 0)
		{
			serial.write(buffer, length);
		}
  }
}
