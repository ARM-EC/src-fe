#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
//#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����0


//#define KEY0_PRES 	1	//KEY0����

//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 


#define KEY1 PAin(4)
#define KEY2 PAin(5)
#define KEY3 PAin(6)

void KEY_Init(void);//IO��ʼ��
//u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
