#ifndef __LIGHT_H
#define __LIGHT_H	 
#include "stm32f10x.h"

#define LIGHT_ON GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define LIGHT_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_7)


void LIGHT_Init(void);//≥ı ºªØ

		 				    
#endif
