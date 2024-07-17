#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f10x.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
//STM32F103C8T6
#define STM32_FLASH_SIZE 	32  //所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 	1   //使能FLASH写入(0-不使能; 1-使能)


#define STM32_FLASH_BASE   0x08000000
#define FLASH_SAVE_ADDR   (STM32_FLASH_BASE + (STM32_FLASH_SIZE-1) * 1024)



//FLASH解锁键值
#define FLASH_KEY1               0X45670123
#define FLASH_KEY2               0XCDEF89AB

void STMFLASH_Unlock(void);					  //FLASH解锁
void STMFLASH_Lock(void);					  //FLASH上锁
u8 STMFLASH_GetStatus(void);				  //获得状态
u8 STMFLASH_WaitDone(u16 time);				  //等待操作结束
u8 STMFLASH_ErasePage(u32 paddr);			  //擦除页
u8 STMFLASH_WriteHalfWord(u32 faddr, u16 dat);//写入半字
u16 STMFLASH_ReadHalfWord(u32 faddr);		  //读出半字  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//指定地址开始写入指定长度的数据
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//指定地址开始读取指定长度数据
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//从指定地址开始读出指定长度的数据

//用户程序
//0-读取成功；1-失败
u8 Flash_Read(u16 *WriteData,u16 _len);
void Flash_Write(u16 *WriteData,u16 _len);
#endif

















