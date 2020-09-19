#ifndef _STORE_H
#define _STORE_H
#include "sys.h"
#include "rc522.h"
#include "key.h"
#include "stdio.h"
#include "string.h"

extern unsigned char CT[2];//卡类型
extern unsigned char SN[4]; //卡号
extern unsigned char RFID[16];			//存放RFID 
extern unsigned char RFID1[16];
extern unsigned char RFID2[16];
extern unsigned char KEYB_1B[6];   //1B地址扇区秘钥B
extern unsigned char IsManager;
extern u8 addrAdmin; //管理员验证身份信息使用的扇区0x18~0x1B  数据块由秘钥B认证后只能读不能写
u8 store(u8 addr,u8* pwd);   //验证管理员用户
u8 ReadCard(u8 addr,u8* pwd);  //读卡
u8 WriteCard(u8 addr,u8* pwd,unsigned char RFID1[16]);
#endif


