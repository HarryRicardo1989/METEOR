/**
 * @file gpio_map.h
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief map of all used GPIO in project
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "driver/gpio.h"
#include "driver/ledc.h"

// #define SDA_PIN GPIO_NUM_18
#define SDA_PIN GPIO_NUM_8
// #define SCL_PIN GPIO_NUM_19
#define SCL_PIN GPIO_NUM_7
#define CHARGING GPIO_NUM_32
#define CHARGED GPIO_NUM_33

#define RGB_LED_RED_GPIO GPIO_NUM_14
#define RGB_LED_GREEN_GPIO GPIO_NUM_12
#define RGB_LED_BLUE_GPIO GPIO_NUM_13

#define LED_DUTY_RESOLUTION LEDC_TIMER_12_BIT
#define I2C_CLK_SPEED_HZ 400000

/**
 * LEDC_TIMER_8_BIT = 255
 * LEDC_TIMER_9_BIT = 512
 * LEDC_TIMER_10_BIT = 1024
 * LEDC_TIMER_12_BIT = 4096
 * LEDC_TIMER_13_BIT = 8192
 * LEDC_TIMER_14_BIT = 16384
 */