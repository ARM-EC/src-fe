#ifndef __MULTI_MENU_H
#define __MULTI_MENU_H	 
		
#define uchar unsigned char

typedef struct
{
	uchar current;//当前按键的索引号
	uchar up;//向上翻索引号
	uchar down;//向下翻索引号
	uchar enter;//确认索引号
	void (*current_operation)();
} key_table;

extern key_table table[30];

	
extern void fun_a1(void); 
extern void fun_b1(void);  
extern void fun_c1(void);  
extern void fun_d1(void);  

extern void fun_a21(void); 
extern void fun_a22(void);  
extern void fun_a23(void);  
extern void fun_a24(void);  

extern void fun_b21(void); 
extern void fun_b22(void);  
extern void fun_b23(void);  
extern void fun_b24(void); 

extern void fun_c21(void); 
extern void fun_c22(void);  
extern void fun_c23(void);  

extern void fun_a31(void); 
extern void fun_a32(void);  
extern void fun_a33(void);  

extern void fun_b31(void); 
extern void fun_b32(void);  
extern void fun_b33(void); 

extern void fun_c31(void); 
extern void fun_c32(void);  
extern void fun_c33(void); 

extern void fun_d31(void); 
extern void fun_d32(void);  
extern void fun_d33(void); 


extern void fun_a41(void);
extern void fun_a42(void);
extern void fun_b41(void);
extern void fun_b42(void);
extern void fun_c41(void);
extern void fun_c42(void);
extern void fun_d41(void);
extern void fun_d42(void);  

extern void fun_0(void);   

#endif
