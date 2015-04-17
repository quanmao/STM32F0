#include "main.h"

CLOCK clock;
Power power;

DigitalOut led1(PC9);
DigitalOut led2(PC8);

Time time;
Date date;

void toggle(void)
{
	led1 = !led1;
	
	// Relaunch alarm in 10 sec
	clock.alarm(10, &toggle);
}

int main(void)
{
	char i = 0;
	
	Systick_Init();
	
	time.hours = 10;
	time.minutes = 30;
	time.seconds = 0;
	
	clock.set(time);
	
	// Alarm set to 10 sec
	clock.alarm(120, &toggle);
	
  while (1)
  {
		clock.get(&time);
		
		Delay(100);
		led2 = !led2;
		i++;
		
		if(i >= 20)
		{
			power.standby(1);
		}
  }
}
