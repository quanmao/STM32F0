#include "main.h"

CLOCK clock; // Default LSI
//CLOCK clock(RTC_LSI); // LSI (internal 40kHz)
//CLOCK clock(RTC_LSE); // LSE (external 32kHz)

DigitalOut led1(PC9);

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
	Systick_Init();
	
	time.hours = 10;
	time.minutes = 30;
	time.seconds = 0;
	
	clock.set(time);
	
	// Alarm set to 10 sec
	clock.alarm(10, &toggle);
	
  while (1)
  {
		clock.get(&time);
  }
}
