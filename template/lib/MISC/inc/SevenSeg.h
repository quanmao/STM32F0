#ifndef __SEVENSEG_H
#define __SEVENSEG_H

/* includes ---------------------------------------------------------------- */
#include "Digital.h"

/* defines ----------------------------------------------------------------- */
#define MAX_SEGMENTS 8
#define MAX_DIGITS	 10
#define REFRESH_TIME 20 // 20 ms => 50 fps

/* structure --------------------------------------------------------------- */
struct Effect
{
	int value;
	int timer;
	int select;
	char flag;
};

/* class ------------------------------------------------------------------- */
class SevenSeg
{
	private:
		
		DigitalOut* m_segment[MAX_SEGMENTS];
		DigitalOut* m_digit;
	
	public:
		
		SevenSeg(DigitalOut* segment, DigitalOut* digit);
		void segments(char c);
		void set(char c);
		void set(int number);
		void on(void);
		void off(void);
};

class SevenSegGroup
{
	private:
		
		SevenSeg* m_digit[MAX_DIGITS];
		char m_buffer[MAX_DIGITS];
		char m_tmp[MAX_DIGITS];
		char m_size;
		char m_inc;
		char m_mux;
		int m_timer;

		Effect m_blink;
		Effect m_scroll;
		Effect m_loading;
	
	public:
		
		SevenSegGroup(void);
		void update(void);
		void add(SevenSeg* digit);
		void set(char* buffer, int length);
		void set(int number);
		void select(int segment);
		void blink(int ms);
		void blink(char select, int ms);
		void scroll(int ms);
		void loading(int ms);
		void clear(void);
		void timer(void);
};

#endif
