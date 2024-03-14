/**
 * @file sleep_timer.c
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief  lib to controll the timer to go to deep sleep mode
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "tasks_common.h"
#include "gpio_map.h"
#include "rgb_led.h"
#include "blink_color.h"

#include "sleep_timer.h"
#include "driver/rtc_io.h"
#include "stdio.h"
#include "rw_data.h"
#include "esp_sleep.h"
#include "esp_cleanup.h"

TaskHandle_t task_sleep_timer_handle = NULL;

int tSleep_timer_time_s = 30;
bool is_counting = false;

void create_sleep_timer(int sleep_timer_time_s)
{
    if (is_counting == true)
    {
        delete_sleep_timer();
    }
    tSleep_timer_time_s = sleep_timer_time_s;

    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_AUTO);
    esp_sleep_enable_touchpad_wakeup();
    esp_sleep_enable_timer_wakeup(read_nvs_uint32_var(TIME_TO_WAKE_UP) * SECONDS);
    printf("criou novo timer %d segundos \n", tSleep_timer_time_s);
    if (tSleep_timer_time_s == 0)
    {
        init_sleep();
    }

    xTaskCreate(vTask_sleep_timer, "TASK SLEEP TIMER", VTASK_STACK_SIZE_SLEEP_TIMER, NULL, VTASK_PRIORITY_SLEEP_TIMER, &task_sleep_timer_handle);
}

void vTask_sleep_timer(void *pvParameters)
{
    is_counting = true;
    while (true)
    {
        vTaskDelay(tSleep_timer_time_s * 1000 / portTICK_PERIOD_MS);
        init_sleep();
    }
}

void delete_sleep_timer(void)
{
    if (is_counting == true)
    {
        is_counting = false;
        vTaskDelete(task_sleep_timer_handle);
        printf("apagou timer de %d segundos \n", tSleep_timer_time_s);
    }
    else
    {
        ESP_LOGI("SLEEP_TIMER", "is not counting");
    }
}
void init_sleep(void)
{
    blink_color_stop();
    blink_led_dual_collor(GO_SLEEP_COLOR0, GO_SLEEP_TIMING0, GO_SLEEP_COLOR1, GO_SLEEP_TIMING1);
    cleanup();
    isolate_gpio();

    printf("\n\nsleeping\n\n");
    esp_deep_sleep_start();
}

void isolate_gpio(void)
{
    rtc_gpio_isolate(RGB_LED_GREEN_GPIO);
    rtc_gpio_isolate(RGB_LED_RED_GPIO);
    rtc_gpio_isolate(RGB_LED_BLUE_GPIO);
}
void deisolate_gpio(void)
{
    rtc_gpio_hold_dis(RGB_LED_GREEN_GPIO);
    rtc_gpio_hold_dis(RGB_LED_RED_GPIO);
    rtc_gpio_hold_dis(RGB_LED_BLUE_GPIO);
}

wakeup_cause_name wakeup_cause()
{
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();

    switch (cause)
    {
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        return WAKEUP_TOUCHPAD;
    case ESP_SLEEP_WAKEUP_TIMER:
        return WAKEUP_TIMER;
    case ESP_SLEEP_WAKEUP_ULP:
        return WAKEUP_ULP;
    case ESP_SLEEP_WAKEUP_GPIO:
        return WAKEUP_GPIO;
    case ESP_SLEEP_WAKEUP_UART:
        return WAKEUP_UART;
    case ESP_SLEEP_WAKEUP_WIFI:
        return WAKEUP_WIFI;
    case ESP_SLEEP_WAKEUP_BT:
        return WAKEUP_BT;
    case ESP_SLEEP_WAKEUP_COCPU:
        return WAKEUP_COCPU;
    case ESP_SLEEP_WAKEUP_ALL:
        return WAKEUP_ALL;
    default:
        return WAKEUP_UNDEFINED;
    }
}
