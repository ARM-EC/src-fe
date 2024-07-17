#include "menu.h"
#include "oled.h"
#include "bmp.h"

key_table table[30]=
{
	//第0层
	{0,0,0,1,(*fun_0)},
	
    //第1层
	{1,3,2, 4,(*fun_a1)},	//手动
	{2,1,3, 7,(*fun_b1)},	//自动
	{3,2,1,0,(*fun_c1)},	//返回
	
    //第2层
	{4,6,5,10,(*fun_a21)},	//水泵				
	{5,4,6,13,(*fun_a22)},	//生长灯
	{6,5,4,1,(*fun_a23)},	//返回	                	
	
	{7,9,8,16,(*fun_b21)},	//湿度
	{8,7,9,19,(*fun_b22)},	//光照强度
	{9,8,7,2,(*fun_b23)},	//返回
	
    //第3层
	{10,12,11,22,(*fun_a31)}, //开		                	
	{11,10,12,23,(*fun_a32)}, //关               	
	{12,11,10,4,(*fun_a33)},	//返回

	{13,15,14,24,(*fun_b31)},	//开		                	
	{14,13,15,25,(*fun_b32)},	//关	                	
	{15,14,13,5,(*fun_b33)},  //返回
	
	{16,18,17,26,(*fun_c31)},	//上限		                	
	{17,16,18,27,(*fun_c32)},	//下限                	
	{18,17,16,7,(*fun_c33)},  //返回
	
	{19,21,20,28,(*fun_d31)},	//上限		                	
	{20,19,21,29,(*fun_d32)},	//下限                	
	{21,20,19,8,(*fun_d33)},  //返回

		//第4层
	{22,25,23,10,(*fun_a41)},	//开水
	{23,22,24,11,(*fun_a42)},	//关水
	{24,23,25,13,(*fun_b41)},	//开灯
	{25,24,22,14,(*fun_b42)},	//关灯
	
	{26,29,27,16,(*fun_c41)},	//上限设定
	{27,26,28,17,(*fun_c42)},	//下限设定
	{28,27,29,19,(*fun_d41)},	//上限设定
	{29,28,26,20,(*fun_d42)},	//下限设定
	
};

/*********第1层***********/
void fun_a1()   
{	
	OLED_ShowChinese(0,0,21,16,1);	//主
	OLED_ShowChinese(17,0,22,16,1);	//菜
	OLED_ShowChinese(33,0,23,16,1);	//单
	
	OLED_ShowChinese(0,16,16,16,1);	//√
	OLED_ShowChinese(17,16,17,16,1);	//手
	OLED_ShowChinese(33,16,18,16,1);	//动
	OLED_ShowChinese(49,16,19,16,1);	//模
	OLED_ShowChinese(65,16,20,16,1);	//式	
	
	OLED_ShowChinese(17,32,24,16,1);	//自
	OLED_ShowChinese(33,32,18,16,1);	//动
	OLED_ShowChinese(49,32,19,16,1);	//模
	OLED_ShowChinese(65,32,20,16,1);	//式	
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_b1()   
{		
	OLED_ShowChinese(0,0,21,16,1);	//主
	OLED_ShowChinese(17,0,22,16,1);	//菜
	OLED_ShowChinese(33,0,23,16,1);	//单
	
	OLED_ShowChinese(17,16,17,16,1);	//手
	OLED_ShowChinese(33,16,18,16,1);	//动
	OLED_ShowChinese(49,16,19,16,1);	//模
	OLED_ShowChinese(65,16,20,16,1);	//式	
	
	OLED_ShowChinese(0,32,16,16,1);	//√
	OLED_ShowChinese(17,32,24,16,1);	//自
	OLED_ShowChinese(33,32,18,16,1);	//动
	OLED_ShowChinese(49,32,19,16,1);	//模
	OLED_ShowChinese(65,32,20,16,1);	//式	
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_c1()     
{	
	OLED_ShowChinese(0,0,21,16,1);	//主
	OLED_ShowChinese(17,0,22,16,1);	//菜
	OLED_ShowChinese(33,0,23,16,1);	//单
	
	OLED_ShowChinese(17,16,17,16,1);	//手
	OLED_ShowChinese(33,16,18,16,1);	//动
	OLED_ShowChinese(49,16,19,16,1);	//模
	OLED_ShowChinese(65,16,20,16,1);	//式	
	
	OLED_ShowChinese(17,32,24,16,1);	//自
	OLED_ShowChinese(33,32,18,16,1);	//动
	OLED_ShowChinese(49,32,19,16,1);	//模
	OLED_ShowChinese(65,32,20,16,1);	//式	
	
	OLED_ShowChinese(0,48,16,16,1);	//√	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}


/*********第2层***********/
void fun_a21()     
{	
	OLED_ShowChinese(0,0,17,16,1);	//手
	OLED_ShowChinese(17,0,18,16,1);	//动
	OLED_ShowChinese(33,0,19,16,1);	//模
	OLED_ShowChinese(49,0,20,16,1);	//式	
	
	OLED_ShowChinese(0,16,16,16,1);	//√
	OLED_ShowChinese(17,16,27,16,1);	//水
	OLED_ShowChinese(33,16,28,16,1);	//泵
	
	OLED_ShowChinese(17,32,29,16,1);	//生
	OLED_ShowChinese(33,32,30,16,1);	//长
	OLED_ShowChinese(49,32,31,16,1);	//灯
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
	
																					
}

void fun_a22()      
{	
	OLED_ShowChinese(0,0,17,16,1);	//手
	OLED_ShowChinese(17,0,18,16,1);	//动
	OLED_ShowChinese(33,0,19,16,1);	//模
	OLED_ShowChinese(49,0,20,16,1);	//式	
	
	OLED_ShowChinese(17,16,27,16,1);	//水
	OLED_ShowChinese(33,16,28,16,1);	//泵
	
	OLED_ShowChinese(0,32,16,16,1);	//√
	OLED_ShowChinese(17,32,29,16,1);	//生
	OLED_ShowChinese(33,32,30,16,1);	//长
	OLED_ShowChinese(49,32,31,16,1);	//灯
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
																						
}

void fun_a23()    
{	
	OLED_ShowChinese(0,0,17,16,1);	//手
	OLED_ShowChinese(17,0,18,16,1);	//动
	OLED_ShowChinese(33,0,19,16,1);	//模
	OLED_ShowChinese(49,0,20,16,1);	//式	
	
	OLED_ShowChinese(17,16,27,16,1);	//水
	OLED_ShowChinese(33,16,28,16,1);	//泵
	
	OLED_ShowChinese(17,32,29,16,1);	//生
	OLED_ShowChinese(33,32,30,16,1);	//长
	OLED_ShowChinese(49,32,31,16,1);	//灯
	
	OLED_ShowChinese(0,48,16,16,1);	//√
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_b21()    
{		
	OLED_ShowChinese(0,0,36,16,1);	//设
	OLED_ShowChinese(17,0,37,16,1);	//定
	OLED_ShowChinese(33,0,38,16,1);	//阈
	OLED_ShowChinese(49,0,39,16,1);	//值
	
	OLED_ShowChinese(0,16,16,16,1);	//√
	OLED_ShowChinese(17,16,8,16,1);	//湿
	OLED_ShowChinese(33,16,9,16,1);	//度

	OLED_ShowChinese(17,32,11,16,1);	//光
	OLED_ShowChinese(33,32,12,16,1);	//照
	OLED_ShowChinese(49,32,13,16,1);	//强
	OLED_ShowChinese(65,32,14,16,1);	//度

	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_b22()
{
	OLED_ShowChinese(0,0,36,16,1);	//设
	OLED_ShowChinese(17,0,37,16,1);	//定
	OLED_ShowChinese(33,0,38,16,1);	//阈
	OLED_ShowChinese(49,0,39,16,1);	//值

	OLED_ShowChinese(17,16,8,16,1);	//湿
	OLED_ShowChinese(33,16,9,16,1);	//度

	OLED_ShowChinese(0,32,16,16,1);	//√
	OLED_ShowChinese(17,32,11,16,1);	//光
	OLED_ShowChinese(33,32,12,16,1);	//照
	OLED_ShowChinese(49,32,13,16,1);	//强
	OLED_ShowChinese(65,32,14,16,1);	//度

	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_b23()
{
	OLED_ShowChinese(0,0,36,16,1);	//设
	OLED_ShowChinese(17,0,37,16,1);	//定
	OLED_ShowChinese(33,0,38,16,1);	//阈
	OLED_ShowChinese(49,0,39,16,1);	//值

	OLED_ShowChinese(17,16,8,16,1);	//湿
	OLED_ShowChinese(33,16,9,16,1);	//度

	OLED_ShowChinese(17,32,11,16,1);	//光
	OLED_ShowChinese(33,32,12,16,1);	//照
	OLED_ShowChinese(49,32,13,16,1);	//强
	OLED_ShowChinese(65,32,14,16,1);	//度

	OLED_ShowChinese(0,48,16,16,1);	//√
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

/*********第3层***********/
void fun_a31()    
{	
	OLED_ShowChinese(0,0,27,16,1);	//水
	OLED_ShowChinese(17,0,28,16,1);	//泵
	
	OLED_ShowChinese(0,16,16,16,1);	//√
	OLED_ShowChinese(17,16,32,16,1);	//打
	OLED_ShowChinese(33,16,33,16,1);	//开
	
	OLED_ShowChinese(17,32,34,16,1);	//关
	OLED_ShowChinese(33,32,35,16,1);	//闭
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
																						
}

void fun_a32()    
{	
	OLED_ShowChinese(0,0,27,16,1);	//水
	OLED_ShowChinese(17,0,28,16,1);	//泵
	
	OLED_ShowChinese(17,16,32,16,1);	//打
	OLED_ShowChinese(33,16,33,16,1);	//开
	
	OLED_ShowChinese(0,32,16,16,1);	//√
	OLED_ShowChinese(17,32,34,16,1);	//关
	OLED_ShowChinese(33,32,35,16,1);	//闭
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_a33()    
{	
	OLED_ShowChinese(0,0,27,16,1);	//水
	OLED_ShowChinese(17,0,28,16,1);	//泵
	
	OLED_ShowChinese(17,16,32,16,1);	//打
	OLED_ShowChinese(33,16,33,16,1);	//开
	
	OLED_ShowChinese(17,32,34,16,1);	//关
	OLED_ShowChinese(33,32,35,16,1);	//闭
	
	OLED_ShowChinese(0,48,16,16,1);	//√
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_b31()    
{	
	OLED_ShowChinese(0,0,29,16,1);	//生
	OLED_ShowChinese(17,0,30,16,1);	//长
	OLED_ShowChinese(33,0,31,16,1);	//灯
	
	OLED_ShowChinese(0,16,16,16,1);	//√
	OLED_ShowChinese(17,16,32,16,1);	//打
	OLED_ShowChinese(33,16,33,16,1);	//开
	
	OLED_ShowChinese(17,32,34,16,1);	//关
	OLED_ShowChinese(33,32,35,16,1);	//闭
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_b32()    
{	
	OLED_ShowChinese(0,0,29,16,1);	//生
	OLED_ShowChinese(17,0,30,16,1);	//长
	OLED_ShowChinese(33,0,31,16,1);	//灯
	
	OLED_ShowChinese(17,16,32,16,1);	//打
	OLED_ShowChinese(33,16,33,16,1);	//开
	
	OLED_ShowChinese(0,32,16,16,1);	//√
	OLED_ShowChinese(17,32,34,16,1);	//关
	OLED_ShowChinese(33,32,35,16,1);	//闭
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_b33()    
{	
	OLED_ShowChinese(0,0,29,16,1);	//生
	OLED_ShowChinese(17,0,30,16,1);	//长
	OLED_ShowChinese(33,0,31,16,1);	//灯
	
	OLED_ShowChinese(17,16,32,16,1);	//打
	OLED_ShowChinese(33,16,33,16,1);	//开
	
	OLED_ShowChinese(17,32,34,16,1);	//关
	OLED_ShowChinese(33,32,35,16,1);	//闭
	
	OLED_ShowChinese(0,48,16,16,1);	//√
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_c31()
{
	OLED_ShowChinese(0,0,8,16,1);	//湿
	OLED_ShowChinese(17,0,9,16,1);	//度
	
	OLED_ShowChinese(0,16,16,16,1);	//√
	OLED_ShowChinese(17,16,40,16,1);	//上
	OLED_ShowChinese(33,16,42,16,1);	//限
	
	OLED_ShowChinese(17,32,41,16,1);	//下
	OLED_ShowChinese(33,32,42,16,1);	//限
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}
void fun_c32()
{
	OLED_ShowChinese(0,0,8,16,1);	//湿
	OLED_ShowChinese(17,0,9,16,1);	//度
	
	OLED_ShowChinese(17,16,40,16,1);	//上
	OLED_ShowChinese(33,16,42,16,1);	//限
	
	OLED_ShowChinese(0,32,16,16,1);	//√
	OLED_ShowChinese(17,32,41,16,1);	//下
	OLED_ShowChinese(33,32,42,16,1);	//限
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_c33()
{
	OLED_ShowChinese(0,0,8,16,1);	//湿
	OLED_ShowChinese(17,0,9,16,1);	//度
	
	OLED_ShowChinese(17,16,40,16,1);	//上
	OLED_ShowChinese(33,16,42,16,1);	//限
	
	OLED_ShowChinese(17,32,41,16,1);	//下
	OLED_ShowChinese(33,32,42,16,1);	//限
	
	OLED_ShowChinese(0,48,16,16,1);	//√
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_d31()
{
	OLED_ShowChinese(0,0,11,16,1);	//光
	OLED_ShowChinese(17,0,12,16,1);	//照
	OLED_ShowChinese(33,0,13,16,1);	//强
	OLED_ShowChinese(49,0,14,16,1);	//度
	
	OLED_ShowChinese(0,16,16,16,1);	//√
	OLED_ShowChinese(17,16,40,16,1);	//上
	OLED_ShowChinese(33,16,42,16,1);	//限
	
	OLED_ShowChinese(17,32,41,16,1);	//下
	OLED_ShowChinese(33,32,42,16,1);	//限
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}
void fun_d32()
{
	OLED_ShowChinese(0,0,11,16,1);	//光
	OLED_ShowChinese(17,0,12,16,1);	//照
	OLED_ShowChinese(33,0,13,16,1);	//强
	OLED_ShowChinese(49,0,14,16,1);	//度
	
	OLED_ShowChinese(17,16,40,16,1);	//上
	OLED_ShowChinese(33,16,42,16,1);	//限
	
	OLED_ShowChinese(0,32,16,16,1);	//√
	OLED_ShowChinese(17,32,41,16,1);	//下
	OLED_ShowChinese(33,32,42,16,1);	//限
	
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}

void fun_d33()
{
	OLED_ShowChinese(0,0,11,16,1);	//光
	OLED_ShowChinese(17,0,12,16,1);	//照
	OLED_ShowChinese(33,0,13,16,1);	//强
	OLED_ShowChinese(49,0,14,16,1);	//度
	
	OLED_ShowChinese(17,16,40,16,1);	//上
	OLED_ShowChinese(33,16,42,16,1);	//限
	
	OLED_ShowChinese(17,32,41,16,1);	//下
	OLED_ShowChinese(33,32,42,16,1);	//限
	
	OLED_ShowChinese(0,48,16,16,1);	//√
	OLED_ShowChinese(17,48,25,16,1);	//返
	OLED_ShowChinese(33,48,26,16,1);	//回
}
/*********第4层***********/
void fun_a41()
{
	OLED_ShowChinese(0,0,16,16,1);	//√
	OLED_ShowChinese(17,0,25,16,1);	//返
	OLED_ShowChinese(33,0,26,16,1);	//回
	OLED_ShowPicture(28,16,72,48,BMP_1,1);	//开水
}

void fun_a42()
{
	OLED_ShowChinese(0,0,16,16,1);	//√
	OLED_ShowChinese(17,0,25,16,1);	//返
	OLED_ShowChinese(33,0,26,16,1);	//回
	OLED_ShowPicture(40,16,48,48,BMP_2,1);	//关水
}

void fun_b41()
{
	OLED_ShowChinese(0,0,16,16,1);	//√
	OLED_ShowChinese(17,0,25,16,1);	//返
	OLED_ShowChinese(33,0,26,16,1);	//回
	OLED_ShowPicture(40,16,48,48,BMP_3,1);	//开灯
}

void fun_b42()
{
	OLED_ShowChinese(0,0,16,16,1);	//√
	OLED_ShowChinese(17,0,25,16,1);	//返
	OLED_ShowChinese(33,0,26,16,1);	//回
	OLED_ShowPicture(40,16,48,48,BMP_4,1);	//关灯
}

void fun_c41()
{
	OLED_ShowChinese(0,0,40,16,1);	//上
	OLED_ShowChinese(17,0,42,16,1);	//限
	OLED_ShowChinese(33,0,36,16,1);	//设
	OLED_ShowChinese(49,0,37,16,1);	//定
	
	OLED_ShowChinese(0,22,43,16,1);	//当
	OLED_ShowChinese(17,22,44,16,1);	//前
	OLED_ShowChinese(33,22,39,16,1);	//值
}

void fun_c42()
{
	OLED_ShowChinese(0,0,41,16,1);	//下
	OLED_ShowChinese(17,0,42,16,1);	//限
	OLED_ShowChinese(33,0,36,16,1);	//设
	OLED_ShowChinese(49,0,37,16,1);	//定
	
	OLED_ShowChinese(0,22,43,16,1);	//当
	OLED_ShowChinese(17,22,44,16,1);	//前
	OLED_ShowChinese(33,22,39,16,1);	//值
}

void fun_d41()
{
	OLED_ShowChinese(0,0,40,16,1);	//上
	OLED_ShowChinese(17,0,42,16,1);	//限
	OLED_ShowChinese(33,0,36,16,1);	//设
	OLED_ShowChinese(49,0,37,16,1);	//定
	
	OLED_ShowChinese(0,22,43,16,1);	//当
	OLED_ShowChinese(17,22,44,16,1);	//前
	OLED_ShowChinese(33,22,39,16,1);	//值
}

void fun_d42()
{
	OLED_ShowChinese(0,0,41,16,1);	//下
	OLED_ShowChinese(17,0,42,16,1);	//限
	OLED_ShowChinese(33,0,36,16,1);	//设
	OLED_ShowChinese(49,0,37,16,1);	//定
	
	OLED_ShowChinese(0,22,43,16,1);	//当
	OLED_ShowChinese(17,22,44,16,1);	//前
	OLED_ShowChinese(33,22,39,16,1);	//值
}

/*********第0层***********/
void fun_0()
{
	OLED_ShowChinese(1,0,0,16,1);	//智
	OLED_ShowChinese(17,0,1,16,1);	//能
	OLED_ShowChinese(33,0,2,16,1);	//农
	OLED_ShowChinese(49,0,3,16,1);	//业
	OLED_ShowChinese(65,0,4,16,1);	//灌
	OLED_ShowChinese(81,0,5,16,1);	//溉
	OLED_ShowChinese(97,0,6,16,1);	//系
	OLED_ShowChinese(109,0,7,16,1);	//统
	
	OLED_ShowChinese(1,22,8,16,1);	//湿
	OLED_ShowChinese(17,22,9,16,1);	//度
	OLED_ShowChinese(33,22,10,16,1);	//：
	OLED_ShowString(75,22,"%",16,1);//%
	
	OLED_ShowChinese(1,43,11,16,1);	//光
	OLED_ShowChinese(17,43,12,16,1);	//照
	OLED_ShowChinese(33,43,13,16,1);	//强
	OLED_ShowChinese(49,43,14,16,1);	//度
	OLED_ShowChinese(65,43,15,16,1);	//：
	OLED_ShowString(100,43,"LX",16,1);//8*16 “ABC”			
}
