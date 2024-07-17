#ifndef __RELAY_H
#define __RELAY_H	 
#include "stm32f10x.h"

#define RELAY_ON GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define RELAY_OFF GPIO_SetBits(GPIOB,GPIO_Pin_6)


void RELAY_Init(void);//≥ı ºªØ

		 				    
#endif
