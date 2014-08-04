#include "main.h"
	
Ticker tick1(TIM17);
DigitalOut led1(PC8);

Ticker tick2(TIM16);
DigitalOut led2(PC9);

void blink1(void)
{
	led1 = !led1;
}

void blink2(void)
{
	led2 = !led1;
}

int main(void)
{
	Systick_Init();

	tick1.attach(&blink1, 500);
	tick2.attach(&blink2, 500);
	
  while(1)
  {
		
  }
}
