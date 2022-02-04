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
	bool shouldMoveLeft()
	{
		return Input::leftPercentage() > Input::rightPercentage();
	}

	bool shouldMoveRight()
	{
		return Input::leftPercentage() < Input::rightPercentage();
	}

	bool shouldMoveDown()
	{
		return Input::upPercentage() < Input::downPercentage();
	}

	bool shouldMoveUp()
	{
		return Input::upPercentage() > Input::downPercentage();
	}

	bool isAligned_X()
	{
		return abs(Input::leftPercentage() - Input::rightPercentage()) <= X_ERROR_MARGIN ||
			(shouldMoveLeft() && Servos::XServo.read() == X_MIN_ANGLE) ||
			(shouldMoveRight() && Servos::XServo.read() == X_MAX_ANGLE);
	}

	bool isAligned_Y()
	{
		return abs(Input::upPercentage() - Input::downPercentage()) <= Y_ERROR_MARGIN ||
			(shouldMoveDown() && Servos::YServo.read() == Y_MIN_ANGLE) ||
			(shouldMoveUp() && Servos::YServo.read() == Y_MAX_ANGLE);
	}

	bool isAligned()
	{
		return isAligned_X() && isAligned_Y();
	}

	void alignX()
	{
		if (!isAligned_X())
		{
			if (shouldMoveLeft())
				{ Servos::moveLeft(); }
			else
				{ Servos::moveRight(); }
		}
	}

	void alignY()
	{
		if (!isAligned_Y())
		{
			if (shouldMoveUp())
				{ Servos::moveUp(); }
			else
				{ Servos::moveDown(); }
		}
	}

	void align()
	{
		while (!isAligned())
		{
			alignX();
			alignY();

			Input::updateAll();
			Input::logLightReadings();
			Servos::logAngles();
			delay(5);
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
	Servos::YServo.write(Y_MAX_ANGLE);

	Input::photoA.assignPin(PHOTORESISTOR_A_PIN);
	Input::photoB.assignPin(PHOTORESISTOR_B_PIN);
	Input::photoC.assignPin(PHOTORESISTOR_C_PIN);
	Input::photoD.assignPin(PHOTORESISTOR_D_PIN);
}

void loop()
{
	Input::updateAll();
	Input::logLightReadings();
	Servos::logAngles();
	Control::align();

	delay(500);
}
