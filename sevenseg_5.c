#include "main.h"
#include "SevenSeg.h"

const char test1[8] = {0x40, 0x02, 0x01, 0x20, 0x40, 0x04, 0x08, 0x10}; 
const char test2[8] = {0x3F, 0x7D, 0x7E, 0x5F, 0x3F, 0x7B, 0x77, 0x6F}; 
const char test3[6] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20};

// Ticker for base timer
Ticker tick(TIM16);

// Array of digital out (segment)
DigitalOut segment[] = {DigitalOut(PA0), DigitalOut(PA1), DigitalOut(PA4), DigitalOut(PF5),
                        DigitalOut(PF4), DigitalOut(PA2), DigitalOut(PA3), DigitalOut(PA5)};

// Array of digital out (digit)
DigitalOut digit[] = {DigitalOut(PB0, GPIO_OType_OD), DigitalOut(PB1, GPIO_OType_OD),
											DigitalOut(PB2, GPIO_OType_OD), DigitalOut(PB10, GPIO_OType_OD),
											DigitalOut(PB11, GPIO_OType_OD), DigitalOut(PB12, GPIO_OType_OD)};

// One seven segment is composed of an array of segment and one digit pin
SevenSeg sevenSeg0(segment, &digit[0]);
SevenSeg sevenSeg1(segment, &digit[1]);
SevenSeg sevenSeg2(segment, &digit[2]);
SevenSeg sevenSeg3(segment, &digit[3]);
SevenSeg sevenSeg4(segment, &digit[4]);
SevenSeg sevenSeg5(segment, &digit[5]);
										
// Create group of seven segment
SevenSegGroup sevenSegGroup;

int delay = 0;
int inc = 0;
											
void GlobalBaseTime(void)
{
	sevenSegGroup.timer();
	
	if(delay) delay--;
}

int main(void)
{	
	Systick_Init();
	
	// Callback executed every 1 ms (1000 us)
	tick.attach_us(&GlobalBaseTime, 1000);
	
	// Add seven segment into a group
	sevenSegGroup.add(&sevenSeg0);
	sevenSegGroup.add(&sevenSeg1);
	sevenSegGroup.add(&sevenSeg2);
	sevenSegGroup.add(&sevenSeg3);
	sevenSegGroup.add(&sevenSeg4);
	sevenSegGroup.add(&sevenSeg5);
	
	//sevenSegGroup.effect((char*)test1, 8, 3, 50);	
	sevenSegGroup.effect((char*)test2, 8, 4, 50);	
	//sevenSegGroup.effect((char*)test3, 6, 1, 50);	
	
  while (1)
  {
		sevenSegGroup.update();
  }
}