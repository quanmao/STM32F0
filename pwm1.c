#include "main.h"

#define FREQUENCY 1000 // 1kHz

PwmOut pwm(PA9, FREQUENCY, TIM1_CH2);

int main(void)
{
  Systick_Init();
	
	// Set duty cycle to 50%
	pwm = 0.5;
	
  while (1)
  {
  }
}
