#include "main.h"
#include "SevenSeg.h"
#include "DS3231.h"
#include "Button.h"

Button button(PB15);

Ticker tick(TIM16);

DigitalOut led1(PC8);
DigitalOut led2(PC9);

void GlobalBaseTime(void)
{
	button.timer();
}

int main(void)
{	
	char value = 0;
	
	Systick_Init();
	
	tick.attach_us(&GlobalBaseTime, 1000);
	
  while (1)
  {
		button.update();
		
		value = button.get();
		
		switch(value)
		{
			case SHORT_PRESS:
				led1 = !led1;
				break;
			
			case LONG_PRESS:
				led2 = !led2;
				break;
			
			case CONTINUOUS_PRESS:
				led1 = !led1;
				led2 = !led2;
				break;
			
			default:
				break;
		}
  }
}