#ifndef __GPIO_H
#define __GPIO_H

/* includes ---------------------------------------------------------------- */
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_tim.h"

/* structure --------------------------------------------------------------- */
typedef struct
{
	GPIO_TypeDef* port;
	int pin;
	int pinSource;
}GPIO_common;

typedef struct
{
	TIM_TypeDef* tim;
	char channel;
	char index;
	char af;
}TIM_common;

// GPIO
extern GPIO_common PA0;
extern GPIO_common PA1;
extern GPIO_common PA2;
extern GPIO_common PA3;
extern GPIO_common PA4;
extern GPIO_common PA5;
extern GPIO_common PA6;
extern GPIO_common PA7;
extern GPIO_common PA8;
extern GPIO_common PA9;
extern GPIO_common PA10;
extern GPIO_common PA11;
extern GPIO_common PA12;
extern GPIO_common PA13;
extern GPIO_common PA14;
extern GPIO_common PA15;

extern GPIO_common PB0;
extern GPIO_common PB1;
extern GPIO_common PB2;
extern GPIO_common PB3;
extern GPIO_common PB4;
extern GPIO_common PB5;
extern GPIO_common PB6;
extern GPIO_common PB7;
extern GPIO_common PB8;
extern GPIO_common PB9;
extern GPIO_common PB10;
extern GPIO_common PB11;
extern GPIO_common PB12;
extern GPIO_common PB13;
extern GPIO_common PB14;
extern GPIO_common PB15;

extern GPIO_common PC0;
extern GPIO_common PC1;
extern GPIO_common PC2;
extern GPIO_common PC3;
extern GPIO_common PC4;
extern GPIO_common PC5;
extern GPIO_common PC6;
extern GPIO_common PC7;
extern GPIO_common PC8;
extern GPIO_common PC9;
extern GPIO_common PC10;
extern GPIO_common PC11;
extern GPIO_common PC12;
extern GPIO_common PC13;
extern GPIO_common PC14;
extern GPIO_common PC15;

extern GPIO_common PD2;

extern GPIO_common PF0;
extern GPIO_common PF1;
extern GPIO_common PF4;
extern GPIO_common PF5;
extern GPIO_common PF6;
extern GPIO_common PF7;

// TIM
extern TIM_common TIM1_CH1;
extern TIM_common TIM1_CH2;
extern TIM_common TIM1_CH3;
extern TIM_common TIM1_CH4;
extern TIM_common TIM2_CH1;
extern TIM_common TIM2_CH2;
extern TIM_common TIM2_CH3;
extern TIM_common TIM2_CH4;
extern TIM_common TIM3_CH1;
extern TIM_common TIM3_CH2;
extern TIM_common TIM3_CH3;
extern TIM_common TIM3_CH4;
extern TIM_common TIM14_CH1;
extern TIM_common TIM15_CH1;
extern TIM_common TIM15_CH2;
extern TIM_common TIM16_CH1;
extern TIM_common TIM17_CH1;

#endif
