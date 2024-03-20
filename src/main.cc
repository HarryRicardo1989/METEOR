
#include "esp_init.hpp"
#include "connections.h"

/*******DEV-LIB-THINGS**********/
#include "ADC_control/adc.hpp"
/**********************/

extern "C"
{
    void app_main(void);
}

void app_main()
{
    TOUCH::TouchPad touch_button(TOUCH_PAD_NUM0, read_nvs_uint32_var(WAKEUP_TOUCH_TRESHOLD));
    init();
    init_i2c();
    create_sleep_timer(40);

    if (read_nvs_int8_var(UPDATE_STATUS))
    {
        ESP_LOGW("OTA-STATUS", "UpdateStatus true");
        otaInit();
        while (true)
        {
            vTaskDelay(5 * PORT_TICK_PERIOD_SECONDS);
        }
    }

    switch (wakeup_cause())
    {
    case WAKEUP_TOUCHPAD:
        ESP_LOGW("ESP-WAKE-UP", "FROM Touch");
        // esp_init_from_touch(&touch_button);
        esp_init_from_timer();

        create_sleep_timer(0);

        break;
    case WAKEUP_TIMER:
        ESP_LOGW("ESP-WAKE-UP", "FROM TIMER");
        esp_init_from_timer();

        create_sleep_timer(0);
        break;
    case WAKEUP_BT:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_BT");
        create_sleep_timer(0);
        break;
    case WAKEUP_EXT0:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_EXT0");
        create_sleep_timer(0);
        break;
    case WAKEUP_EXT1:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_EXT1");
        create_sleep_timer(0);
        break;
    case WAKEUP_ULP:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_ULP");
        create_sleep_timer(0);
        break;
    case WAKEUP_GPIO:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_GPIO");
        create_sleep_timer(0);
        break;
    case WAKEUP_UART:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_UART");
        create_sleep_timer(0);
        break;
    case WAKEUP_WIFI:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_WIFI");
        create_sleep_timer(0);
        break;
    case WAKEUP_COCPU:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_COCPU");
        create_sleep_timer(0);
        break;
    case WAKEUP_ALL:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_ALL");
        create_sleep_timer(0);
        break;
    case WAKEUP_UNDEFINED:
        ESP_LOGW("ESP-WAKE-UP", "WAKEUP_UNDEFINED");
        save_nvs_string_var(MODEL, DEFAULT_MODEL);
        save_nvs_u32_var(WAKEUP_TOUCH_TRESHOLD, 1300);
        save_nvs_u32_var(TIME_TO_WAKE_UP, 40);
        save_nvs_int8_var(UPDATE_STATUS, false);
        create_sleep_timer(0);
        break;

    default:
        ESP_LOGW("ESP-WAKE-UP", "RESET ERROR %d", wakeup_cause());

        create_sleep_timer(0);

        break;
    }
    while (true)
    {

        vTaskDelay(5 * PORT_TICK_PERIOD_SECONDS);
    }
}