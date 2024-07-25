#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "config.h"
#include "soft_uart.h"
#include "delay.h"
#include "encoder.h"
#include "timer.h"
#include "iapEeprom.h"


//系统参数用于保存到eeprom
typedef struct
{
    uint8_t dutyCycle; // 当前占空比
} SysConfig;

void init_IO(void);
void timer0_Init(void);
void setPWM(uint8_t dutyCycle, bool bCoolingFan);
void saveConfig(void);
void loadConfig(void);
uint8_t updateDutyCycle(void);

#endif // MAIN_H_INCLUDED