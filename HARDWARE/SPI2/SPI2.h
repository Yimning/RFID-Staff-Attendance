#ifndef _SPI2_H
#define _SPI2_H

#include "sys.h"
void SPI2_Init(void); //SPI��ʼ��
void SPI2_SpeedSet(u8 speed); //SPIʱ�����ã�����APB1�ķ�Ƶ
u8 SPI2_ReadWriteByte(u8 TxData);//SPI��д����
u8 SPIWriteByte(u8 Byte); //SPI����
#endif
