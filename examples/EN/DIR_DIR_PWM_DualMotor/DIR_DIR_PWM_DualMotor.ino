/*
 * Language: English | Русский: ../RU/DIR_DIR_PWM_DualMotor/ | Қазақ: ../KZ/DIR_DIR_PWM_DualMotor/
 *
 * This code demonstrates control of two motors using the AlashMotorControlLite library.
 * It sets different rotation speeds for two motors with delays between them.
 * Code written for Alash engineering.
 */

#include "AlashMotorControlLite.h"
// Create motorLeft object with DIR_DIR_PWM mode and pins inA = 4, inB = 5, PWM = 6
AlashMotorControlLite motorLeft(DIR_DIR_PWM, 4, 5, 6);
// Create motorRight object with DIR_DIR_PWM mode and pins inA = 7, inB = 8, PWM = 9
AlashMotorControlLite motorRight(DIR_DIR_PWM, 7, 8, 9);
void setup() {
  // No initialization in this function, left empty
}
void loop() {
  motorLeft.setSpeed(100); // Set forward rotation speed for left motor
  motorRight.setSpeed(100); // Set forward rotation speed for right motor
  delay(3000); // Delay 3 seconds

  motorLeft.setSpeed(0); // Stop left motor
  motorRight.setSpeed(0); // Stop right motor
  delay(3000); // Delay 3 seconds

  motorLeft.setSpeed(-100); // Set reverse rotation speed for left motor
  motorRight.setSpeed(-100); // Set reverse rotation speed for right motor
  delay(3000); // Delay 3 seconds

  motorLeft.setSpeed(0); // Stop left motor
  motorRight.setSpeed(0); // Stop right motor
  delay(3000); // Delay 3 seconds
}
