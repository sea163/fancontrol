#include "delay.h"

void Delay1ms(void)		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 24;
	j = 84;
	do
	{
		while (--j);
	} while (--i);
}

/**
 * @brief 延迟函数（毫秒级）
 *
 * 根据传入的毫秒数（ms）进行延迟。
 *
 * @param ms 延迟的毫秒数
 */
void delay_ms(uint8_t ms) {
    uint8_t i;
    for (i = 0; i < ms; i++) {
        Delay1ms();
    }
}