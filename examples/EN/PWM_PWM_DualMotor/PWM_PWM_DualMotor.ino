/*
 * Language: English | Русский: ../RU/PWM_PWM_DualMotor/ | Қазақ: ../KZ/PWM_PWM_DualMotor/
 *
 * This code demonstrates control of two motors using the AlashMotorControlLite library.
 * It sets different rotation speeds for each motor with delays between speed changes.
 * Code written for Alash engineering.
 */
#include "AlashMotorControlLite.h"
// Create motorLeft and motorRight objects with PWM_PWM mode
// Pins for motorLeft: PWM1 = 9, PWM2 = 10
// Pins for motorRight: PWM1 = 5, PWM2 = 6
AlashMotorControlLite motorLeft(PWM_PWM, 9, 10);
AlashMotorControlLite motorRight(PWM_PWM, 5, 6);
void setup() {
  // No initialization in this function, left empty
}
void loop() {
  motorLeft.setSpeed(50);   // Rotate forward at 50% speed for left motor
  motorRight.setSpeed(50);  // Rotate forward at 50% speed for right motor
  delay(1000);              // Delay 1 second

  motorLeft.setSpeed(100);  // Rotate forward at full speed for left motor
  motorRight.setSpeed(100); // Rotate forward at full speed for right motor
  delay(1000);              // Delay 1 second

  motorLeft.stop();         // Stop left motor
  motorRight.stop();        // Stop right motor
  delay(1000);              // Delay 1 second

  motorLeft.setSpeed(-50);  // Rotate reverse at 50% speed for left motor
  motorRight.setSpeed(-50); // Rotate reverse at 50% speed for right motor
  delay(1000);              // Delay 1 second

  motorLeft.setSpeed(-100); // Rotate reverse at full speed for left motor
  motorRight.setSpeed(-100);// Rotate reverse at full speed for right motor
  delay(1000);              // Delay 1 second

  motorLeft.brake();        // Brake left motor
  motorRight.brake();       // Brake right motor
  delay(1000);              // Delay 1 second
}
