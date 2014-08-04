/*!
 * \file I2C.cpp
 * \brief I2C API.
 * \author Rémi.Debord
 * \version 1.0
 * \date 19 novembre 2013
 *
 * I2C library (400kHz).
 *
 */

#include "I2C.h"

char I2C1_buffer[MAX_I2C_BUF_LEN];
char I2C1_busy;
char I2C1_index;

char I2C2_buffer[MAX_I2C_BUF_LEN];
char I2C2_busy;
char I2C2_index;

/*!
 *  \brief Constructor
 *
 *  I2C constructor.
 *
 *  \param I2Cx : I2C number (I2C1 or I2C2)
 *  \param GPIO_c_sda : data pin
 *  \param GPIO_c_scl : clock pin
 *
 */

I2C :: I2C(I2C_TypeDef* I2Cx, GPIO_common GPIO_c_sda, GPIO_common GPIO_c_scl)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;
	
	m_I2C = I2Cx;
	
	m_sdaPort = GPIO_c_sda.port;
	m_sdaPin = GPIO_c_sda.pin;
	m_sdaSource = GPIO_c_sda.pinSource;
	
	m_sclPort = GPIO_c_scl.port;
	m_sclPin = GPIO_c_scl.pin;
	m_sclSource = GPIO_c_scl.pinSource;
	
	if(m_I2C == I2C1)
	{
		m_buffer = I2C1_buffer;
		m_busy = &I2C1_busy;
		m_index = &I2C1_index;
	}
	else if(m_I2C == I2C2)
	{
		m_buffer = I2C2_buffer;
		m_busy = &I2C2_busy;
		m_index = &I2C2_index;
	}
	
	*m_busy = 0;
	*m_index = 0;

	/* SDA/SCL GPIO clock enable */
  if(m_sdaPort == GPIOA) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	else if(m_sdaPort == GPIOB) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	else if(m_sdaPort == GPIOC) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	else if(m_sdaPort == GPIOD) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	else if(m_sdaPort == GPIOF) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	
	if(m_sclPort == GPIOA) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	else if(m_sclPort == GPIOB) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	else if(m_sclPort == GPIOC) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	else if(m_sclPort == GPIOD) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	else if(m_sclPort == GPIOF) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	
	/* Connect pins to I2Cx Alternate Function mapping */
	GPIO_PinAFConfig(m_sdaPort, m_sdaSource, GPIO_AF_1);
	GPIO_PinAFConfig(m_sclPort, m_sclSource, GPIO_AF_1);

	/* GPIO Configuration SDA and SCL */
  GPIO_InitStructure.GPIO_Pin = m_sdaPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(m_sdaPort, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = m_sclPin;
  GPIO_Init(m_sclPort, &GPIO_InitStructure);
	
	/* Enable I2C interrupt */
	if(m_I2C == I2C1) NVIC_InitStructure.NVIC_IRQChannel = I2C1_IRQn;
	else if(m_I2C == I2C2) NVIC_InitStructure.NVIC_IRQChannel = I2C2_IRQn;
	
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  /* I2C Peripheral clock enable */
  if(m_I2C == I2C1) RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	else if(m_I2C == I2C2) RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	
	/* Configure the I2C clock source */
  if(m_I2C == I2C1) RCC_I2CCLKConfig(RCC_I2C1CLK_HSI);
	
	/* I2C De-initialize (!important) */
  I2C_DeInit(m_I2C);
	
  /* I2C configuration */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;					/* I2C mode (I2C, SMBus, ...) */
	I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  I2C_InitStructure.I2C_DigitalFilter = 0x00;
	I2C_InitStructure.I2C_OwnAddress1 = OWN_ADDRESS;		/* Own address */
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;					/* Acknowledge enable */
	
	if(m_I2C == I2C1) I2C_InitStructure.I2C_Timing = 0x0030020B; 					// Speed !!! 400KHz | 8MHz (HSI) => 0x0030020A
  else if(m_I2C == I2C2) I2C_InitStructure.I2C_Timing =  0x10950C27;		// Speed !!! 400KHz | 48MHz (PCCLK => HSE) => 0x10950C27
	
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	/* 7-bit address is acknowledged */

  /* I2C Initialization */
  I2C_Init(m_I2C, &I2C_InitStructure);

	/* IRQ configuration */	
	I2C_ITConfig(m_I2C, I2C_IT_TXI, ENABLE);
	I2C_ITConfig(m_I2C, I2C_IT_TC, ENABLE);
	I2C_ITConfig(m_I2C, I2C_IT_RXNE, ENABLE);
	I2C_ITConfig(m_I2C, I2C_IT_NACKF, ENABLE);
	I2C_ITConfig(m_I2C, I2C_IT_STOPF, ENABLE);
	
  /* I2C ENABLE */
  I2C_Cmd(m_I2C, ENABLE);
}

/*!
 *  \brief I2C Read (non blocking call)
 *
 *  Read (non blocking).
 *
 *  \param address : device address
 *  \param command : command byte(s)
 *  \param size : number of command byte 
 *
 *  \return SUCCESS or ERROR
 */

char I2C :: read(char address, char* command, char size)
{
	char result = SUCCESS;
	int timeout = size * I2C_TIMEOUT;
	char i;
	
	/* Periheral busy ? */
	if(I2C_GetFlagStatus(m_I2C, I2C_FLAG_BUSY) || *m_busy)
	{
		return ERROR;
	}
	
	*m_index = 0;
	*m_busy = 1;
	
	/* Send first Start and control byte (slave address + R/W) */
	I2C_TransferHandling(m_I2C, address, size, I2C_SoftEnd_Mode, I2C_Generate_Start_Read);	
	
	while(*m_index != size)
	{
		if((timeout--) == 0)
		{
			*m_busy = 0;
			return ERROR;
		}
	}
	
	*m_busy = 0;
	
	/* Copy data */
	for(i = 0; i < size; i++, command++)
	{
		*command = *(m_buffer + i);
	}
	
	return result;
}

/*!
 *  \brief I2C Write (non blocking call)
 *
 *  Write data to i2c peripheral (non blocking).
 *
 *  \param address : device address
 *  \param command : command byte(s)
 *  \param size : number of command byte 
 *
 *  \return SUCCESS or ERROR
 */

char I2C :: write(char address, char* command, char size)
{
	char result = SUCCESS;
	char i = 0;
	
	/* Periheral busy ? */
	if(I2C_GetFlagStatus(m_I2C, I2C_FLAG_BUSY) || *m_busy)
	{
		return ERROR;
	}
	
	*m_index = 0;
	*m_busy = 1;
	
	/* Copy data to i2c buffer */
	for(i = 0; i < size; i++, command++)
	{
		*(m_buffer + i) = *command;
	}
	
	/* Send first Start and control byte (slave address + R/W) */
	I2C_TransferHandling(m_I2C, address, size, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
	
	return result;
}

/*!
 *  \brief I2C Write (blocking call)
 *
 *  Write data (blocking).
 *
 *  \param address : device address
 *  \param command : command byte(s)
 *  \param size : number of command byte 
 *
 *  \return SUCCESS or ERROR
 */
 
char I2C :: write_b(char address, char* command, char size)
{
	char result = SUCCESS;
	char i = 0;
	
	/* Periheral busy ? */
	if(I2C_GetFlagStatus(m_I2C, I2C_FLAG_BUSY) || *m_busy)
	{
		return ERROR;
	}
	
	*m_index = 0;
	*m_busy = 1;
	
	/* Copy data to i2c buffer */
	for(i = 0; i < size; i++, command++)
	{
		*(m_buffer + i) = *command;
	}
	
	/* Send first Start and control byte (slave address + R/W) */
	I2C_TransferHandling(m_I2C, address, size, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
	
	while(*m_busy);
	
	return result;
}

/*!
 *  \brief I2C IRQ handler
 */

extern "C"
{
	void I2C1_IRQHandler(void)
	{
		/* Transmit complete */
		if(I2C_GetITStatus(I2C1, I2C_IT_TC))
		{
			I2C_GenerateSTOP(I2C1, ENABLE);		
		}
		
		/* Transmit buffer interrupt status */
		if(I2C_GetITStatus(I2C1, I2C_IT_TXIS))
		{
			I2C_SendData(I2C1, (uint8_t) I2C1_buffer[I2C1_index]);
			I2C1_index++;
		}
		
		/* Receive buffer interrupt status */
		if(I2C_GetITStatus(I2C1, I2C_IT_RXNE))
		{			
			I2C1_buffer[I2C1_index] = I2C_ReceiveData(I2C1);
			I2C1_index++;
		}
		
		/* Clear NACK error */
		if(I2C_GetITStatus(I2C1, I2C_IT_NACKF))
		{
			I2C_ClearITPendingBit(I2C1, I2C_IT_NACKF);
			I2C1_busy = 0;
		}
		
		/* Stop generation end */
		if(I2C_GetITStatus(I2C1, I2C_IT_STOPF))
		{
			I2C_ClearITPendingBit(I2C1, I2C_IT_STOPF);
			I2C_GenerateSTOP(I2C1, DISABLE);
			I2C1_busy = 0;	
		}
	}
	
	void I2C2_IRQHandler(void)
	{
		/* Transmit complete */
		if(I2C_GetITStatus(I2C2, I2C_IT_TC))
		{
			I2C_GenerateSTOP(I2C2, ENABLE);		
		}
		
		/* Transmit buffer interrupt status */
		if(I2C_GetITStatus(I2C2, I2C_IT_TXIS))
		{
			I2C_SendData(I2C2, (uint8_t) I2C2_buffer[I2C2_index]);
			I2C2_index++;
		}
		
		/* Receive buffer interrupt status */
		if(I2C_GetITStatus(I2C2, I2C_IT_RXNE))
		{			
			I2C2_buffer[I2C2_index] = I2C_ReceiveData(I2C2);
			I2C2_index++;
		}
		
		/* Clear NACK error */
		if(I2C_GetITStatus(I2C2, I2C_IT_NACKF))
		{
			I2C_ClearITPendingBit(I2C2, I2C_IT_NACKF);
			I2C2_busy = 0;
		}
		
		/* Stop generation end */
		if(I2C_GetITStatus(I2C2, I2C_IT_STOPF))
		{
			I2C_ClearITPendingBit(I2C2, I2C_IT_STOPF);
			I2C_GenerateSTOP(I2C2, DISABLE);
			I2C2_busy = 0;	
		}
	}
}
