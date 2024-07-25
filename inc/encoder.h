#ifndef ENCODER_H
#define ENCODER_H

#include "config.h"
#include "delay.h"
#include "soft_uart.h"

extern volatile signed char encoder_state;
extern volatile unsigned char button_state;
extern volatile unsigned int button_press_time;

void encoder_scan(void);
void button_scan(void);

#endif // ENCODER_H
