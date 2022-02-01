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
}

void loop()
{
	while (Servos::XServo.read() < X_MAX_ANGLE)
		{ Servos::moveRight(); Servos::logAngles(); }

	while (Servos::XServo.read() > X_MIN_ANGLE)
		{ Servos::moveLeft(); Servos::logAngles(); }

	while (Servos::YServo.read() > Y_MIN_ANGLE)
		{ Servos::moveDown(); Servos::logAngles(); }
	
	while (Servos::YServo.read() < Y_MAX_ANGLE)
		{ Servos::moveUp(); Servos::logAngles(); }

	delay(500);
}
