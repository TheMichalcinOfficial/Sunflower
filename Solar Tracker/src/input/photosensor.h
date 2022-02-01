#pragma once

// Local includes
#include "sensor.h"
#include "../config.h"

namespace Input
{
    /////////////////// Classes ///////////////////

    class Photosensor : public AnalogSensor
    {
    // Constructor
    public:
        Photosensor() = default;

    // Methods
    public:
        // Getters

        byte lightAsPercentage() const
        {
            return map(this->getReading(), 0, 1023, 0, 100);
        }
    };

    extern Photosensor photoA, photoB, photoC, photoD;

    ////////////////// Functions //////////////////

    void logLightReadings()
    {
    #ifdef LOG_LIGHT_READINGS
        Serial.print(photoA.lightAsPercentage()); Serial.print(" ");
        Serial.print(photoB.lightAsPercentage()); Serial.print(" ");
        Serial.print(photoC.lightAsPercentage()); Serial.print(" ");
        Serial.println(photoD.lightAsPercentage());
    #endif
    }
}
