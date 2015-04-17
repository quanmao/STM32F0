#include "main.h"
#include <string.h>

#define SLAVE_ADDRESS	(0xB1) // STM32F0 slave

//#define MASTER

DigitalOut led(PC8);

#ifdef MASTER
I2C i2c(I2C2, PB11, PB10);
#else
I2C i2c(I2C2, PF7, PF6, SLAVE_ADDRESS);
#endif

int main(void)
{
	char buffer[255] = "";
	
	Systick_Init();
	
	while(1)
	{
#ifdef MASTER
		// Data to send
		strcpy(buffer, "Hello World!");
		
		// Store data
		i2c.write(SLAVE_ADDRESS, buffer, 12);
		
		Delay(1000);
		
		led = !led;
#else		
		if(i2c.read_s(buffer))
		{
			if(strcmp(buffer, "Hello World!\0") == 0)
			{
				led = !led;
			}
		}
#endif
	}
}