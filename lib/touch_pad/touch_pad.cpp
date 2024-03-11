/**
 * @file touch_pad.cpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief  Class to prepare Touch pad to wakeup MCU from deep sleep
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "touch_pad.hpp"

namespace TOUCH
{
    TouchPad::TouchPad(touch_pad_t touch_pad_num, uint16_t threshold)
    {

        c_touch_pad_num = touch_pad_num;
        ESP_ERROR_CHECK(touch_pad_init());
        touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
        touch_pad_set_voltage(TOUCH_HVOLT_2V4, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
        touch_pad_config(c_touch_pad_num, threshold);
    }
    int TouchPad::touch_read()
    {
        uint16_t touch_value;
        touch_pad_read(c_touch_pad_num, &touch_value);
        return touch_value;
    }
}