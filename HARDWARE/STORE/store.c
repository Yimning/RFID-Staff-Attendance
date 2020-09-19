#include "store.h"

unsigned char IsManager=0;
unsigned char CT[2];//������
unsigned char SN[4]; //����
unsigned char RFID[16];			//���RFID 
unsigned char KEYB_1B[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};   //����Ա����ԿB (����ԱȨ��)
unsigned char RFID1[16];
unsigned char RFID2[16];
u8 addrAdmin=0x18; //��֤�����Ϣʹ�õ�����0x18~0x1B


/*******�������������裺Ѱ��-������ײ-��ѡ��-����Կ��֤*********/
u8 ReadCard(u8 addr,u8* pwd)
{
	u8 status=MI_ERR;
	PcdAntennaOn();
	status=PcdRequest(PICC_REQALL,CT);
	if(status==MI_OK)  //Ѱ���ɹ�
	{
		status=MI_ERR;
		status = PcdAnticoll(SN);/*����ײ*/
		if (status==MI_OK)//����ײ�ɹ�
		{
			status=MI_ERR;
			status=PcdSelect(SN); /*ѡ��*/
		}
		if(status==MI_OK)//ѡ���ɹ�
		{
			 status=MI_ERR;
				 status =PcdAuthState(0x61,addr,pwd,SN); /*��֤��ԿB*/
		}
		if(status==MI_OK)//��֤��Կ�ɹ�
		{
			PcdRead(addr,RFID);
			status=MI_OK;
		}	
	}
	else
	{
		PcdAntennaOff();  //�ر�����
	}
	return status;
}


/*******д������*********/
u8 WriteCard(u8 addr,u8* pwd,unsigned char RFID1[16])
{
	u8 status=MI_ERR;
	u16 RETRY=0xFFF;
	PcdAntennaOn(); //��������
	do
	{
		RETRY--;
		status=PcdRequest(PICC_REQALL,CT);  
	}while(RETRY!=0&&status!=MI_OK); //�ȴ�Ѱ���ɹ�
	if(RETRY!=0&&status==MI_OK)  //Ѱ���ɹ�
	{
		status=MI_ERR;
		status = PcdAnticoll(SN);/*����ײ*/
		if (status==MI_OK)//����ײ�ɹ�
		{
			status=MI_ERR;
			status=PcdSelect(SN); /*ѡ��*/
		}
		if(status==MI_OK)//ѡ���ɹ�
		{
			 status=MI_ERR;
				status =PcdAuthState(0x61,addr,pwd,SN); /*��֤��ԿB*/
		}
		if(status==MI_OK)//��֤��Կ�ɹ�
		{
			PcdWrite(addr,RFID1);
			status=MI_OK;
		}	
	}
	else
	{
		PcdAntennaOff();  //�ر�����
	}
	return status;
}


u8 store(u8 addr,u8* pwd)
{
	u8 status=MI_ERR;
	status=ReadCard(addr,pwd);
	if(status==MI_OK) //�����ɹ�
	{
			IsManager=1;
			return MI_OK;
	}
	return MI_ERR;
}

