#ifndef __RTC_H
#define __RTC_H

/* includes ---------------------------------------------------------------- */
#include "stm32f0xx_rtc.h"

/* structures -------------------------------------------------------------- */
struct Time
{
	char hours;
	char minutes;
	char seconds;
};

struct Date
{
	int year;
	char month;
	char day;
};

/* class ------------------------------------------------------------------- */
class CLOCK
{
	private:
	
	public:
		
		CLOCK(void);
		void set(Time time);
		void set(Date date);
		void get(Time *time);
		void get(Date *date);
		void alarm(int seconds, void(*f)(void));
	
		static int dow(int year, int month, int day);
};

#endif
