#include "main.h"

namespace Servos
{
	// Servos

	Servo XServo;
	Servo YServo;

	// Functions

	void moveServo(Servo& servo, int angle)
	{
		int newAngle = Utils::constrainInRange(static_cast<int>(servo.read()) + angle, 0, 180);
		#ifdef LOG_ANGLES
			Serial.print("Angle: ");
			Serial.println(newAngle);
		#endif
		servo.write(newAngle);
		delay(100);
	}

	void moveLeft()
		{ moveServo(XServo, -ANGLE_STEP); }

	void moveRight()
		{ moveServo(XServo, ANGLE_STEP); }

	void moveDown()
		{ moveServo(YServo, -ANGLE_STEP); }

	void moveUp()
		{ moveServo(YServo, ANGLE_STEP); }
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
	// Servos::YServo.write(Servos::YServo.read());
}

void loop()
{
	while (Servos::XServo.read() < 180)
		{ Servos::moveRight(); }

	while (Servos::XServo.read() > 0)
		{ Servos::moveLeft(); }
	
	delay(500);
}
