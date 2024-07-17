#include "stm32f10x.h"
#include "oled.h"
#include "delay.h"
#include "can.h"
#include "key.h"
#include "menu.h"
#include "stmflash.h"

u8 key;
u8 canbuf[8];	//存储接收数据数组
u8 res=0;
u8 i=0;
u8 water_on=01;
u8 water_off=00;
u8 light_on=11;
u8 light_off=10;

void (*current_operation_index)();
uchar func_index = 0; //初始显示欢迎界面
uchar last_index = 127; //last初始为无效值

#define LEN 7
u16 eep[LEN];
#define soilHumMin eep[5]
#define soilHumMax eep[6]
#define lightMin eep[3] 
#define lightMax eep[4] 

int auto_state=0;
void SaveFLASH(void)
{
    // 保存在Flash中
    eep[0] = 0xA5; // Flash标记
    STMFLASH_Write(FLASH_SAVE_ADDR, (u16*)eep, LEN);
}

void ReadFLASH(void)
{
    STMFLASH_Read(FLASH_SAVE_ADDR, (u16*)eep, LEN);
    if(eep[0] != 0xA5)
    {
        soilHumMin = 0;
        soilHumMax = 90;
				lightMin=40;
				lightMax=80;
    }
}


//界面执行函数
void Execute(void)
{
		if (func_index != last_index)
		{	
			current_operation_index = table[func_index].current_operation;			
			OLED_Clear(); 
			(*current_operation_index)();//执行当前操作函数
			OLED_Refresh();					
			last_index = func_index;		
		}
	}

int main(void)
{	    		  
	KEY_Init();		  	
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	ReadFLASH();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	CAN_Mode_Init(CAN_SJW_1tq, CAN_BS2_8tq, CAN_BS1_9tq, 4, CAN_Mode_Normal); //CAN初始化正常模式，波特率500Kbps
	while(1)
	{		
					switch(func_index)
					{
						case 22:
						{
							canbuf[0]=water_on;
							res = Can_Send_Msg(canbuf, 1); 									
							break;
						}	
						case 23:
						{
							canbuf[0]=water_off;
							res = Can_Send_Msg(canbuf, 1); 									
							break;
						}
						case 24:
						{
							canbuf[0]=light_on;
							res = Can_Send_Msg(canbuf, 1); 									
							break;
						}
						case 25:
						{
							canbuf[0]=light_off;
							res = Can_Send_Msg(canbuf, 1); 									
							break;
						}

		/*湿度上限设定*/
						case 26:
								OLED_ShowNum(60, 22, soilHumMax, 2, 16, 1); 
								OLED_Refresh();
								if(KEY1==0)
								{
										delay_ms(10);
										OLED_ClearPlace(60,22,20,20);
										soilHumMax = (soilHumMax + 1) % 101;
										OLED_ShowNum(60, 22, soilHumMax, 2, 16, 1);
										OLED_Refresh();
										while(!KEY1);
								}
								else if(KEY2==0)
								{
										delay_ms(10);
										OLED_ClearPlace(60,22,20,20);
										soilHumMax = (soilHumMax - 1 + 101) % 101;
										OLED_ShowNum(60, 22, soilHumMax, 2, 16, 1);
										OLED_Refresh();
										while(!KEY2);
								}
								else if(KEY3==0)
								{
										soilHumMax = soilHumMax; 
									  SaveFLASH();
										canbuf [0] = soilHumMax; 
										canbuf[1] = 's';
										canbuf[2] = 'a';
										canbuf[3] = 'x';
										res = Can_Send_Msg(canbuf, 4); 									
										func_index = table[func_index].enter;    //确认
									  while(!KEY3);
										Execute();
									  auto_state=1;
								}
								break;
						
		/*湿度下限设定*/
						case 27:
								OLED_ShowNum(60, 22, soilHumMin, 2, 16, 1); 
								OLED_Refresh();
								if(KEY1==0)
								{
										delay_ms(10);
										OLED_ClearPlace(60,22,20,20);
										soilHumMin = (soilHumMin + 1) % 101;
										OLED_ShowNum(60, 22, soilHumMin, 2, 16, 1);
										OLED_Refresh();
										while(!KEY1);
								}
								else if(KEY2==0)
								{
										delay_ms(10);
										OLED_ClearPlace(60,22,20,20);
										soilHumMin = (soilHumMin - 1 + 101) % 101;
										OLED_ShowNum(60, 22, soilHumMin, 2, 16, 1);
										OLED_Refresh();
										while(!KEY2);
								}
								else if(KEY3==0)
								{
										soilHumMin = soilHumMin; 
									  SaveFLASH();
										canbuf [0] = soilHumMin; 
										canbuf[1] = 's';
										canbuf[2] = 'i';
										canbuf[3] = 'n';
										res = Can_Send_Msg(canbuf, 4); 										
										func_index = table[func_index].enter;    //确认
									  while(!KEY3);
										Execute();
									  auto_state=1;
								}
								break;
						
		/*光照强度上限设定*/
						case 28:
								OLED_ShowNum(60, 22, lightMax, 2, 16, 1); 
								OLED_Refresh();
								if(KEY1==0)
								{
										delay_ms(10);
										OLED_ClearPlace(60,22,20,20);
										lightMax = (lightMax + 1) % 101;
										OLED_ShowNum(60, 22, lightMax, 2, 16, 1);
										OLED_Refresh();
										while(!KEY1);
								}
								else if(KEY2==0)
								{
										delay_ms(10);
										OLED_ClearPlace(60,22,20,20);
										lightMax = (lightMax - 1 + 101) % 101;
										OLED_ShowNum(60, 22, lightMax, 2, 16, 1);
										OLED_Refresh();
										while(!KEY2);
								}
								else if(KEY3==0)
								{
										lightMax = lightMax; 
									  SaveFLASH();
										canbuf [0] = lightMax; 
										canbuf[1] = 'l';
										canbuf[2] = 'a';
										canbuf[3] = 'x';
										res = Can_Send_Msg(canbuf, 4); 									
										func_index = table[func_index].enter;    //确认
									  while(!KEY3);
										Execute();
									  auto_state=1;
								}
								break;
							
		/*光照强度下限设定*/
						case 29:
								OLED_ShowNum(60, 22, lightMin, 2, 16, 1); 
								OLED_Refresh();
								if(KEY1==0)
								{
										delay_ms(10);
										OLED_ClearPlace(60,22,20,20);
										lightMin = (lightMin + 1) % 101;
										OLED_ShowNum(60, 22, lightMin, 2, 16, 1);
										OLED_Refresh();
										while(!KEY1);
								}
								else if(KEY2==0)
								{
										delay_ms(10);
										OLED_ClearPlace(60,22,20,20);
										lightMin = (lightMin - 1 + 101) % 101;
										OLED_ShowNum(60, 22, lightMin, 2, 16, 1);
										OLED_Refresh();
										while(!KEY2);
								}
								else if(KEY3==0)
								{
										lightMin = lightMin; 
									  SaveFLASH();
										canbuf [0] = lightMin; 
										canbuf[1] = 'l';
										canbuf[2] = 'i';
										canbuf[3] = 'n';
										res = Can_Send_Msg(canbuf, 4); 									
										func_index = table[func_index].enter;    //确认
									  while(!KEY3);
										Execute();
									  auto_state=1;
								}
								break;
						default:
							  break;
					}
						key = Can_Receive_Msg(canbuf);
						if ((func_index == 0) &&(key !=0))
						{
								OLED_ShowNum(60, 22, canbuf[0], 2, 16, 1); // 显示数据
								OLED_ShowNum(80, 43, canbuf[1], 2, 16, 1);	
								OLED_Refresh();
								delay_ms(1000);
						}
							if((KEY1==0)||(KEY2==0)||(KEY3==0))
							{
								delay_ms(10);//消抖
								if(KEY1==0)
								{
									func_index = table[func_index].up;    //向上翻
									while(!KEY1);//松手检测
								}
								if(KEY2==0)
								{
									func_index = table[func_index].down;    //向下翻
									while(!KEY2);
								}
								if(KEY3==0)
								{
									func_index = table[func_index].enter;    //确认
									while(!KEY3);
								}
							}	
							Execute();
   }
}





