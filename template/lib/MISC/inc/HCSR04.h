#ifndef __HCSR04_H
#define __HCSR04_H

/* includes ---------------------------------------------------------------- */
#include "Digital.h"
#include "Timer.h"

/* defines ----------------------------------------------------------------- */
#define HCSR04_TIMEOUT 			100 	// 100 ms
#define HCSR04_PULSE_TIME 	10		// 10 us
#define HCSR04_WAIT_TIME		50000	// 50 ms (50000 us)

#define HCSR04_SPEED_OF_SOUND 0.034 // 340 m/s => 0.034 cm / us
#define HCSR04_COEF		 (1 / (HCSR04_SPEED_OF_SOUND / 2)) // Divide by two (return trip)

#define HCSR04_WAIT 	0x00
#define HCSR04_PULSE 	0x01
#define HCSR04_ECHO		0x02

#define HCSR04_MIN 0
#define HCSR04_MAX 200

/* class ------------------------------------------------------------------- */
class HCSR04
{
	private:
		
		DigitalOut m_trigger;
		InterruptIn* m_echo;
		Timer* m_timer;
		
		char m_state;
		char m_flag;
		int m_t[2];
		int m_timeout;
		int m_duration;
		int m_distance;
	
	public:
		
		HCSR04(GPIO_common trigger, InterruptIn* echo, Timer* timer);
		void update(void);
		int get(void);
		void irq(void);
		void timer(void);
	
		static int round(int number, int divisor);
};

#endif
