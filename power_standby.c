#include "main.h"

Power power;

DigitalOut led1(PC9);

int main(void)
{
	char i = 0;
	
	Systick_Init();
	
  while (1)
  {		
		Delay(250);
		led1 = !led1;
		
		if(i >= 20)
		{
			i = 0;
			led1 = 0;
			
			// PA0 WkUp1
			power.standby(1);
		}
		else i++;
  }
}