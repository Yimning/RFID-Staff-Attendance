#ifndef _STORE_H
#define _STORE_H
#include "sys.h"
#include "rc522.h"
#include "key.h"
#include "stdio.h"
#include "string.h"

extern unsigned char CT[2];//������
extern unsigned char SN[4]; //����
extern unsigned char RFID[16];			//���RFID 
extern unsigned char RFID1[16];
extern unsigned char RFID2[16];
extern unsigned char KEYB_1B[6];   //1B��ַ������ԿB
extern unsigned char IsManager;
extern u8 addrAdmin; //����Ա��֤�����Ϣʹ�õ�����0x18~0x1B  ���ݿ�����ԿB��֤��ֻ�ܶ�����д
u8 store(u8 addr,u8* pwd);   //��֤����Ա�û�
u8 ReadCard(u8 addr,u8* pwd);  //����
u8 WriteCard(u8 addr,u8* pwd,unsigned char RFID1[16]);
#endif


