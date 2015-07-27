/*!
 * \file Encoder.cpp
 * \brief Rotary encoder API.
 * \author Rémi.Debord
 * \version 1.0
 * \date 01 juillet 2015
 *
 * Rotary encoder library (!= motor encoder).
 *
 * Thanks to Mauro Alfieri (http://www.mauroalfieri.it/elettronica/rover-5-usare-lencoder.html)
 * and Gavin Kistner (http://phrogz.net/round-to-nearest-via-modulus-division)
 *
 */

#include "Encoder.h"

const signed char encSequence[4][4] = { 0, -1,  1,  2, 1,  0,  2, -1, -1,  2,  0,  1, 2,  1, -1,  0};

/*!
 *  \brief Constructor
 *
 *  Encoder constructor.
 *
 *  \param A : InterruptIn object address (channel A)
 *  \param A : InterruptIn object address (channel B)
 */
																		 
Encoder :: Encoder(InterruptIn* A, InterruptIn* B)
{
	m_A = A;
	m_B = B;
	
	m_A->mode(GPIO_PuPd_UP);
	m_B->mode(GPIO_PuPd_UP);
	
	m_value = (m_B->read() << 1) + m_A->read();
	m_old = m_value;
	
	m_value = 0;
}

/*!
 *  \brief Get
 *
 *  Read accumulated value.
 *
 *  \return counter: accumulated value
 */

int Encoder :: get(void)
{		
	return (Encoder :: round(m_accum, 4) / 4);
}

/*!
 *  \brief IRQ
 *
 *  Need to be placed in InterruptIn channel A and B callback.
 *
 */

void Encoder :: irq(void)
{	
	m_value = (m_B->read() << 1) + m_A->read();
	
	// New value ?
	if(m_value != m_old)
	{
		// Sequence valid ? (!= 2)
		if(encSequence[m_value][m_old] != 2)
		{
			m_accum += encSequence[m_value][m_old];
			
			m_old = m_value;
		}
	}
}

/*!
 *  \brief round
 *
 *  Round a number to the nearest value.
 *
 * \param number: number to round
 * \param divisor: number divisor
 */

int Encoder :: round(int number, int divisor)
{
	int half = divisor / 2;
	int result = 0;
	
	if(number < 0) half = -half;
	
	result = ((number + half) - ((number + half) % divisor));
	
	return result;
}
