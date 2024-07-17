#include "stm32f10x.h"     
#include "adc.h"
#include "delay.h"
#include "serial.h"
#include "can.h"
#include "key.h"
#include "relay.h"
#include "oled.h"
#include "light.h"
#include "stmflash.h"

u8 key;	//接收数据
u8 canbuf[8];	//存储发送数据和接收数据的数组
u8 res;	//发送数据
u8 soilHum=0;	//定义湿度变量
u8 lightIntensity=0;	//定义光照强度变量


#define LEN 7
u16 eep[LEN];
#define soilHumMin eep[5]
#define soilHumMax eep[6]
#define lightMin eep[3] 
#define lightMax eep[4] 

int relay_state=0;
int light_state=0;


int a=0;
int b=1;



void SaveFLASH(void)
{
    // 保存在Flash中
    eep[0] = 0xA5; // Flash标记
    STMFLASH_Write(FLASH_SAVE_ADDR, (u16*)eep, LEN);
}

/*读取FLASH内存*/
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

void OLED_Start(void)
{
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示 
	OLED_ShowString(0,0,"soilHumMax",16,1);
	OLED_ShowChinese(82,0,0,16,1);
	OLED_ShowNum(88, 0, soilHumMax, 2, 16, 1); 
	
	OLED_ShowString(0,16,"soilHumMin",16,1);
	OLED_ShowChinese(82,16,0,16,1);
	OLED_ShowNum(88, 16, soilHumMin, 2, 16, 1); 
	
	OLED_ShowString(0,32,"lightMax",16,1);
	OLED_ShowChinese(82,32,0,16,1);
	OLED_ShowNum(88, 32, lightMax, 2, 16, 1); 
	
	OLED_ShowString(0,48,"lightMin",16,1);
	OLED_ShowChinese(82,48,0,16,1);
	OLED_ShowNum(88, 48, lightMin, 2, 16, 1); 
	OLED_Refresh();

}

/*自动模式*/
void Auto(void)
{
			if((soilHum<=soilHumMin) || (light_state==0 && lightIntensity>=lightMax))
		{
				RELAY_ON;
				relay_state=1;
				delay_ms(1000);
		}
		else if((relay_state==1 && soilHum>=soilHumMax) || (light_state==0  && lightIntensity>lightMin && lightIntensity<lightMax))
		{
				RELAY_OFF;
				relay_state=0;
		}  
		else if(lightIntensity<=lightMin)
		{
				LIGHT_ON;
				light_state=1;
				delay_ms(1000); 					
		}
		else if(light_state==1 && lightIntensity>=lightMax)
		{
				LIGHT_OFF;
				light_state=0;
		} 	
}



#define FILTER6_N 6
#define FILTER6_A 50
int filter_buf[FILTER6_N];

// 全局变量，用于存储最近的原始输入信号
int last_raw_input;

// 初始化函数，用于设置初始值
void init()
{
    last_raw_input = 0;
}

// 计算信噪比的函数
float calculate_SNR(int filtered_output)
{
    // 计算信号的能量，即滤波后的输出信号的功率
    float signal_energy = filtered_output * filtered_output;

    // 计算噪声的能量，即滤波器输入信号与原始输入信号之差的平方的均值
    float noise_energy = 0;
    for (int i = 0; i < FILTER6_N; i++) 
    {
        int diff = filter_buf[i] - last_raw_input;
        noise_energy += diff * diff;
    }
    noise_energy /= FILTER6_N;

    // 计算信噪比
    float SNR = signal_energy / noise_energy;

    return SNR;
}

int filter6(int value) 
{
  static int a = 0;
  int i;
  int filter_sum = 0;
  filter_buf[FILTER6_N - 1] = value; // 将获取的数据存入滤波器数组
  a++;
  if (a == 255) a = 0; // 重置a，避免溢出
  if (((filter_buf[FILTER6_N - 1] - filter_buf[FILTER6_N - 2]) > FILTER6_A) || ((filter_buf[FILTER6_N - 2] - filter_buf[FILTER6_N - 1]) > FILTER6_A))
    filter_buf[FILTER6_N - 1] = filter_buf[FILTER6_N - 2]; // 如果当前值与上一个值之差超过阈值，则舍弃当前值
  for (i = 0; i < FILTER6_N - 1; i++) 
  {
    filter_buf[i] = filter_buf[i + 1]; // 移动滤波器数组
    filter_sum += filter_buf[i]; // 计算滤波后的数据总和
  }
	
	// 调用计算信噪比的函数
    float SNR = calculate_SNR(filter_sum / (FILTER6_N - 1));
  	Serial_Printf("\r\n%d",SNR);
    // 更新原始输入信号
    last_raw_input = value;
  return filter_sum / (FILTER6_N - 1); // 返回滤波后的平均值
}

void pros6(void)
{
  int filtered_soilHum = filter6(100 - (AD_GetValue(ADC_Channel_0) / 40.95f)); // 对土壤湿度进行滤波处理
  // 打印滤波后的数据
	Serial_Printf("\r\nlater%d",filtered_soilHum);
}


int main(void)
{
/***********************CAN通信********************/	
    delay_ms(1000);
    AD_Init();                 //AD通道初始化 
	  Serial_Init();
//		OLED_Init();
//		OLED_ColorTurn(0);//0正常显示，1 反色显示
//		OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示 
//		RELAY_Init();
//	  LIGHT_Init();
//		RELAY_OFF;
//	  ReadFLASH();
//		OLED_Start();
//	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
//    CAN_Mode_Init(CAN_SJW_1tq, CAN_BS2_8tq, CAN_BS1_9tq, 4, CAN_Mode_Normal); //CAN初始化正常模式，波特率500Kbps
    while (1)
		{
				soilHum = 100 - (AD_GetValue(ADC_Channel_0) / 40.95f); // 获取土壤湿度
//				lightIntensity=(100/3.3)*(3.3-AD_GetValue(ADC_Channel_1)*(3.3/4095));
			   	Serial_Printf("\r\nfront%d",soilHum);
					delay_ms(500);
					pros6();	
					delay_ms(20);
//				canbuf [0] = soilHum; // 填充发送缓冲区
//				canbuf [1]=lightIntensity;
//				
//				res = Can_Send_Msg(canbuf, 2); // 发送2个字节的数据
//				delay_ms(1000); // 等待一定时间再发送下一个数据
									
//				key = Can_Receive_Msg(canbuf);
//				if (key) // 接收到有数据
//				{		
//					/*接收湿度上限设定*/
//						if(canbuf[1]=='s' && canbuf[2]=='a' && canbuf[3]=='x')
//						{
//								soilHumMax=canbuf[0];
//								SaveFLASH();
//								OLED_ClearPlace(88,0,20,20);
//								OLED_ShowNum(88, 0, soilHumMax, 2, 16, 1); 
//								OLED_Refresh();
//							  Auto();
//						}
//					/*接收湿度下限设定*/
//						else if(canbuf[1]=='s' && canbuf[2]=='i' && canbuf[3]=='n')
//						{
//								soilHumMin=canbuf[0];
//								SaveFLASH();
//								OLED_ClearPlace(88,16,20,20);
//								OLED_ShowNum(88, 16, soilHumMin, 2, 16, 1); 
//								OLED_Refresh();
//							  Auto();
//						}
//					/*接收光照强度上限设定*/
//						else if(canbuf[1]=='l' && canbuf[2]=='a' && canbuf[3]=='x')
//						{
//								lightMax=canbuf[0];
//								SaveFLASH();
//								OLED_ClearPlace(88,32,20,20);
//								OLED_ShowNum(88, 32, lightMax, 2, 16, 1); 
//								OLED_Refresh();
//							  Auto();
//						}
//					/*接收光照强度下限设定*/
//						else if(canbuf[1]=='l' && canbuf[2]=='i' && canbuf[3]=='n')
//						{
//								lightMin=canbuf[0];
//								SaveFLASH();
//								OLED_ClearPlace(88,48,20,20);
//								OLED_ShowNum(88, 48, lightMin, 2, 16, 1); 
//								OLED_Refresh();
//							  Auto();
//						}
//						else if(canbuf[0]==01)
//						{
//							RELAY_ON;
//						}
//						else if(canbuf[0]==00)
//						{
//							RELAY_OFF;
//						}
//						else if(canbuf[0]==11)
//						{
//							LIGHT_ON;
//						}
//						else if(canbuf[0]==10)
//						{
//							LIGHT_OFF;
//						}						
//				}
//				else
//				{
//					Auto();
//				}
				
					
		}	
}

