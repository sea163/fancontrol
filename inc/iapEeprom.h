#ifndef __IAPEEPROM_H__
#define __IAPEEPROM_H__

#include "config.h"

/*Define ISP/IAP/EEPROM command*/
#define IAP_IDLE     0                         //Stand-By
#define IAP_BYTE_READ 1	  //字节读
#define IAP_BYTE_PROGRAM 2 //字节编程,前提是该字节是空，0FFh
#define IAP_SECTOR_ERASE 3 //扇区擦除,要某字节为空，要擦一扇区

/*Define ISP/IAP/EEPROM operation const for IAP_CONTR*/
#define  ENABLE_IAP   0x80             //if SYSCLK<30MHz
//#define  ENABLE_IAP   0x81               //if SYSCLK<24MHz
//#define   ENABLE_IAP    0x82           //if SYSCLK<20MHz
//#define  ENABLE_IAP   0x83             //if SYSCLK<12MHz
//#define  ENABLE_IAP   0x84             //if SYSCLK<6MHz
//#define  ENABLE_IAP   0x85             //if SYSCLK<3MHz
//#define  ENABLE_IAP   0x86             //if SYSCLK<2MHz
//#define  ENABLE_IAP   0x87             //if SYSCLK<MHz

//Start address for series EEPROM
//STC15F104E eeprom大小 1K 地址范围 0000H~03FFH(KB)
#define   IAP_ADDRESS   0x0000

//trigger command
//stc15f100
#define   TRIGGER_COMMAND1 0x5a
#define   TRIGGER_COMMAND2 0xa5
//stc89c52
//#define   TRIGGER_COMMAND1 0x46
//#define   TRIGGER_COMMAND2 0xb9

/*功能: 数据Flash区扇区擦除
扇区擦除，没有字节擦除，只有扇区擦除，512 字节 / 扇区,
扇区里面任意一个字节的地址都是扇区地址,无需求首地址,单片机会自己处理
建议同一次修改的数据放在同一个扇区
如果要对某个扇区进行擦除，而其中有些字节的内容需要保留，则需将其先读到单片机
内部的 RAM 中保存，再将该扇区擦除，然后将须保留的数据写回该扇区，
所以每个扇区中用的字节数越少越好，操作起来越灵活越快
强烈建议同一次修改的数据放在同一个扇区
IAPCommand( IAP_SECTOR_ERASE, address, 0);
IAPCommand(IAP_BYTE_PROGRAM, IAP_ADDRESS, dat);
dat = IAPCommand(IAP_BYTE_READ, IAP_ADDRESS, 0);
*/

uint8_t IAPCommand(uint8_t cmd, unsigned int address,uint8_t value);
void IAPBufCommand(uint8_t cmd, unsigned int address, uint8_t *buf,uint8_t len);
#endif