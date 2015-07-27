#ifndef __FONA_H
#define __FONA_H

/* includes ---------------------------------------------------------------- */
#include "Serial.h"
#include "Digital.h"
#include "Delay.h"

/* defines ----------------------------------------------------------------- */
#define TIMEOUT 2000 	// 1sec
#define CTRLZ		0x1A	// "Substitute" in ASCII
	
/* class ------------------------------------------------------------------- */
class FONA
{
	private:
		
		Serial* m_serial;
	
		DigitalIn m_status;
		DigitalOut m_key;
		DigitalOut m_reset;

		int m_timer;

		char write(char* command, char* reply);
		char read(char* command, char* reply);
		char find(int number, char* buffer, char* output, char c);
	
	public:
		
		FONA(Serial* serialx, GPIO_common status, GPIO_common key, GPIO_common reset);
		char on(void);
		char off(void);
		char echo(char state);
		char pin(char* code);
		char send(char* number, char* message);
		char recv(char index, char* number, char* message);
		char clear(char index);
		char network(char* output);
		int battery(void);
		int strength(void);
		void timer(void);
};

#endif
