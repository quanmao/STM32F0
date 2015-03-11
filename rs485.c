#include "main.h"

// RX, TX, DE
Serial rs485(USART2, PA3, PA2, PA1);

int main(void)
{
  Systick_Init();
	
  while (1)
  {
		rs485.write((char *)"Hello world!", 12);
		
		Delay(1000);
  }
}
