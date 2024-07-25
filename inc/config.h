#ifndef _H_STC15_CONF
#define _H_STC15_CONF

#include <compiler.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stc15f104e.H"

typedef unsigned char u8;
typedef unsigned int u16;

#ifndef MAIN_Fosc
    #define MAIN_Fosc 24000000L // 系统时钟频率 24.000MHz
#endif

#ifndef MCU_Type
    #define MCU_Type STC15F104E //4K 1K
#endif

#define MainFosc_KHZ (MAIN_Fosc / 1000)

#ifndef _nop_
#define _nop_() __asm__ ("nop");
#endif

/********** 看门狗定义 **********/
//看门狗定义
//The WDT period is determined by the following equation	看门狗溢出时间计算
//看门狗溢出时间	=（ 12 x Pre-scale x 32768) / Oscillator frequency
//12M 时
//看门狗溢出时间	=	(12 × Pre-scale × 32768) / 12000000 = Pre-scale× 393216 / 12000000
//256分频 约4.045s
#define FeedDog() WDT_CONTR = 0x3F

// IO 端口设置
#define IO_COOL_FAN_CTRL P30
#define COOL_FAN_ON() IO_COOL_FAN_CTRL = 1
#define COOL_FAN_OFF() IO_COOL_FAN_CTRL = 0

#define IO_LED P31
#define LED_ON() IO_LED = 0
#define LED_OFF() IO_LED = 1

// EC11 编码器
#define IO_ENCODER_B P32
#define IO_ENCODER_A P33
#define IO_ENCODER_S P34

#define IO_FAN_PWM P35
#define FAN_PWM_ON() IO_FAN_PWM = 0
#define FAN_PWM_OFF() IO_FAN_PWM = 1

// PWM 输出设置 18KHz
#define PWM_FREQ 18000L  // PWM频率
#define TIMER0_RELOAD (65536 - (MAIN_Fosc / PWM_FREQ)) // 定时器0重装载值 1T 模式 约 1333 个时钟周期
#define TIMER0_RELOAD_CALC (MAIN_Fosc / PWM_FREQ) // 定时器0重装载值 1T 模式 约 1333 个时钟周期
// #define FAN_PWM_CYCLE 252

#define TIMER0_ON() TR0 = 1
#define TIMER0_OFF() TR0 = 0

#endif