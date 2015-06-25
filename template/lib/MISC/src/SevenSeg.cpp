#include "SevenSeg.h"
#include "AsciiMap.h"

#include <stdio.h>
#include <string.h>

SevenSeg :: SevenSeg(DigitalOut* segment, DigitalOut* digit)
{
	char i = 0;
	
	for(i = 0; i < MAX_SEGMENTS; i++)
	{
		m_segment[i] = segment++;
	}
	
	m_digit = digit;
}

void SevenSeg :: segments(char c)
{
	char i = 0;
	char value = 0;
	
	for(i = 0; i < MAX_SEGMENTS; i++)
	{
		value = ((c & (0x01 << i)) > 0) ? 1 : 0;
			
		m_segment[i]->write(value);
	}
}

void SevenSeg :: set(char c)
{	
	if(c < 0x7F)
	{
		this->segments(digitAsciiMap[c]);
	}
}

void SevenSeg :: set(int number)
{
	if((number >= 0) && (number < 10))
	{
		this->set((char) (number+0x30));
	}
}

void SevenSeg :: on(void)
{
	m_digit->write(0);
}

void SevenSeg :: off(void)
{
	m_digit->write(1);
}

SevenSegGroup :: SevenSegGroup(void)
{
	// Init value(s)
	m_size = 0;
	m_inc = 0;
	m_timer = 0;
}

void SevenSegGroup :: update(void)
{	
	char i = 0;
	
	// Refresh ?
	if(m_timer == 0)
	{
		m_timer = m_mux;
		
		// SevenSeg object inserted ?
		if(m_size > 0)
		{
			// Special effects using segments ?
			if(m_loading.value)
			{
				m_digit[m_inc]->segments(m_buffer[m_inc]);
			}
			// Display ASCII characters ?
			else
			{
				m_digit[m_inc]->set(m_buffer[m_inc]);
			}
			
			// Switch digits (Only 1 turn ON)
			for(i = 0; i < m_size; i++)
			{
				// Digit to switch ON ?
				if(i == m_inc)
				{
					// Digit selected for blinking ? and blink effect activated ?
					if(((m_blink.select & (0x01 << i)) != 0) && (m_blink.flag))
					{
						m_digit[i]->off();
					}
					// Normal use
					else
					{
						m_digit[i]->on();
					}
				}
				// Switch OFF others digits
				else
				{
					m_digit[i]->off();
				}
			}
			
			m_inc = (m_inc + 1) % m_size;
		}
	}
	
	// Blink ?
	if((m_blink.timer == 0) && m_blink.value)
	{
		m_blink.timer = m_blink.value;
		
		m_blink.flag = (m_blink.flag) ? 0 : 1;
	}
	
	// Scroll ?
	if((m_scroll.timer == 0) && m_scroll.value)
	{
		m_scroll.timer = m_scroll.value;
		
		for(i = 0; i < m_size; i++)
		{			
			m_tmp[i] = m_buffer[(i+1)%m_size];
		}
		
		for(i = 0; i < m_size; i++)
		{			
			m_buffer[i] = m_tmp[i];
		}
	}
	
	// Loading ?
	if((m_loading.timer == 0) && m_loading.value)
	{
		m_loading.timer = m_loading.value;
		
		m_loading.flag = (m_loading.flag + 1) % 6;
		
		for(i = 0; i < m_size; i++)
		{
			m_buffer[i] = loadingMap[(m_loading.flag+i)%6];
		}
	}
}

void SevenSegGroup :: add(SevenSeg* digit)
{
	m_digit[m_size++] = digit;
	
	m_mux = REFRESH_TIME / m_size;
}

void SevenSegGroup :: set(char* buffer, int length)
{
	char i = 0;
	
	length = (length > m_size) ? m_size : length;
	
	for(i = 0; i < length; i++)
	{
		m_buffer[i] = buffer[i];
	}
}

void SevenSegGroup :: set(int number)
{
	char buffer[MAX_DIGITS] = {0};
	
	sprintf(buffer, "%%0%dd", m_size);
	
	sprintf(m_buffer, buffer, number);
}

void SevenSegGroup :: blink(int ms)
{
	if(m_blink.value != ms)
	{
		m_blink.select = 0xFFFF;
		
		m_blink.value = (ms <= 0) ? 0 : ms;
		m_blink.flag = 0;
		
		m_blink.timer = m_blink.value;
	}
}

void SevenSegGroup :: blink(char select, int ms)
{
	m_blink.select |= 0x01 << select;
	
	if(m_blink.value != ms)
	{		
		m_blink.value = (ms <= 0) ? 0 : ms;
		m_blink.flag = 0;
		
		m_blink.timer = m_blink.value;
	}
}

void SevenSegGroup :: scroll(int ms)
{
	if(m_scroll.value != ms)
	{
		m_scroll.value = (ms <= 0) ? 0 : ms;
		m_scroll.flag = 0;
		
		m_scroll.timer = m_scroll.value;
	}
}

void SevenSegGroup :: loading(int ms)
{
	if(m_loading.value != ms)
	{
		m_loading.value = (ms <= 0) ? 0 : ms;
		m_loading.flag = 0;
		
		m_loading.timer = m_loading.value;
	}
}

void SevenSegGroup :: clear(void)
{
	m_blink.value = 0;
	m_blink.select = 0;
	
	m_scroll.value = 0;
	m_loading.value = 0;
}

void SevenSegGroup :: timer(void)
{
	if(m_timer) m_timer--;
	
	if(m_blink.timer) m_blink.timer--;
	if(m_scroll.timer) m_scroll.timer--;
	if(m_loading.timer) m_loading.timer--;
}
