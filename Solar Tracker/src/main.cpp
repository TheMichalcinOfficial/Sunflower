#include "main.h"

namespace Servos
{
	// Servos

	Servo XServo;
	Servo YServo;

	// Functions

	void moveServo(Servo &servo, int angle, int minAngle = 0, int maxAngle = 180, byte speed = 1)
	{
		int newAngle = Utils::constrainInRange(static_cast<int>(servo.read()) + angle, minAngle, maxAngle);
		#ifdef LOG_ANGLES
			Serial.print("Angle: ");
			Serial.println(newAngle);
		#endif
		servo.write(newAngle);
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
}

namespace Input
{

}

void setup()
{
	Serial.begin(9600);

	pinMode(ERR_LED_PIN, OUTPUT);
	pinMode(OK_LED_PIN, OUTPUT);

	Servos::XServo.attach(X_SERVO_PIN);
	Servos::YServo.attach(Y_SERVO_PIN);
	Servos::YServo.write(Y_MAX_ANGLE);
}

void loop()
{
	while (Servos::XServo.read() < X_MAX_ANGLE)
		{ Servos::moveRight(); }

	while (Servos::XServo.read() > X_MIN_ANGLE)
		{ Servos::moveLeft(); }
	
	delay(500);
}
