#include "main.h"

int value1 = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;
int value5 = 0;

AnalogIn_DMA ain1(PC5); // Channel 15
AnalogIn_DMA ain2(PA5); // Channel 5
AnalogIn_DMA ain3(PA1); // Channel 1
AnalogIn_DMA ain4(PC4); // Channel 14
AnalogIn_DMA ain5(PB0); // Channel 8

int main(void)
{
	Systick_Init();
	
  while (1)
  {
		value1 = ain1.read();
		value2 = ain2.read();
		value3 = ain3.read();
		value4 = ain4.read();
		value5 = ain5.read();
  }
}
