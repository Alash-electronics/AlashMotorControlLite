/*
 * Language: English | Русский: ../RU/DIR_DIR_PWM/ | Қазақ: ../KZ/DIR_DIR_PWM/
 *
 * This code demonstrates motor control using the AlashMotorControlLite library.
 * It sets different rotation speeds for the motor with delays between them.
 * Code written for Alash engineering.
 */
#include "AlashMotorControlLite.h"
// Create motor object with DIR_DIR_PWM mode and pins inA = 4, inB = 5, PWM = 6
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);
void setup() {
}
void loop() {
  motor.setSpeed(100); // Set forward rotation speed
  delay(3000); // Delay 3 seconds

  motor.setSpeed(0); // Stop motor
  delay(3000); // Delay 3 seconds

  motor.setSpeed(-100); // Set reverse rotation speed
  delay(3000); // Delay 3 seconds

  motor.setSpeed(0); // Stop motor
  delay(3000); // Delay 3 seconds
}
