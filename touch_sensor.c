#include "main.h"

Touch touch1(PA3, PA1);
Touch touch2(PB2, PB1);

DigitalOut led1(PC9);
DigitalOut led2(PC8);

int value1 = 0;
int value2 = 0;

int main(void)
{
  Systick_Init();
	
  while (1)
  {	
		value1 = touch1.get_value();
		value2 = touch2.get_value();
		
		if(touch1.pressed())
		{
			led1 = 1;
		}
		else led1 = 0;		
		
		if(touch2.pressed())
		{
			led2 = 1;
		}
		else led2 = 0;
  }
}
