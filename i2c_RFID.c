#include "main.h"
#include <string.h>

// Led configuration
DigitalOut led1(PC8);

// I2C configuration
I2C i2c(I2C2, PF7, PF6);

// PN532 configuration
PN532 nfc(&i2c);

// Tick for base time
Ticker tick(TIM16);

void GlobalBaseTime(void);

int main(void)
{
	char uid[10] = "";
	char firmware;
	
	Systick_Init();
	
	// Execute GlobalTime every 1 ms
	tick.attach(&GlobalBaseTime, 1);
	
	// Get firmware
	firmware = nfc.getFirmware();
	
	// Configure SAM
	nfc.setSAM();
	
	while(firmware)
	{
		nfc.update();
		
		if(nfc.getUID(uid))
		{
			led1 = !led1;
		}
	}
}

void GlobalBaseTime(void)
{
	nfc.timer();
}
