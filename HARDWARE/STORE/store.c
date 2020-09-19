#include "store.h"

unsigned char IsManager=0;
unsigned char CT[2];//卡类型
unsigned char SN[4]; //卡号
unsigned char RFID[16];			//存放RFID 
unsigned char KEYB_1B[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};   //管理员卡秘钥B (管理员权限)
unsigned char RFID1[16];
unsigned char RFID2[16];
u8 addrAdmin=0x18; //验证身份信息使用的扇区0x18~0x1B


/*******读卡函数，步骤：寻卡-》防冲撞-》选卡-》秘钥验证*********/
u8 ReadCard(u8 addr,u8* pwd)
{
	u8 status=MI_ERR;
	PcdAntennaOn();
	status=PcdRequest(PICC_REQALL,CT);
	if(status==MI_OK)  //寻卡成功
	{
		status=MI_ERR;
		status = PcdAnticoll(SN);/*防冲撞*/
		if (status==MI_OK)//防冲撞成功
		{
			status=MI_ERR;
			status=PcdSelect(SN); /*选卡*/
		}
		if(status==MI_OK)//选卡成功
		{
			 status=MI_ERR;
				 status =PcdAuthState(0x61,addr,pwd,SN); /*验证秘钥B*/
		}
		if(status==MI_OK)//验证秘钥成功
		{
			PcdRead(addr,RFID);
			status=MI_OK;
		}	
	}
	else
	{
		PcdAntennaOff();  //关闭天线
	}
	return status;
}


/*******写卡函数*********/
u8 WriteCard(u8 addr,u8* pwd,unsigned char RFID1[16])
{
	u8 status=MI_ERR;
	u16 RETRY=0xFFF;
	PcdAntennaOn(); //开启天线
	do
	{
		RETRY--;
		status=PcdRequest(PICC_REQALL,CT);  
	}while(RETRY!=0&&status!=MI_OK); //等待寻卡成功
	if(RETRY!=0&&status==MI_OK)  //寻卡成功
	{
		status=MI_ERR;
		status = PcdAnticoll(SN);/*防冲撞*/
		if (status==MI_OK)//防冲撞成功
		{
			status=MI_ERR;
			status=PcdSelect(SN); /*选卡*/
		}
		if(status==MI_OK)//选卡成功
		{
			 status=MI_ERR;
				status =PcdAuthState(0x61,addr,pwd,SN); /*验证秘钥B*/
		}
		if(status==MI_OK)//验证秘钥成功
		{
			PcdWrite(addr,RFID1);
			status=MI_OK;
		}	
	}
	else
	{
		PcdAntennaOff();  //关闭天线
	}
	return status;
}


u8 store(u8 addr,u8* pwd)
{
	u8 status=MI_ERR;
	status=ReadCard(addr,pwd);
	if(status==MI_OK) //读卡成功
	{
			IsManager=1;
			return MI_OK;
	}
	return MI_ERR;
}

