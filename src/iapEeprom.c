/*
说明: 用于STC系列单片机内部EEPROM操作
设置等待时间                 CPU   等待时间(机器周期)
WT2 WT1 WT0 Read Program Sector Erase Recommended System Cloc
 0  1  1 6 30 5471 5MHz
 0  1  0 11 60 10942 10MHz
 0  0  1 22 120 21885 20MHz
 0  0  0 43 240 43769 40MHz

STC89C52RC,STC89LE52RC 单片机内部可用Data Flash(EEPROM)的地址：
每个扇区512字节建议同一次修改的数据放在同一扇区
第一扇区         第二扇区         第三扇区        第四扇区
起始地址 结束地址 起始地址 结束地址 起始地址 结束地址 起始地址 结束地址
2000h    21FFh    2200h    23FFh    2400h    25FFh    2600h    27FFh
第五扇区         第六扇区         第七扇区        第八扇区
起始地址 结束地址 起始地址 结束地址 起始地址 结束地址 起始地址 结束地址
2800h    29FFh    2A00h    2BFFh    2C00h    2DFFh    2E00h    2FFFh
*/
#include "iapEeprom.h"

/**
 * @brief 触发IAP命令
 *
 * 根据给定的命令、地址和值触发IAP（In-Application Programming）操作。
 *
 * @param cmd 命令字节
 * @param address 目标地址（无符号整数）
 * @param value 要写入的值（8位无符号整数）
 *
 * @return 读取到的IAP数据（8位无符号整数）
 */
uint8_t IAPCommand(uint8_t cmd, unsigned int address,uint8_t value)
{
    IAP_ADDRL = address;//送地址低字节 地址需要改变时才需重新送地址
    IAP_ADDRH = address >> 8;//送地址高字节
    IAP_DATA = value;
	//允许ISP/IAP 操作
    IAP_CONTR = ENABLE_IAP;							//允许ISP/IAP 操作 设置等待时间
    IAP_CMD = cmd;					//送字节读命令,命令不需改变时,不需重新送命令

    IAP_TRIG = TRIGGER_COMMAND1;//先送46h,再送B9h 到ISP/IAP 触发寄存器,每次都需如此
    IAP_TRIG = TRIGGER_COMMAND2;//送完B9h 后，ISP/IAP 命令立即被触发起动
	//再送46h,B9h 到ISP/IAP 触发寄存器,起动ISP/IAP 命令,关中断在触发之前即可
    _nop_();
	_nop_();
	_nop_();
	//以下语句可不用,只是出于安全考虑而已
    IAP_CONTR = 0;		//禁止ISP/IAP操作
    IAP_CMD = 0;        //去除ISP/IAP命令
    IAP_TRIG = 0;		//防止ISP/IAP命令误触发
    IAP_ADDRH = 0;		//送地址高字节单元为00,指向非EEPROM 区
    IAP_ADDRL = 0;		//送地址低字节单元为00,防止误操作

	return (IAP_DATA); 
}

/**
 * @brief IAP缓冲区命令
 *
 * 执行数据Flash区的字节读写操作。
 *
 * @param cmd 命令码
 *   - IAP_BYTE_READ: 读取字节
 *   - IAP_BYTE_PROGRAM: 写入字节
 * @param address Flash地址
 * @param buf 缓冲区指针，用于存放读取的数据或待写入的数据
 * @param len 缓冲区长度，即要读取或写入的字节数
 */
void IAPBufCommand(uint8_t cmd, unsigned int address, uint8_t *buf,uint8_t len)
{
	/*功能: 数据Flash区字节读写*/	
    uint8_t i;
    for (i=0; i< len; i++)
    {
		if (cmd == IAP_BYTE_READ)
			buf[i] = IAPCommand( IAP_BYTE_READ, address, 0);
		else
			IAPCommand( IAP_BYTE_PROGRAM, address, buf[i]);
        address++;
    }
}