/*
 * Language: English | Русский: ../RU/DIR_PWM/ | Қазақ: ../KZ/DIR_PWM/
 *
 * This code demonstrates motor control using the AlashMotorControlLite library.
 * It sets different rotation speeds for the motor with delays between them.
 * Code written for Alash engineering.
 */
#include "AlashMotorControlLite.h"
// Create motor object with DIR_PWM mode and pins inA = 4, PWM = 3
AlashMotorControlLite motor(DIR_PWM, 4, 3);
void setup() {   // No initialization in this function, left empty
}
void loop() {
  motor.setSpeed(50);   // Rotate forward at 50% speed
  delay(1000);          // Delay 1 second

  motor.setSpeed(100);  // Rotate forward at full speed
  delay(1000);          // Delay 1 second

  motor.stop();         // Stop motor (coast stop)
  delay(1000);          // Delay 1 second

  motor.setSpeed(-50);  // Rotate reverse at 50% speed
  delay(1000);          // Delay 1 second

  motor.setSpeed(-100); // Rotate reverse at full speed
  delay(1000);          // Delay 1 second

  motor.brake();        // Brake motor
  delay(1000);          // Delay 1 second
}
