#pragma once

// Local includes

#include "..\config.h"

// Boards list

#define ARDUINO_NANO_SOLAR_SHIELD 1
#define CUSTOM_SETUP 999

// Pins configuration selection

#if BOARD_LAYOUT == ARDUINO_NANO_SOLAR_SHIELD
    #include "pins_Arduino_Nano_Solar_Shield.h"
#elif BOARD_LAYOUT == CUSTOM_SETUP
    #include "pins_CUSTOM.h"
#else
    #error "Unknown board layout selected!"
#endif
