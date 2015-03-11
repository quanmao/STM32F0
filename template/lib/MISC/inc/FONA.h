#ifndef __FONA_H
#define __FONA_H

/* includes ---------------------------------------------------------------- */
#include "Serial.h"
#include "Digital.h"
#include "Delay.h"

/* defines ----------------------------------------------------------------- */
#define INIT		  0
#define ECHO			1
#define PIN		  	2
#define STANDBY 	3
#define RECEIVE 	4
#define POWER_ON	5
#define POWER_OFF 6

#define BOOT_TIME_LOW 	1000 // 3sec
#define BOOT_TIME_HIGH 	3000 // 1sec
#define TIMEOUT 				1000 // 1sec

/* class ------------------------------------------------------------------- */
class FONA
{
	private:
		
		Serial* m_serial;
		DigitalOut m_key;
		DigitalIn m_status;
	
		char m_message[128];
		char m_number[16];	
		
		char m_reply[256];
		char m_state;
		char m_pstate;
		char m_ready;
		int m_timer;
	
		void send(char* command, char* reply);
	
	public:
		
		FONA(Serial* serialx, GPIO_common key, GPIO_common status);
		void update(void);
		void on(void);
		void off(void);
		char ready(void);
		char send_sms(char* number, char* message);
		void timer(void);
};

#endif
