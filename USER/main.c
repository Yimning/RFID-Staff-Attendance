#include "output.h"
#include "delay.h"
#include "sys.h"
#include "rc522.h"
#include "usart.h"
#include "string.h" 
#include "led.h"
#include "store.h"
#include "beep.h"

/*******************************
*连线说明：
*1--SS  <----->PF0
*2--SCK <----->PB13
*3--MOSI<----->PB15
*4--MISO<----->PB14
*5--悬空
*6--GND <----->GND
*7--RST <----->PF1
*8--VCC <----->VCC
********************************/
int main(void)
{		
	unsigned char status;
	u16 len;
	u16 t;
	Stm32_Clock_Init(9);
	MY_NVIC_PriorityGroupConfig(2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	delay_init(72);	    	 //延时函数初始化	
 	OUTPUT_Init();			 //输出模块初始化
	uart_init(72,115200);
	LED_Init();
	BEEP_Init();         	//初始化蜂鸣器端口
	InitRc522();				//初始化射频卡模块
	
	while(1) 
	{
		status=store(addrAdmin,KEYB_1B);  //认证   
		if(IsManager==1){ //验证身份成功
			delay_ms(1000);
			//printf("卡号:");
			for(t=0;t<4;t++) 
			{ 
				printf("%02x",SN[t]);
			}
			//printf("\r\n数据:");
			for(t=0;t<16;t++) 
			{ 
				printf("%c",RFID[t]);
			}
			printf("\r\n");
			IsManager=0;
			delay_ms(1000);
		}
		
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			
			if(len==17) 
			{
				if(USART_RX_BUF[0]=='W')    //写卡命令
				{
					LED0=0;
					for(t=0;t<16;t++)
					{
						RFID1[t]=USART_RX_BUF[t+1];
					}
					status=MI_ERR;
	        status=WriteCard(addrAdmin,KEYB_1B,RFID1);
					if(status==MI_OK)
						printf("成功\r\n");
					else
						printf("失败\r\n");
					delay_ms(1000);
					LED0=1;
				}
			}
			
			if(len==2)
			{
				if(USART_RX_BUF[0]=='J')     //是否成功
				{	
				  if(USART_RX_BUF[1]=='T')
					{
						LED1=0;
						//BEEP=1;	
						delay_ms(500);
						LED1=1;
						//BEEP=0;
					}
					if(USART_RX_BUF[1]=='F')
					{
						LED0=0;	
						delay_ms(500);
						LED0=1;
					}
				}
			}
			
			USART_RX_STA=0;
		}
		/*else
		{
			status=store(addrAdmin,KEYB_1B);  //认证   
		 if(IsManager==1){ //验证身份成功
			delay_ms(1000);
			//printf("卡号:");
			for(t=0;t<4;t++) 
			{ 
				printf("%02x",SN[t]);
			}
			//printf("\r\n数据:");
			for(t=0;t<16;t++) 
			{ 
				printf("%c",RFID[t]);
			}
			printf("\r\n");
			IsManager=0;
			delay_ms(1000);
		}
		}*/
	}
	
}

