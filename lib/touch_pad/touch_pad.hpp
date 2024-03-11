/**
 * @file touch_pad.hpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief Class to prepare Touch pad to wakeup MCU from deep sleep
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "driver/touch_pad.h"
#include "tasks_common.h"

#define TOUCHPAD_NUM TOUCH_PAD_NUM0

namespace TOUCH
{
    class TouchPad
    {
    private:
        touch_pad_t c_touch_pad_num;

    public:
        TouchPad(touch_pad_t touch_pad_num, uint16_t threshold);
        int touch_read();
    };
}