/*!
 * \file Digital.cpp
 * \brief Digital API.
 * \author Rémi.Debord
 * \version 1.1
 * \date 19 novembre 2013
 *
 * Digital library (DigitalIn, DigitalOut and InterruptIn).
 *
 */

#include "Digital.h"

extern "C"
{
	char externalInterruptAttach[16];
	void (*ExternalInterruptPin[16])(void);
}

/*!
 *  \brief Constructor
 *
 *  DigitalIn constructor.
 *
 *  \param GPIO_c : GPIO pin
 *
 */

DigitalIn :: DigitalIn(GPIO_common GPIO_c)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	m_port = GPIO_c.port;
	m_pin = GPIO_c.pin;
	m_value = 0;
	
  /* GPIOx Periph clock enable */
	if(m_port == GPIOA) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	else if(m_port == GPIOB) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	else if(m_port == GPIOC) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	else if(m_port == GPIOD) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	else if(m_port == GPIOF) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	
  /* Configure "pin" in input mode */
  GPIO_InitStructure.GPIO_Pin = m_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	//GPIO_PuPd_NOPULL;
  GPIO_Init(m_port, &GPIO_InitStructure);
}

/*!
 *  \brief Change input mode
 *
 *  Modify input mode (no pull, pull up, ...).
 *
 *  \param pull : pull mode
 *
 */

void DigitalIn :: mode(GPIOPuPd_TypeDef pull)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Configure "pin" in input mode */
  GPIO_InitStructure.GPIO_Pin = m_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_PuPd = pull;
  GPIO_Init(m_port, &GPIO_InitStructure);
}

/*!
 *  \brief DigitalIn read
 *
 *  Read GPIO state (0 or 1).
 *
 *  \return 0 or 1
 *
 */

int DigitalIn :: read()
{
	if((GPIO_ReadInputDataBit(m_port, m_pin)) != 0) m_value = 1;
	else m_value = 0;
	
	return m_value;
}

/*!
 *  \brief DigitalIn read (shorthand)
 *
 *  Read GPIO state (0 or 1).
 *
 *  \return 0 or 1
 *
 */

DigitalIn :: operator int()
{
	if((GPIO_ReadInputDataBit(m_port, m_pin)) != 0) m_value = 1;
	else m_value = 0;
	
	return m_value;
}

/*!
 *  \brief Constructor
 *
 *  DigitalOut constructor.
 *
 *  \param GPIO_c : GPIO pin
 *
 */

DigitalOut :: DigitalOut(GPIO_common GPIO_c)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	m_port = GPIO_c.port;
	m_pin = GPIO_c.pin;
	m_value = 0;
	
  /* GPIOx Periph clock enable */
	if(m_port == GPIOA) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	else if(m_port == GPIOB) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	else if(m_port == GPIOC) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	else if(m_port == GPIOD) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	else if(m_port == GPIOF) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	
  /* Configure "pin" in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = m_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(m_port, &GPIO_InitStructure);
}

/*!
 *  \brief Constructor
 *
 *  DigitalOut constructor.
 *
 *  \param GPIO_c : GPIO pin
 *	\param type: Push pull or Open drain
 *
 */

DigitalOut :: DigitalOut(GPIO_common GPIO_c, GPIOOType_TypeDef type)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	m_port = GPIO_c.port;
	m_pin = GPIO_c.pin;
	m_value = 0;
	
  /* GPIOx Periph clock enable */
	if(m_port == GPIOA) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	else if(m_port == GPIOB) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	else if(m_port == GPIOC) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	else if(m_port == GPIOD) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	else if(m_port == GPIOF) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	
  /* Configure "pin" in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = m_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_OType = type;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(m_port, &GPIO_InitStructure);
}

/*!
 *  \brief DigitalOut write
 *
 *  Write GPIO new state (0 or 1).
 *
 *  \param n : GPIO state
 *
 */

void DigitalOut :: write(int n)
{
	if(n == 0) m_port->BRR = m_pin;
	else m_port->BSRR = m_pin;	
}

/*!
 *  \brief DigitalOut read
 *
 *  Read GPIO state (0 or 1).
 *
 *  \return 0 or 1
 *
 */

int DigitalOut :: read()
{
	if((m_port->ODR & m_pin) != 0) return 1;
	return 0;
}

/*!
 *  \brief DigitalOut write (shorthand)
 *
 *  Write GPIO new state (0 or 1).
 *
 */

DigitalOut& DigitalOut ::  operator= (int n)
{
	this->write(n);
	return *this;
}

/*!
 *  \brief DigitalOut read (shorthand)
 *
 *  Read GPIO state (0 or 1).
 *
 *  \return 0 or 1
 *
 */

DigitalOut :: operator int()
{
	return this->read();
}

/*!
 *  \brief Constructor
 *
 *  InterruptIn constructor.
 *
 *  \param GPIO_c : GPIO pin
 *
 */

InterruptIn :: InterruptIn(GPIO_common GPIO_c)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
	
	m_port = GPIO_c.port;
	m_pin = GPIO_c.pin;
	m_pinSource = GPIO_c.pinSource;
	
	if((m_pinSource >= GPIO_PinSource0) && (m_pinSource <= GPIO_PinSource1)) m_irqVector = EXTI0_1_IRQn;
	else if((m_pinSource >= GPIO_PinSource2) && (m_pinSource <= GPIO_PinSource3)) m_irqVector = EXTI2_3_IRQn;
	else if((m_pinSource >= GPIO_PinSource4) && (m_pinSource <= GPIO_PinSource15)) m_irqVector = EXTI4_15_IRQn;

  /* Enable GPIOx clock */
	if(m_port == GPIOA) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	else if(m_port == GPIOB) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	else if(m_port == GPIOC) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	else if(m_port == GPIOD) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	else if(m_port == GPIOF) RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
  
	/* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure "pin" as input floating */
  GPIO_InitStructure.GPIO_Pin = m_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(m_port, &GPIO_InitStructure);

  /* Connect EXTI Line to "pin" */
	if(m_port == GPIOA) SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, m_pinSource);
	else if(m_port == GPIOB) SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, m_pinSource);
	else if(m_port == GPIOC) SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, m_pinSource);
	else if(m_port == GPIOD) SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, m_pinSource);
	
  /* Configure EXTI "pin" */
  EXTI_InitStructure.EXTI_Line = (uint32_t) m_pin;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI "pin" Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = m_irqVector;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*!
 *  \brief Set callback function on a rising edge
 *
 *  Associate rising edge to callback function.
 *
 *  \param void(*f)(void) : function address
 *
 */

void InterruptIn :: rise(void(*f)(void))
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	/* Attribute function adress to the function pointer */
	ExternalInterruptPin[m_pinSource] = f;
	externalInterruptAttach[m_pinSource] = 1;
	
	/* Configure EXTI "pin" */
  EXTI_InitStructure.EXTI_Line = (uint32_t) m_pin;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/*!
 *  \brief Set callback function on a falling edge
 *
 *  Associate falling edge to callback function.
 *
 *  \param void(*f)(void) : function address
 *
 */

void InterruptIn :: fall(void(*f)(void))
{	
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	/* Attribute function adress to the function pointer */
	ExternalInterruptPin[m_pinSource] = f;
	externalInterruptAttach[m_pinSource] = 1;
	
	/* Configure EXTI "pin" */
  EXTI_InitStructure.EXTI_Line = (uint32_t) m_pin;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/*!
 *  \brief Change input mode
 *
 *  Modify input mode (no pull, pull up, ...).
 *
 *  \param pull : pull mode
 *
 */

void InterruptIn :: mode(GPIOPuPd_TypeDef pull)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Configure "pin" in input mode */
  GPIO_InitStructure.GPIO_Pin = m_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_PuPd = pull;
  GPIO_Init(m_port, &GPIO_InitStructure);
}

/*!
 *  \brief External interrupt IRQ handler
 */

extern "C"
{
	void EXTI0_1_IRQHandler(void)
	{
		if(EXTI_GetITStatus(EXTI_Line0) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[0])(*ExternalInterruptPin[0])();
			
			/* Clear the EXTI line 0 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line0);
		}
		
		if(EXTI_GetITStatus(EXTI_Line1) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[1])(*ExternalInterruptPin[1])();
			
			/* Clear the EXTI line 1 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line1);
		}
	}
	
	void EXTI2_3_IRQHandler(void)
	{
		if(EXTI_GetITStatus(EXTI_Line2) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[2])(*ExternalInterruptPin[2])();
			
			/* Clear the EXTI line 2 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line2);
		}
		
		if(EXTI_GetITStatus(EXTI_Line3) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[3])(*ExternalInterruptPin[3])();
			
			/* Clear the EXTI line 3 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line3);
		}
	}
	
	void EXTI4_15_IRQHandler(void)
	{
		if(EXTI_GetITStatus(EXTI_Line4) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[4])(*ExternalInterruptPin[4])();
			
			/* Clear the EXTI line 4 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line4);
		}
		
		if(EXTI_GetITStatus(EXTI_Line5) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[5])(*ExternalInterruptPin[5])();
			
			/* Clear the EXTI line 5 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line5);
		}
		
		if(EXTI_GetITStatus(EXTI_Line6) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[6])(*ExternalInterruptPin[6])();
			
			/* Clear the EXTI line 6 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line6);
		}
		
		if(EXTI_GetITStatus(EXTI_Line7) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[7])(*ExternalInterruptPin[7])();
			
			/* Clear the EXTI line 7 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line7);
		}

		if(EXTI_GetITStatus(EXTI_Line8) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[8])(*ExternalInterruptPin[8])();
			
			/* Clear the EXTI line 8 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line8);
		}
		
		if(EXTI_GetITStatus(EXTI_Line9) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[9])(*ExternalInterruptPin[9])();
			
			/* Clear the EXTI line 9 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line9);
		}

		if(EXTI_GetITStatus(EXTI_Line10) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[10])(*ExternalInterruptPin[10])();
			
			/* Clear the EXTI line 10 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line10);
		}
		
		if(EXTI_GetITStatus(EXTI_Line11) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[11])(*ExternalInterruptPin[11])();
			
			/* Clear the EXTI line 11 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line11);
		}

		if(EXTI_GetITStatus(EXTI_Line12) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[12])(*ExternalInterruptPin[12])();
			
			/* Clear the EXTI line 12 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line12);
		}

		if(EXTI_GetITStatus(EXTI_Line13) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[13])(*ExternalInterruptPin[13])();
			
			/* Clear the EXTI line 13 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line13);
		}
		
		if(EXTI_GetITStatus(EXTI_Line14) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[14])(*ExternalInterruptPin[14])();
			
			/* Clear the EXTI line 14 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line14);
		}

		if(EXTI_GetITStatus(EXTI_Line15) != RESET)
		{
			/* Call function */
			if(externalInterruptAttach[15])(*ExternalInterruptPin[15])();
			
			/* Clear the EXTI line 15 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line15);
		}
	}
}
