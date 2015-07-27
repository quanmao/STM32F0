#include "main.h"
#include "HCSR04.h"

Ticker tick(TIM16);

Timer timer(TIM2);

InterruptIn echo(PC7);

HCSR04 hcsr04(PC8, &echo, &timer);

int distance = 0;

void EchoEdges(void);
void GlobalBaseTime(void);

int main(void)
{
 	Systick_Init();
	
	tick.attach_us(&GlobalBaseTime, 1000);
	
	echo.risefall(&EchoEdges);
	
  while (1)
  {
		hcsr04.update();
		
		distance = hcsr04.get();
  }
}

void EchoEdges(void)
{
	hcsr04.irq();
}

void GlobalBaseTime(void)
{
	hcsr04.timer();
}