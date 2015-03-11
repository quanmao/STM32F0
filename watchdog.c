#include "main.h"

DigitalOut led1(PC8);
DigitalOut led2(PC9);
	
// DigitalIn pushButton(PA0);
InterruptIn pushButton(PA0);

// 2000 ms timeout
Watchdog watchdog(2000);

char flag = 1;

void Push(void)
{
	led2 = !led2;
	flag = 0;
}

int main(void)
{
	Systick_Init();
	
	pushButton.rise(&Push);
	
	led1 = 0;
	
	Delay(1000);
	
  while (1)
  {
		led1 = 1;
		
		if(flag)
		{
			watchdog.reload();
		}
  }
}
