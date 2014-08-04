#include "main.h"
	
Ticker tick(TIM16);
DigitalOut led1(PC8);
DigitalOut led2(PC9);

void blink(void)
{
	led1 = !led1;
}

int main(void)
{
	Systick_Init();

	tick.attach_us(&blink, 15);
	
  while(1)
  {
		led2 = !led2;
		Delay(1);
  }
}
