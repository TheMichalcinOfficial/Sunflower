#pragma once

// Board info

#ifndef BOARD_NAME
#define BOARD_NAME "Arduino Nano Solar Shield"
#endif

// LEDs

#ifndef ERR_LED_PIN
    #define ERR_LED_PIN 2
#endif
#ifndef OK_LED_PIN
    #define OK_LED_PIN 3
#endif

// Photoresistors

#define PR_A_PIN A0
#define PR_B_PIN A1
#define PR_C_PIN A2
#define PR_D_PIN A3

// Servos

#define X_SERVO_PIN 8
#define Y_SERVO_PIN 9
#define Z_SERVO_PIN -1

// Input

// #define SENSITIVITY_INPUT_PIN -1
// #define MODE_SWITCH_PIN -1
