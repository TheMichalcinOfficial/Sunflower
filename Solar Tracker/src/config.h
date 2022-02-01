#pragma once

// Choose control board layout
#define BOARD_LAYOUT ARDUINO_NANO_SOLAR_SHIELD

// Servos

#define ANGLE_STEP 1			// Dergrees
#define X_MIN_ANGLE 0           // Degrees
#define X_MAX_ANGLE 180           // Degrees
#define Y_MIN_ANGLE 90           // Degrees
#define Y_MAX_ANGLE 180           // Degrees

// Photoresistor settings

#define DARKNESS_THRESHOLD 25	// % of sunlight

// Debuging

#define LOG_ANGLES
