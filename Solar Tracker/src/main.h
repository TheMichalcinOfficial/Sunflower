#pragma once

// Library includes

#include <Arduino.h>
#include <Servo.h>

// Local includes

#include "config.h"
#include "pins/pins.h"
#include "input/photosensor.h"

#ifdef SENSITIVITY_INPUT_PIN
    #define HAS_SENSITIVITY_SETTING
#endif

#ifdef MODE_SWITCH_PIN
    #define HAS_MODE_SWITCH
#endif

#ifndef X_ERROR_MARGIN
    #define X_ERROR_MARGIN ERROR_MARGIN
#endif

#ifndef Y_ERROR_MARGIN
    #define Y_ERROR_MARGIN ERROR_MARGIN
#endif

namespace Utils
{
    template <typename T>
    inline T constrainInRange(const T& x, const T& low, const T& high)
    {
        return x < low ? low : x > high ? high : x;
    }
}
