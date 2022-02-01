#pragma once

// Library includes
#include <Arduino.h>

namespace Input
{
    class Sensor_Base
    {
    // Constructor
    public:
        constexpr Sensor_Base() = default;

    // Methods
    public:
        // Getters

        constexpr byte getPinNumber() const
        {
            return this->m_Pin;
        }

        // Setters

        virtual void assignPin(byte pin)
        {
            this->m_Pin = pin;
        }

    // Attributes
    private:
        byte m_Pin{ 0 };
    };

    class AnalogSensor : public Sensor_Base
    {
    // Constructor
    public:
        AnalogSensor() = default;

    // Methods
    public:
        // Getters

        unsigned int getReading() const
        {
            return this->m_Reading;
        }

        // Interaction

        void update()
        {
            this->m_Reading = analogRead(this->getPinNumber());
        }

        // Attributes
    private:
        unsigned int m_Reading{ 0 };
    };
}
