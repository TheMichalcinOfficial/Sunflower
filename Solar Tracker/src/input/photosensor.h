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

    unsigned int sumLightReadings()
    {
        return photoA.getReading() + photoB.getReading() + photoC.getReading() + photoD.getReading();
    }

    byte leftPercentage()
    {
        const float leftSum = photoB.getReading() + photoC.getReading();
        return (leftSum / static_cast<float>(sumLightReadings())) * 100;
    }

    byte rightPercentage()
    {
        const float rightSum = photoA.getReading() + photoD.getReading();
        return (rightSum / static_cast<float>(sumLightReadings())) * 100;
    }

    byte downPercentage()
    {
        const float downSum = photoA.getReading() + photoB.getReading();
        return (downSum / static_cast<float>(sumLightReadings())) * 100;
    }

    byte upPercentage()
    {
        const float upSum = photoC.getReading() + photoD.getReading();
        return (upSum / static_cast<float>(sumLightReadings())) * 100;
    }

    void logLightReadings()
    {
    #ifdef LOG_LIGHT_READINGS
        #ifdef LOG_INDIVIDUAL_SENSORS
        Serial.print("A: "); Serial.print(photoA.lightAsPercentage()); Serial.print("% ");
        Serial.print("B: "); Serial.print(photoB.lightAsPercentage()); Serial.print("% ");
        Serial.print("C: "); Serial.print(photoC.lightAsPercentage()); Serial.print("% ");
        Serial.print("D: "); Serial.print(photoD.lightAsPercentage()); Serial.print("% ");
        Serial.println();
        #endif

        Serial.print("Left: "); Serial.print(leftPercentage()); Serial.print("% ");
        Serial.print("Right: "); Serial.print(rightPercentage()); Serial.print("% ");
        Serial.println();

        Serial.print("Up: "); Serial.print(upPercentage()); Serial.print("% ");
        Serial.print("Down: "); Serial.print(downPercentage()); Serial.print("% ");
        Serial.print("\n\n");
    #endif
    }
}
