#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
//#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//读取按键0


//#define KEY0_PRES 	1	//KEY0按下

//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 


#define KEY1 PAin(4)
#define KEY2 PAin(5)
#define KEY3 PAin(6)

void KEY_Init(void);//IO初始化
//u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
