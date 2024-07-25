/*************************************
 * 
 *        BL2717 无刷电机风扇控制
 * 
 * CPU: STC15F104E
 * FREQ: 11.0592MHz
 * FLASH:4K RAM:128 定时器:2 看门狗:有 
 * 
 * ***********************************
*/

#include "main.h"

// 中断服务程序需要在 main 函数所在文件中声明。如果中断服务程序定义在其他文件中，需要在 main.c 文件中进行声明。
void timer1_ISR(void) __interrupt(3) __using (1);
void timer0_ISR(void) __interrupt(1) __using (2);

// 系统时钟计数器
volatile uint16_t lastTickCount = 0;

// PWM 输出频率 18KHz
volatile uint16_t pwmHighTime, pwmLowTime; // 高电平时间和低电平时间

// 当前设置
volatile SysConfig config;
volatile bool needSave = false;
volatile uint16_t saveDelayCounter = 0;

// 模拟自然风
volatile uint8_t minDutyCycle = 20;
volatile uint8_t maxDutyCycle = 60;

// 预先计算的正弦波查找表，范围从0到255
const uint8_t sineTable[256] = {
    128, 131, 134, 137, 140, 143, 146, 149, 152, 155, 158, 161, 164, 167, 170, 173,
    176, 179, 182, 185, 188, 191, 194, 197, 200, 203, 206, 209, 212, 215, 218, 221,
    224, 227, 230, 233, 236, 239, 242, 245, 248, 251, 254, 255, 254, 251, 248, 245,
    242, 239, 236, 233, 230, 227, 224, 221, 218, 215, 212, 209, 206, 203, 200, 197,
    194, 191, 188, 185, 182, 179, 176, 173, 170, 167, 164, 161, 158, 155, 152, 149,
    146, 143, 140, 137, 134, 131, 128, 125, 122, 119, 116, 113, 110, 107, 104, 101,
    98, 95, 92, 89, 86, 83, 80, 77, 74, 71, 68, 65, 62, 59, 56, 53, 50, 47, 44, 41,
    38, 35, 32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2, 1, 2, 5, 8, 11, 14, 17, 20, 23,
    26, 29, 32, 35, 38, 41, 44, 47, 50, 53, 56, 59, 62, 65, 68, 71, 74, 77, 80, 83,
    86, 89, 92, 95, 98, 101, 104, 107, 110, 113, 116, 119, 122, 125
};

void main(void)
{
    bool isPowerOn = false; //风扇软开关
    bool isNaturalWind = false; // 自然风
    uint8_t lastdutyCycle=0;

    delay_ms(250); // 延时250毫秒，等待系统稳定
    delay_ms(250);
    delay_ms(250);
    delay_ms(250);

    loadConfig(); // 加载配置
    if (config.dutyCycle > 100) config.dutyCycle = 100; // 修正异常值
    LOG("dutyCycle %d\n", config.dutyCycle);
    // config.dutyCycle = 50;
    // saveConfig();
    // while (1) {
    // }
    
    init_IO();
    timer1_init(); // 10ms 中断一次

    //PWM 初始化, 初始化后不输出PWM 默认IO为高电平
    timer0_Init();  // 周期 = 1 / 18000 Hz ≈ 55.56 μs
    
    EA = 1;       // 使能全局中断

    while (1) {
        encoder_scan(); // 扫描编码器
        button_scan(); // 扫描按键
        delay_ms(1); // 延时1毫秒

        // 编码器处理
        if (encoder_state != 0) {
            if (isPowerOn == true && isNaturalWind == false){ // 风扇软开关
                if (encoder_state > 0) {
                    // 右旋
                    config.dutyCycle = config.dutyCycle + 2;
                    if (config.dutyCycle > 100) {
                        config.dutyCycle = 100;
                    }
                    LOG("right\n");
                } else {
                    // 左旋
                    config.dutyCycle = config.dutyCycle - 2;
                    if (config.dutyCycle < 10) {
                        config.dutyCycle = 10;
                    }
                    LOG("left\n");
                }
                setPWM( config.dutyCycle, true);
                needSave = true; // 设置需要保存并延迟10秒
                saveDelayCounter = sysTickCount;
            }
            encoder_state = 0; // 重置状态
        }

        // 按键处理
        if (button_state != 0) {
            if (button_state == 1) {
                // 短按
                // P1 = 0x04; // 假设P1连接到LED，用于指示短按
                LOG("short key\n");
                // LOG("tickCount %d\n", sysTickCount);
                if (isPowerOn == false) {
                    setPWM(config.dutyCycle, true);
                    isPowerOn = true;
                    LOG("pwoer on\n");
                } else {
                    isPowerOn = false; 
                    isNaturalWind = false;
                    setPWM(0, true);
                    LOG("pwoer off\n");
                }
            } else if (button_state == 2) {
                // 长按
                // P1 = 0x08; // 假设P1连接到LED，用于指示长按
                LOG("long key\n");
                if (isPowerOn == true){ // 开启关闭自然风
                    if (isNaturalWind == true){
                        isNaturalWind = false;
                        setPWM(config.dutyCycle, true); // 恢复占空比
                    }else{
                        isNaturalWind = true;
                        setPWM(20, false);
                        COOL_FAN_ON(); // 自然风模式, 打开冷却风扇
                    }
                }
            }
            button_state = 0; // 重置状态
        }

        // 定时器处理 10ms计数一次,655.35 秒, 约 10.92 分钟回绕一次
        #ifdef DEBUG
            if (sysTickCount - lastTickCount > 100 * 10) {
                lastTickCount = sysTickCount; // 更新计数器
                LOG("timer 10s\n");
            }
        #endif
        
        // 需要保存配置, 延迟10秒执行
        if (needSave == true && (sysTickCount - saveDelayCounter) > (100 * 10)) {
            LOG("saveConfig...\n");
            saveConfig();
            needSave = false;
            saveDelayCounter = 0;
        }

        // led 闪烁
        if (isPowerOn == true) {
            if (config.dutyCycle == 100) {
                LED_ON();
            } else if (config.dutyCycle == 0) {
                LED_OFF();
            } else {
                if (isNaturalWind == true){
                    // 模拟自然风
                    if (sysTickCount % (100 - lastdutyCycle) == 0) {
                        IO_LED = !IO_LED;
                    } 
                }else{
                    // 固定占空比
                    if (sysTickCount % (100 - config.dutyCycle) == 0) {
                        IO_LED = !IO_LED;
                    }
                }
            }
        }else{
            LED_OFF();
        }

        // 模拟自然风, 每300ms更新一次占空比
        if (isNaturalWind == true && sysTickCount % 30 == 0) {
            uint8_t dutyCycle = updateDutyCycle();
            if (lastdutyCycle != dutyCycle) {
                setPWM( dutyCycle, false);
                lastdutyCycle = dutyCycle;
            }
        }

        FeedDog(); // 喂狗
    } // end while
}

/**
 * @brief 保存配置
 *
 * 将配置信息保存到指定的扇区。
 *
 * 注意：在保存配置时，会先关闭中断，以防止在写入过程中被其他中断打断。
 * 写入完成后，会重新打开中断。
 */
void saveConfig(void) {
    EA = 0;
    //擦除扇区
    IAPCommand( IAP_SECTOR_ERASE, IAP_ADDRESS, 0); //第一扇区
    IAPBufCommand( IAP_BYTE_PROGRAM, IAP_ADDRESS, (uint8_t*)&config, sizeof(SysConfig));
    EA = 1;
}

/**
 * @brief 加载配置
 *
 * 从指定地址加载系统配置到 config 结构体中。
 *
 * @note 使用IAP（In-Application Programming）机制进行配置读取。
 */
void loadConfig(void) {
    IAPBufCommand( IAP_BYTE_READ, IAP_ADDRESS, (uint8_t*)&config, sizeof(SysConfig));
}

/**
 * @brief 初始化IO端口
 *
 * 初始化指定的IO端口，将其配置为指定的模式。
 * 包括：
 * - IO_COOL_FAN_CTRL (P30) 设置为推挽输出
 * - IO_LED (P31) 设置为准双向口
 * - IO_ENCODER_B (P32) 设置为仅为输入
 * - IO_ENCODER_A (P33) 设置为仅为输入
 * - IO_ENCODER_S (P34) 设置为仅为输入
 * - IO_FAN_PWM (P35) 设置为推挽输出
 */
void init_IO(void)
{
    // IO_COOL_FAN_CTRL P30 设置为推挽输出
    // IO_LED P31 设置为准双向口
    // IO_ENCODER_B P32 设置为仅为输入
    // IO_ENCODER_A P33 设置为仅为输入
    // IO_ENCODER_S P34 设置为仅为输入
    // IO_FAN_PWM P35 设置为推挽输出

    /*
    // 设置 P3_0 为推挽输出
    P3M1 &= ~(1 << 0); // 清除 P3_0 的 M1 位
    P3M0 |= (1 << 0);  // 设置 P3_0 的 M0 位

    // 设置 P3_1 为准双向口
    P3M1 &= ~(1 << 1); // 清除 P3_1 的 M1 位
    P3M0 &= ~(1 << 1); // 清除 P3_1 的 M0 位

    // 设置 P3_2 为仅输入
    P3M1 |= (1 << 2);  // 设置 P3_2 的 M1 位
    P3M0 &= ~(1 << 2); // 清除 P3_2 的 M0 位

    // 设置 P3_3 为仅输入
    P3M1 |= (1 << 3);  // 设置 P3_3 的 M1 位
    P3M0 &= ~(1 << 3); // 清除 P3_3 的 M0 位

    // 设置 P3_4 为仅输入
    P3M1 |= (1 << 4);  // 设置 P3_4 的 M1 位
    P3M0 &= ~(1 << 4); // 清除 P3_4 的 M0 位

    // 设置 P3_5 为推挽输出
    P3M1 &= ~(1 << 5); // 清除 P3_5 的 M1 位
    P3M0 |= (1 << 5);  // 设置 P3_5 的 M0 位
    */

    COOL_FAN_OFF(); // 关闭冷却风扇
    FAN_PWM_OFF(); // 设置端口输出高电平 启动时关闭风扇

    // 设置 P3M1 和 P3M0 寄存器
    P3M1 = 0x1C; // 0001 1100, 设置 P3_2, P3_3, P3_4 为仅输入
    P3M0 = 0x21; // 0010 0001, 设置 P3_0, P3_5 为推挽输出，P3_1 为准双向口
}


/**
 * @brief 初始化定时器0
 *
 * 初始化定时器0，设置其工作模式和初始值，并启动定时器0进行计时。
 * 同时使能定时器0中断。
 */
void timer0_Init(void) {
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式

	//设置定时初始值
    TH0 = TIMER0_RELOAD >> 8;
    TL0 = TIMER0_RELOAD & 0xFF;

	TF0 = 0;		//清除TF0标志
	// TR0 = 1;		//定时器0开始计时

    PT0 = 1;		//高优先级中断
    ET0 = 1;  // 使能定时器0中断
}


/**
 * @brief 设置PWM占空比
 *
 * 根据给定的占空比和是否控制散热风扇，设置PWM输出。
 *
 * @param dutyCycle 占空比，范围在0到100之间
 * @param bCoolingFan 是否控制散热风扇，true表示控制，false表示不控制
 */
void setPWM(uint8_t dutyCycle, bool bCoolingFan) {
    LOG("setPWM %d\n", dutyCycle);
    if (dutyCycle > 100) dutyCycle = 100;

    #ifndef DEBUG
        // 无刷电机散热风扇控制
        if (bCoolingFan) {
            if (dutyCycle > 30) {
                COOL_FAN_ON(); // 打开冷却风扇
            } else {
                COOL_FAN_OFF(); // 关闭冷却风扇
            }
        }
    #endif
    
    if (dutyCycle == 100) {
        TIMER0_OFF();
        FAN_PWM_ON();  // 设置端口输出低电平
    } else if (dutyCycle == 0) {
        TIMER0_OFF();
        FAN_PWM_OFF();  // 设置端口输出高电平
    } else {
        dutyCycle = 100 - dutyCycle; // 如果需要反转占空比，保留此行代码
        pwmHighTime = (TIMER0_RELOAD_CALC * dutyCycle) / 100;
        pwmLowTime = TIMER0_RELOAD_CALC - pwmHighTime;
        LOG("L %d H %d\n", pwmLowTime, pwmHighTime);
        pwmHighTime = 65536 - pwmHighTime;
        pwmLowTime = 65536 - pwmLowTime;
        TIMER0_ON();
    }
}

void timer0_ISR(void) __interrupt(1) __using (2) {
    static bit pwmState = 0;

    if (pwmState) {
        TH0 = pwmLowTime >> 8;
        TL0 = pwmLowTime & 0xFF;
        IO_FAN_PWM = 0; // 设置P1.0引脚为低电平
    } else {
        TH0 = pwmHighTime >> 8;
        TL0 = pwmHighTime & 0xFF;
        IO_FAN_PWM = 1; // 设置P1.0引脚为高电平
    }
    pwmState = !pwmState;
}

/**
 * @brief 更新占空比
 *
 * 根据正弦波生成一个占空比值，并在每个正弦波周期后更新最大和最小占空比。
 *
 * @return 当前计算出的占空比值（0-255）
 */
uint8_t updateDutyCycle(void) {
    static uint8_t angle = 0;
    // float sineValue = (sinf(angle * PI / 180.0) + 1) / 2; // 生成0到1之间的正弦波
    uint8_t sineValue = sineTable[angle]; // 从查找表中获取正弦值
    uint8_t dutyCycle = minDutyCycle + (uint8_t)((sineValue * (maxDutyCycle - minDutyCycle)) / 255); // 映射到minDutyCycle到maxDutyCycle之间

    LOG("a %d n %d\n", angle, dutyCycle);
    angle = (angle + 1) % 256; // 角度范围0到255

    if (angle == 0) { // 每完成一个正弦波周期后更新最大和最小占空比
        minDutyCycle = 20 + rand() % 11; // 生成20到30之间的随机值
        maxDutyCycle = 50 + rand() % 11; // 生成50到60之间的随机值
        LOG("min %d max %d\n", minDutyCycle, maxDutyCycle);
    }

    return dutyCycle;
}