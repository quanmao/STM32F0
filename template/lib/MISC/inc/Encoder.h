#ifndef __ENCODER_H
#define __ENCODER_H

/* includes ---------------------------------------------------------------- */
#include "Digital.h"

/* defines ----------------------------------------------------------------- */

/* class ------------------------------------------------------------------- */
class Encoder
{
	private:
		
		InterruptIn* m_A;
		InterruptIn* m_B;
		char m_value;
		char m_old;
	
		int m_accum;
	
	public:
		
		Encoder(InterruptIn* A, InterruptIn* B);
		int get(void);
		void irq(void);
	
		static int round(int number, int divisor);
};

#endif
