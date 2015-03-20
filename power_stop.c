#include "main.h"

Power power;

DigitalOut led1(PC9);
DigitalOut led2(PC8);

InterruptIn button(PA0);

void toggle(void)
{
	led2 = !led2;
}

int main(void)
{
	char i = 0;
	
	Systick_Init();
	
	button.rise(&toggle);
	
  while (1)
  {		
		Delay(250);
		led1 = !led1;
		
		if(i >= 20)
		{
			i = 0;
			led1 = 0;
			
			power.stop();
		}
		else i++;
  }
}
