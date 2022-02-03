#include "main.h"

namespace Servos
{
	// Servos

	Servo XServo;
	Servo YServo;

	// Functions

	void moveServo(Servo &servo, int angle, int minAngle = 0, int maxAngle = 180, byte speed = 1)
	{
		servo.write(Utils::constrainInRange(static_cast<int>(servo.read()) + angle, minAngle, maxAngle));
		delay(100 / speed);
	}

	void moveLeft()
		{ moveServo(XServo, -ANGLE_STEP, X_MIN_ANGLE, X_MAX_ANGLE); }

	void moveRight()
		{ moveServo(XServo, ANGLE_STEP, X_MIN_ANGLE, X_MAX_ANGLE); }

	void moveDown()
		{ moveServo(YServo, -ANGLE_STEP, Y_MIN_ANGLE, Y_MAX_ANGLE); }

	void moveUp()
		{ moveServo(YServo, ANGLE_STEP, Y_MIN_ANGLE, Y_MAX_ANGLE); }

	void logAngles()
	{
	#ifdef LOG_ANGLES
		Serial.print("X Angle: "); Serial.print(XServo.read());
		Serial.print(" Y Angle: "); Serial.println(YServo.read());
	#endif
	}

}

namespace Input
{
	Photosensor photoA, photoB, photoC, photoD;

	void updateAll()
	{
		AnalogSensor *analogSensors[] = {&photoA, &photoB, &photoC, &photoC, &photoD};
		for (size_t i = 0; i < sizeof(analogSensors) / sizeof(AnalogSensor *); ++i)
		{
			analogSensors[i]->update();
		}
	}
}

namespace Control
{
	bool isAligned_X()
	{
		return Input::leftPercentage() == Input::rightPercentage();
	}

	bool isAligned()
	{
		return isAligned_X();
	}

	void alignX()
	{
		if (!isAligned_X())
		{
			if (Input::leftPercentage() > Input::rightPercentage())
				{ Servos::moveLeft(); }
			else
				{ Servos::moveRight(); }
		}
	}

	void align()
	{
		while (!isAligned())
		{
			alignX();

			Input::updateAll();
			Input::logLightReadings();
		}
	}
}

void setup()
{
#ifdef DEBUG_LOGGING
	Serial.begin(9600);
#endif

	pinMode(ERR_LED_PIN, OUTPUT);
	pinMode(OK_LED_PIN, OUTPUT);

	Servos::XServo.attach(X_SERVO_PIN);
	Servos::YServo.attach(Y_SERVO_PIN);
	Servos::YServo.write(Y_MAX_ANGLE - 1);

	Input::photoA.assignPin(PHOTORESISTOR_A_PIN);
	Input::photoB.assignPin(PHOTORESISTOR_B_PIN);
	Input::photoC.assignPin(PHOTORESISTOR_C_PIN);
	Input::photoD.assignPin(PHOTORESISTOR_D_PIN);
}

void loop()
{
	Input::updateAll();
	Input::logLightReadings();
	Control::align();

	delay(500);
}
