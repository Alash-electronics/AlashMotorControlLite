/*
 * Language: English | Русский: ../RU/DIR_DIR_PWM_pot/ | Қазақ: ../KZ/DIR_DIR_PWM_pot/
 *
 * Code demonstrates motor control using the AlashMotorControlLite library.
 * Using analog input readings, it changes the speed and direction of motor rotation.
 * Code written for Alash engineering.
 */

#include "AlashMotorControlLite.h"
// Create motor object with DIR_DIR_PWM mode and pins inA = 4, inB = 5, PWM = 6
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);
void setup() {
  Serial.begin(9600); // Initialize serial port at 9600 baud
}
void loop() {
  int speed = map(analogRead(A0), 0, 1023, -100, 100); // Read value from analog input A0 and convert it to range -100 to 100
  motor.setSpeed(speed); // Set motor speed
  Serial.println(speed); // Output current speed to serial monitor
  delay(1000); // Delay 1 second
}
