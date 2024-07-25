#include "timer.h"

volatile uint16_t sysTickCount = 0;

/**
 * @brief 初始化定时器1
 *
 * 初始化定时器1，并设置其为10毫秒的计时周期（基于24.000MHz的时钟频率）。
 *
 * 定时器模式设置为12T模式，并设置初始定时值。
 * 清除TF1标志，并启动定时器1。
 * 同时使能定时器1的中断。
 */
void timer1_init(void) {
    //10毫秒@24.000MHz
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE0;		//设置定时初始值
	TH1 = 0xB1;		//设置定时初始值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时

    ET1 = 1;      // 使能定时器1中断
}

/**
 * @brief 定时器1中断服务程序
 *
 * 当定时器1触发中断时，此函数将被调用，用于累加时间计数器。
 *
 * 注意：此函数作为中断服务程序，在中断发生时自动执行，无需显式调用。
 */
void timer1_ISR(void) __interrupt(3) __using (1) {
    sysTickCount++;  // 累加时间计数器 间隔10ms
}