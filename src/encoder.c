#include "encoder.h"

// 全局变量，用于存储编码器状态和按键状态
volatile signed char encoder_state = 0;
volatile unsigned char button_state = 0;
volatile unsigned int button_press_time = 0;
volatile bit long_press_detected = 0; // 标记长按是否已触发

/**
 * @brief 编码器扫描函数
 *
 * 扫描编码器状态，并根据A、B相的状态判断旋转方向和角度，并更新编码器状态。
 */
void encoder_scan(void) {
    static bit last_A = 1; // 上一次A相的状态
    static bit last_B = 1; // 上一次B相的状态

    if (last_A == 1) {
        if (IO_ENCODER_A == 0) {
            // INT0=0(下降沿Falling) 编码器 ON
            // 编码器从高电平变为低电平（下降沿），编码器开始工作
            last_B = IO_ENCODER_B; // 保存当前B端口状态
            // if (IO_ENCODER_B) {
            //     // B相为高电平时
            //     LOG("B high\n");
            // } else {
            //     // B相为低电平时
            //     LOG("B low\n");
            // }
        }
    } else {
        // INT0=1(上升沿Rising) 编码器 OFF
        // 编码器从低电平变为高电平（上升沿），编码器停止工作
        if (IO_ENCODER_A == 1) {
            // 打印当前A、B相状态以及上一次A、B相状态
            // LOG("%d %d %d %d\n", current_A, IO_ENCODER_B, last_A, last_B);
            if (IO_ENCODER_B) {
                // 如果当前B相为高电平，且上一次B相为低电平，则表示编码器顺时针旋转
                if (last_B == 0) {
                    encoder_state++; // 顺时针旋转
                    // LOG("es %d\n", encoder_state);
                }
            } else {
                // 如果当前B相为低电平，且上一次B相为高电平，则表示编码器逆时针旋转
                if (last_B) {
                    encoder_state--; // 逆时针旋转
                    // LOG("es %d\n", encoder_state);
                }
            }
        }
    }
    last_A = IO_ENCODER_A; // 保存当前A相的状态
}

/**
 * @brief 扫描按键状态
 *
 * 扫描按键状态，根据按键的按下、持续按下和释放来更新内部状态和计数器。
 */
void button_scan(void) {
    static bit last_S = 1; // 上一次按键的状态

    // 检测按键按下
    if (IO_ENCODER_S == 0 && last_S == 1) {
        button_press_time = 0; // 重置按键按下时间
        long_press_detected = 0; // 重置长按标记
    } 
    // 检测按键持续按下
    else if (IO_ENCODER_S == 0 && last_S == 0) {
        button_press_time++; // 增加按键按下时间
        if (button_press_time > 1000 && !long_press_detected) {
            button_state = 2; // 长按
            long_press_detected = 1; // 标记长按已触发
        }
    } 
    // 检测按键释放
    else if (IO_ENCODER_S == 1 && last_S == 0) {
        if (button_press_time <= 1000) {
            button_state = 1; // 短按
        }
        button_press_time = 0; // 重置按键按下时间
    }
    last_S = IO_ENCODER_S; // 更新按键状态
}

/*
#include "encoder.h"

void main() {
    while (1) {
        encoder_scan(); // 扫描编码器
        button_scan(); // 扫描按键
        delay_ms(1); // 延时1毫秒

        // 测试代码
        if (encoder_state != 0) {
            if (encoder_state > 0) {
                // 右旋
                P1 = 0x01; // 假设P1连接到LED，用于指示右旋
            } else {
                // 左旋
                P1 = 0x02; // 假设P1连接到LED，用于指示左旋
            }
            encoder_state = 0; // 重置状态
        }

        if (button_state != 0) {
            if (button_state == 1) {
                // 短按
                P1 = 0x04; // 假设P1连接到LED，用于指示短按
            } else if (button_state == 2) {
                // 长按
                P1 = 0x08; // 假设P1连接到LED，用于指示长按
            }
            button_state = 0; // 重置状态
        }
    }
}

*/