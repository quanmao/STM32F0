/*!
 * \file HCSR04.cpp
 * \brief Ultrasonic sensor API.
 * \author Rémi.Debord
 * \version 1.0
 * \date 02 juillet 2015
 *
 * HCSR04 Ultrasonic sensor API.
 *
 *
 */

#include "HCSR04.h"

/*!
 *  \brief Constructor
 *
 *  HCSR04 constructor.
 *
 *  \param trigger : trigger pin
 *  \param echo : InterruptIn object address (echo)
 *  \param timer : timer object address
 */

HCSR04 :: HCSR04(GPIO_common trigger, InterruptIn* echo, Timer* timer): m_trigger(trigger)
{
	m_echo = echo;
	m_timer = timer;
	
	m_state = HCSR04_WAIT;
	m_flag = 0;
	m_distance = 0;
	
	timer->start();
}

/*!
 *  \brief Update
 *
 *  Manage HCSR04 measure.
 *
 */

void HCSR04 :: update(void)
{
	switch(m_state)
	{
		case HCSR04_WAIT:
			m_t[0] = m_timer->read_us();
			
			m_trigger = 0;
			
			// Wait 50 ms before next reading
			if((m_t[0] - m_t[1]) >= HCSR04_WAIT_TIME)
			{
				m_t[1] = m_timer->read_us();
				m_state = HCSR04_PULSE;
			}
			break;
				
		case HCSR04_PULSE:
			m_t[0] = m_timer->read_us();
			
			m_trigger = 1;
			
			// 10 us ?
			if((m_t[0] - m_t[1]) >= HCSR04_PULSE_TIME)
			{
				m_trigger = 0;
					
				m_t[0] = m_timer->read_us();
				m_t[1] = m_t[0];
					
				m_state = HCSR04_ECHO;
					
				m_timeout = HCSR04_TIMEOUT;
			}
			break;
				
		case HCSR04_ECHO:
			// Wait edges
			if(m_flag)
			{
				m_flag = 0;
				
				// Echo pulse duration (us)
				m_duration = m_t[1] - m_t[0];
				
				// Distance = (duration in us * speed of sound in cm/us) / 2
				m_distance = m_duration / HCSR04_COEF;
					
				m_state = HCSR04_WAIT;
			}
			// No response under 100 ms ?
			else if(m_timeout == 0)
			{
				m_t[0] = m_timer->read_us();
				m_t[1] = m_t[0];
					
				m_state = HCSR04_WAIT;
			}
			break;
	}
}

/*!
 *  \brief Get
 *
 *  Get distance in cm.
 *
 *  \return distance
 */

int HCSR04 :: get(void)
{	
	int value = 0;
	
	if((m_distance >= HCSR04_MIN) && (m_distance <= HCSR04_MAX))
	{
		value = m_distance;
	}
	
	return value;
}

/*!
 *  \brief IRQ
 *
 *  Need to be placed in InterruptIn echo callback.
 *
 */

void HCSR04 :: irq(void)
{	
	// Rising edge ?
	if(m_echo->read())
	{
		m_t[0] = m_timer->read_us();
	}
	// Falling edge ?
	else
	{
		m_t[1] = m_timer->read_us();
		m_flag = 1;
	}
}

/*!
 *  \brief Manage HCSR04 base time 
 *
 *  Note: Place it into a ticker callback of 1 ms
 *
 */

void HCSR04 :: timer(void)
{
	if(m_timeout) m_timeout--;
}
