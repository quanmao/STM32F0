#include "main.h"
	
DigitalOut led1(PC8);

Memory memory(MEMORY_START_ADDRESS);

int data;

int main(void)
{
	Systick_Init();
	
	// Read data at address 0
	data = memory.read(0);
	
	// Write with specified address (0)
	memory.write(0, data+1);
	
	// adress auto-increment
	memory.write(data+2);
	memory.write(data+3);
	memory.write(data+4);
	
  while (1)
  {
		led1 = !led1;
		Delay(100);
  }
}
