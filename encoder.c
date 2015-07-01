#include "main.h"
#include "Encoder.h"

DigitalOut led1(PC8);
DigitalOut led2(PC9);

InterruptIn channelA(PB13);
InterruptIn channelB(PB14);

Encoder encoder(&channelA, &channelB);

void irqA(void);
void irqB(void);

int x = 0;

int main(void)
{
	Systick_Init();
	
	channelA.risefall(&irqA);
	channelB.risefall(&irqB);
	
  while (1)
  {
		led1 = channelA.read();
		led2 = channelB.read();
		
		x = encoder.read();
  }
}

void irqA(void)
{
	encoder.irq();
}

void irqB(void)
{
	encoder.irq();
}