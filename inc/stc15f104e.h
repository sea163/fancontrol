#ifndef __STC15F104E_H__
#define __STC15F104E_H__

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif


/* redefine some keywords */

// primitive type
typedef __sfr sfr;
typedef __sfr16 sfr16;
typedef __sfr32 sfr32;
typedef __sbit sbit;
typedef __bit bit;

// keywords
#define interrupt __interrupt
#define using __using
#define _at_ __at
#define _priority_
#define _task_

// storage type
#define reentrant __reentrant
#define compact
#define small __near
#define large __far
#define data __data
#define bdata
#define idata __idata
#define pdata __pdata
#define xdata __xdata
#define code __code

/////////////////////////////////////////////////

//包含本头文件后,不用另外再包含"REG51.H"

// 内核特殊功能寄存器        // 复位值   描述
__sfr __at (0xE0) ACC;   // 0000,0000 累加器Accumulator
__sfr __at (0xF0) B;     // 0000,0000 B寄存器
__sfr __at (0xD0) PSW;   // 0000,0000 程序状态字

__sbit __at (0xD7) CY;   // PSW^7
__sbit __at (0xD6) AC;   // PSW^6
__sbit __at (0xD5) F0;   // PSW^5
__sbit __at (0xD4) RS1;  // PSW^4
__sbit __at (0xD3) RS0;  // PSW^3
__sbit __at (0xD2) OV;   // PSW^2
__sbit __at (0xD1) F1;   // PSW^1
__sbit __at (0xD0) P;    // PSW^0

__sfr __at (0x81) SP;    // 0000,0111 堆栈指针
__sfr __at (0x82) DPL;   // 0000,0000 数据指针低字节
__sfr __at (0x83) DPH;   // 0000,0000 数据指针高字节


// I/O 口特殊功能寄存器
__sfr __at (0x80) P0;   // 1111,1111 端口0
__sbit __at (0x80) P00; // P0^0
__sbit __at (0x81) P01; // P0^1
__sbit __at (0x82) P02; // P0^2
__sbit __at (0x83) P03; // P0^3
__sbit __at (0x84) P04; // P0^4
__sbit __at (0x85) P05; // P0^5
__sbit __at (0x86) P06; // P0^6
__sbit __at (0x87) P07; // P0^7

__sfr __at (0x90) P1;   // 1111,1111 端口1
__sbit __at (0x90) P10; // P1^0
__sbit __at (0x91) P11; // P1^1
__sbit __at (0x92) P12; // P1^2
__sbit __at (0x93) P13; // P1^3
__sbit __at (0x94) P14; // P1^4
__sbit __at (0x95) P15; // P1^5
__sbit __at (0x96) P16; // P1^6
__sbit __at (0x97) P17; // P1^7

__sfr __at (0xA0) P2;   // 1111,1111 端口2
__sbit __at (0xA0) P20; // P2^0
__sbit __at (0xA1) P21; // P2^1
__sbit __at (0xA2) P22; // P2^2
__sbit __at (0xA3) P23; // P2^3
__sbit __at (0xA4) P24; // P2^4
__sbit __at (0xA5) P25; // P2^5
__sbit __at (0xA6) P26; // P2^6
__sbit __at (0xA7) P27; // P2^7

__sfr __at (0xB0) P3;   // 1111,1111 端口3
__sbit __at (0xB0) P30; // P3^0
__sbit __at (0xB1) P31; // P3^1
__sbit __at (0xB2) P32; // P3^2
__sbit __at (0xB3) P33; // P3^3
__sbit __at (0xB4) P34; // P3^4
__sbit __at (0xB5) P35; // P3^5
__sbit __at (0xB6) P36; // P3^6
__sbit __at (0xB7) P37; // P3^7

__sfr __at (0xC0) P4;   // 1111,1111 端口4
__sbit __at (0xC0) P40; // P4^0
__sbit __at (0xC1) P41; // P4^1
__sbit __at (0xC2) P42; // P4^2
__sbit __at (0xC3) P43; // P4^3
__sbit __at (0xC4) P44; // P4^4
__sbit __at (0xC5) P45; // P4^5
__sbit __at (0xC6) P46; // P4^6
__sbit __at (0xC7) P47; // P4^7

__sfr __at (0xC8) P5;   // xxxx,1111 端口5
__sbit __at (0xC8) P50; // P5^0
__sbit __at (0xC9) P51; // P5^1
__sbit __at (0xCA) P52; // P5^2
__sbit __at (0xCB) P53; // P5^3
__sbit __at (0xCC) P54; // P5^4
__sbit __at (0xCD) P55; // P5^5
__sbit __at (0xCE) P56; // P5^6
__sbit __at (0xCF) P57; // P5^7

__sfr __at (0xE8) P6;   // 0000,0000 端口6
__sbit __at (0xE8) P60; // P6^0
__sbit __at (0xE9) P61; // P6^1
__sbit __at (0xEA) P62; // P6^2
__sbit __at (0xEB) P63; // P6^3
__sbit __at (0xEC) P64; // P6^4
__sbit __at (0xED) P65; // P6^5
__sbit __at (0xEE) P66; // P6^6
__sbit __at (0xEF) P67; // P6^7

__sfr __at (0xF8) P7;   // 0000,0000 端口7
__sbit __at (0xF8) P70; // P7^0
__sbit __at (0xF9) P71; // P7^1
__sbit __at (0xFA) P72; // P7^2
__sbit __at (0xFB) P73; // P7^3
__sbit __at (0xFC) P74; // P7^4
__sbit __at (0xFD) P75; // P7^5
__sbit __at (0xFE) P76; // P7^6
__sbit __at (0xFF) P77; // P7^7

__sfr __at (0x94) P0M0; // 0000,0000 端口0模式寄存器0
__sfr __at (0x93) P0M1; // 0000,0000 端口0模式寄存器1
__sfr __at (0x92) P1M0; // 0000,0000 端口1模式寄存器0
__sfr __at (0x91) P1M1; // 0000,0000 端口1模式寄存器1
__sfr __at (0x96) P2M0; // 0000,0000 端口2模式寄存器0
__sfr __at (0x95) P2M1; // 0000,0000 端口2模式寄存器1
__sfr __at (0xB2) P3M0; // 0000,0000 端口3模式寄存器0
__sfr __at (0xB1) P3M1; // 0000,0000 端口3模式寄存器1
__sfr __at (0xB4) P4M0; // 0000,0000 端口4模式寄存器0
__sfr __at (0xB3) P4M1; // 0000,0000 端口4模式寄存器1
__sfr __at (0xCA) P5M0; // 0000,0000 端口5模式寄存器0
__sfr __at (0xC9) P5M1; // 0000,0000 端口5模式寄存器1
__sfr __at (0xCC) P6M0; // 0000,0000 端口6模式寄存器0
__sfr __at (0xCB) P6M1; // 0000,0000 端口6模式寄存器1
__sfr __at (0xE2) P7M0; // 0000,0000 端口7模式寄存器0
__sfr __at (0xE1) P7M1; // 0000,0000 端口7模式寄存器1

// 系统管理特殊功能寄存器
__sfr __at (0x87) PCON;       // 0001,0000 电源控制寄存器
__sfr __at (0x8E) AUXR;       // 0000,0000 辅助寄存器
__sfr __at (0xA2) AUXR1;      // 0000,0000 辅助寄存器1
__sfr __at (0xA2) P_SW1;      // 0000,0000 外设端口切换寄存器1
__sfr __at (0x97) CLK_DIV;    // xxxx,x000 时钟分频控制寄存器
__sfr __at (0xA1) BUS_SPEED;  // xx10,x011 总线速度控制寄存器
__sfr __at (0x9D) P1ASF;      // 0000,0000 端口1模拟功能配置寄存器
__sfr __at (0xBA) P_SW2;      // 0000,0000 外设端口切换寄存器
__sfr __at (0xBB) IRC_CLKO;   // 0000,0000 内部振荡器时钟输出控制寄存器

// 中断特殊功能寄存器
__sfr __at (0xA8) IE;         // 0000,0000 中断控制寄存器
__sbit __at (0xAF) EA;        // IE^7
__sbit __at (0xAE) ELVD;      // IE^6
__sbit __at (0xAD) EADC;      // IE^5
__sbit __at (0xAC) ES;        // IE^4
__sbit __at (0xAB) ET1;       // IE^3
__sbit __at (0xAA) EX1;       // IE^2
__sbit __at (0xA9) ET0;       // IE^1
__sbit __at (0xA8) EX0;       // IE^0
__sfr __at (0xB8) IP;         // 0000,0000 中断优先级寄存器
__sbit __at (0xBF) PPCA;      // IP^7
__sbit __at (0xBE) PLVD;      // IP^6
__sbit __at (0xBD) PADC;      // IP^5
__sbit __at (0xBC) PS;        // IP^4
__sbit __at (0xBB) PT1;       // IP^3
__sbit __at (0xBA) PX1;       // IP^2
__sbit __at (0xB9) PT0;       // IP^1
__sbit __at (0xB8) PX0;       // IP^0
__sfr __at (0xAF) IE2;        // 0000,0000 中断控制寄存器2
__sfr __at (0xB5) IP2;        // xxxx,xx00 中断优先级寄存器2
__sfr __at (0x8F) INT_CLKO;   // 0000,0000 外部中断与时钟输出控制寄存器

// 定时器特殊功能寄存器
__sfr __at (0x88) TCON;       // 0000,0000 T0/T1控制寄存器
__sbit __at (0x8F) TF1;       // TCON^7
__sbit __at (0x8E) TR1;       // TCON^6
__sbit __at (0x8D) TF0;       // TCON^5
__sbit __at (0x8C) TR0;       // TCON^4
__sbit __at (0x8B) IE1;       // TCON^3
__sbit __at (0x8A) IT1;       // TCON^2
__sbit __at (0x89) IE0;       // TCON^1
__sbit __at (0x88) IT0;       // TCON^0
__sfr __at (0x89) TMOD;       // 0000,0000 T0/T1模式寄存器
__sfr __at (0x8A) TL0;        // 0000,0000 T0低字节
__sfr __at (0x8B) TL1;        // 0000,0000 T1低字节
__sfr __at (0x8C) TH0;        // 0000,0000 T0高字节
__sfr __at (0x8D) TH1;        // 0000,0000 T1高字节
__sfr __at (0xD1) T4T3M;      // 0000,0000 T3/T4模式寄存器
__sfr __at (0xD1) T3T4M;      // 0000,0000 T3/T4模式寄存器
__sfr __at (0xD2) T4H;        // 0000,0000 T4高字节
__sfr __at (0xD3) T4L;        // 0000,0000 T4低字节
__sfr __at (0xD4) T3H;        // 0000,0000 T3高字节
__sfr __at (0xD5) T3L;        // 0000,0000 T3低字节
__sfr __at (0xD6) T2H;        // 0000,0000 T2高字节
__sfr __at (0xD7) T2L;        // 0000,0000 T2低字节
__sfr __at (0xAA) WKTCL;      // 0000,0000 掉电唤醒定时器低字节
__sfr __at (0xAB) WKTCH;      // 0000,0000 掉电唤醒定时器高字节
__sfr __at (0xC1) WDT_CONTR;  // 0000,0000 看门狗控制寄存器

// 串行口特殊功能寄存器
__sfr __at (0x98) SCON;       // 0000,0000 串口1控制寄存器
__sbit __at (0x9F) SM0;       // SCON^7
__sbit __at (0x9E) SM1;       // SCON^6
__sbit __at (0x9D) SM2;       // SCON^5
__sbit __at (0x9C) REN;       // SCON^4
__sbit __at (0x9B) TB8;       // SCON^3
__sbit __at (0x9A) RB8;       // SCON^2
__sbit __at (0x99) TI;        // SCON^1
__sbit __at (0x98) RI;        // SCON^0
__sfr __at (0x99) SBUF;       // xxxx,xxxx 串口1数据寄存器
__sfr __at (0x9A) S2CON;      // 0000,0000 串口2控制寄存器
__sfr __at (0x9B) S2BUF;      // xxxx,xxxx 串口2数据寄存器
__sfr __at (0xAC) S3CON;      // 0000,0000 串口3控制寄存器
__sfr __at (0xAD) S3BUF;      // xxxx,xxxx 串口3数据寄存器
__sfr __at (0x84) S4CON;      // 0000,0000 串口4控制寄存器
__sfr __at (0x85) S4BUF;      // xxxx,xxxx 串口4数据寄存器
__sfr __at (0xA9) SADDR;      // 0000,0000 从机地址寄存器
__sfr __at (0xB9) SADEN;      // 0000,0000 从机地址屏蔽寄存器

// ADC 特殊功能寄存器
__sfr __at (0xBC) ADC_CONTR;  // 0000,0000 A/D转换控制寄存器
__sfr __at (0xBD) ADC_RES;    // 0000,0000 A/D转换结果高8位
__sfr __at (0xBE) ADC_RESL;   // 0000,0000 A/D转换结果低2位


// SPI 特殊功能寄存器
__sfr __at (0xCD) SPSTAT;   // 00xx,xxxx SPI状态寄存器
__sfr __at (0xCE) SPCTL;    // 0000,0100 SPI控制寄存器
__sfr __at (0xCF) SPDAT;    // 0000,0000 SPI数据寄存器

// IAP/ISP 特殊功能寄存器
__sfr __at (0xC2) IAP_DATA; // 0000,0000 EEPROM数据寄存器
__sfr __at (0xC3) IAP_ADDRH;// 0000,0000 EEPROM地址高字节
__sfr __at (0xC4) IAP_ADDRL;// 0000,0000 EEPROM地址低字节
__sfr __at (0xC5) IAP_CMD;  // xxxx,xx00 EEPROM命令寄存器
__sfr __at (0xC6) IAP_TRIG; // 0000,0000 EEPROM命令触发寄存器
__sfr __at (0xC7) IAP_CONTR;// 0000,x000 EEPROM控制寄存器

// PCA/PWM 特殊功能寄存器
__sfr __at (0xD8) CCON;     // 00xx,xx00 PCA控制寄存器
__sbit __at (0xDF) CF;      // CCON^7
__sbit __at (0xDE) CR;      // CCON^6
__sbit __at (0xDA) CCF2;    // CCON^2
__sbit __at (0xD9) CCF1;    // CCON^1
__sbit __at (0xD8) CCF0;    // CCON^0
__sfr __at (0xD9) CMOD;     // 0xxx,x000 PCA 工作模式寄存器
__sfr __at (0xE9) CL;       // 0000,0000 PCA计数器低字节
__sfr __at (0xF9) CH;       // 0000,0000 PCA计数器高字节
__sfr __at (0xDA) CCAPM0;   // 0000,0000 PCA模块0的PWM寄存器
__sfr __at (0xDB) CCAPM1;   // 0000,0000 PCA模块1的PWM寄存器
__sfr __at (0xDC) CCAPM2;   // 0000,0000 PCA模块2的PWM寄存器
__sfr __at (0xEA) CCAP0L;   // 0000,0000 PCA模块0的捕捉/比较寄存器低字节
__sfr __at (0xEB) CCAP1L;   // 0000,0000 PCA模块1的捕捉/比较寄存器低字节
__sfr __at (0xEC) CCAP2L;   // 0000,0000 PCA模块2的捕捉/比较寄存器低字节
__sfr __at (0xF2) PCA_PWM0; // xxxx,xx00 PCA模块0的PWM寄存器
__sfr __at (0xF3) PCA_PWM1; // xxxx,xx00 PCA模块1的PWM寄存器
__sfr __at (0xF4) PCA_PWM2; // xxxx,xx00 PCA模块2的PWM寄存器
__sfr __at (0xFA) CCAP0H;   // 0000,0000 PCA模块0的捕捉/比较寄存器高字节
__sfr __at (0xFB) CCAP1H;   // 0000,0000 PCA模块1的捕捉/比较寄存器高字节
__sfr __at (0xFC) CCAP2H;   // 0000,0000 PCA模块2的捕捉/比较寄存器高字节


/////////////////////////////////////////////////

#endif

