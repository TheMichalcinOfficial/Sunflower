#pragma once

// Choose control board layout
#define BOARD_LAYOUT ARDUINO_NANO_SOLAR_SHIELD

// Servos

#define ANGLE_STEP 1			// Dergrees
#define X_MIN_ANGLE 0           // Degrees
#define X_MAX_ANGLE 180           // Degrees
#define Y_MIN_ANGLE 90           // Degrees
#define Y_MAX_ANGLE 165          // Degrees

// Photoresistor settings

#define DARKNESS_THRESHOLD 25	// % of sunlight
#define PHOTORESISTOR_A_PIN A0
#define PHOTORESISTOR_B_PIN A1
#define PHOTORESISTOR_C_PIN A2
#define PHOTORESISTOR_D_PIN A3

// Tracking
#define ERROR_MARGIN 1                  // %
//#define INDIVIDUAL_ERROR_MARGINS
#ifdef INDIVIDUAL_ERROR_MARGINS
    #define X_ERROR_MARGIN 1            // %
    #define Y_ERROR_MARGIN 1            // %
#endif

// Debuging

#define DEBUG_LOGGING
#ifdef DEBUG_LOGGING
    #define LOG_ANGLES

    #define LOG_LIGHT_READINGS
    #ifdef LOG_LIGHT_READINGS
        // #define LOG_INDIVIDUAL_SENSORS
    #endif
#endif
