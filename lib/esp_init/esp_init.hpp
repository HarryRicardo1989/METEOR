#pragma once

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "nvs_flash.h"
#include <sstream>
#include <iomanip> // Para std::setprecision
#include <cstring> // Para strcpy
#include "tasks_common.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_log.h"
#include "sleep_timer.h"
#include "touch_pad.hpp"
#include "esp_mac.h"
#include "rgb_led.hpp"
#include "blink_color.h"
#include "connections.h"
#include "WIFI/wifi_manager.hpp"
#include "MQTT/MqttClient.hpp"
#include "MQTT/MqttPublish.hpp"
#include "MQTT/MqttInit.hpp"
#include "gpio_map.h"
#include "I2C/cppi2c.h"
#include "bme280/bme280_common.hpp"
#include "battery.hpp"
#include "OTA/OtaUpdate.hpp"

void esp_init_from_touch(TOUCH::TouchPad *touch);
void esp_init_from_timer();
void generate_client_ID();
void scanI2CDevices(int sdaPin, int sclPin);
char *convert_value_to_string(int value);
char *convert_float_to_string(float value);
void battery_things();
void init_i2c();
void tryConnectToWiFi();
void display_meteor(float temperature, float pressure, int humidity, float i2cDewPoint, int battery_level, u_int32_t battery_voltage);
void otaInit();