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
*����˵����
*1--SS  <----->PF0
*2--SCK <----->PB13
*3--MOSI<----->PB15
*4--MISO<----->PB14
*5--����
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
	MY_NVIC_PriorityGroupConfig(2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	delay_init(72);	    	 //��ʱ������ʼ��	
 	OUTPUT_Init();			 //���ģ���ʼ��
	uart_init(72,115200);
	LED_Init();
	BEEP_Init();         	//��ʼ���������˿�
	InitRc522();				//��ʼ����Ƶ��ģ��
	
	while(1) 
	{
		status=store(addrAdmin,KEYB_1B);  //��֤   
		if(IsManager==1){ //��֤��ݳɹ�
			delay_ms(1000);
			//printf("����:");
			for(t=0;t<4;t++) 
			{ 
				printf("%02x",SN[t]);
			}
			//printf("\r\n����:");
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
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			
			if(len==17) 
			{
				if(USART_RX_BUF[0]=='W')    //д������
				{
					LED0=0;
					for(t=0;t<16;t++)
					{
						RFID1[t]=USART_RX_BUF[t+1];
					}
					status=MI_ERR;
	        status=WriteCard(addrAdmin,KEYB_1B,RFID1);
					if(status==MI_OK)
						printf("�ɹ�\r\n");
					else
						printf("ʧ��\r\n");
					delay_ms(1000);
					LED0=1;
				}
			}
			
			if(len==2)
			{
				if(USART_RX_BUF[0]=='J')     //�Ƿ�ɹ�
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
			status=store(addrAdmin,KEYB_1B);  //��֤   
		 if(IsManager==1){ //��֤��ݳɹ�
			delay_ms(1000);
			//printf("����:");
			for(t=0;t<4;t++) 
			{ 
				printf("%02x",SN[t]);
			}
			//printf("\r\n����:");
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

