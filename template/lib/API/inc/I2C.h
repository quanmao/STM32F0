#ifndef __I2C_H
#define __I2C_H

/* includes ---------------------------------------------------------------- */
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_i2c.h"
#include "Common.h"

/* defines ----------------------------------------------------------------- */
#define OWN_ADDRESS 			0x00
#define MAX_I2C_BUF_LEN 	64
#define I2C_TIMEOUT				0x1800	// 0x1800 / 48MHz (SystemCoreClock) = 0.12 ms

/* class ------------------------------------------------------------------- */
class I2C
{
	private:
		
		I2C_TypeDef* m_I2C;
	
		GPIO_TypeDef* m_sdaPort;
		int m_sdaPin;
		int m_sdaSource;
	
		GPIO_TypeDef* m_sclPort;
		int m_sclPin;
		int m_sclSource;
		
		char* m_buffer;
		char* m_index;
		char* m_busy;
		
	public:
		
		I2C(I2C_TypeDef* I2Cx, GPIO_common GPIO_c_sda, GPIO_common GPIO_c_scl, char address = OWN_ADDRESS);
		char read(char address, char* command, char size);
		char read_s(char* buffer);
		char write(char address, char* command, char size);
		char write_b(char address, char* command, char size);
		char busy(void);
};

#endif
