/*
 * Language: English | Русский: ../RU/ESP32_ZK5AD_SingleMotor/ | Қазақ: ../KZ/ESP32_ZK5AD_SingleMotor/
 *
 * Simple example of controlling one motor on ESP32 with ZK-5AD driver
 * ZK-5AD driver uses PWM_PWM mode for motor control
 *
 * Connection:
 * Motor: IN1 -> GPIO 32, IN2 -> GPIO 33
 *
 * Driver power:
 * VCC -> 5V (or 3.3V depending on driver)
 * GND -> GND
 * VM -> Motor power (6-12V)
 *
 * Code written for Alash engineering
 */

#include "AlashMotorControlLite.h"

// Create motor object in PWM_PWM mode
// GPIO 32 (IN1), GPIO 33 (IN2)
AlashMotorControlLite motor(PWM_PWM, 32, 33);

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 + ZK-5AD Motor Control"));
  Serial.println(F("Speed range: -100 to 100"));
  delay(1000);
}

void loop() {
  // Rotate forward at 50% speed
  Serial.println(F("Motor forward at 50%"));
  motor.setSpeed(50);
  delay(2000);

  // Rotate forward at full speed
  Serial.println(F("Motor forward at 100%"));
  motor.setSpeed(100);
  delay(2000);

  // Stop motor
  Serial.println(F("Stopping motor"));
  motor.stop();
  delay(1000);

  // Rotate reverse at 50% speed
  Serial.println(F("Motor reverse at 50%"));
  motor.setSpeed(-50);
  delay(2000);

  // Rotate reverse at full speed
  Serial.println(F("Motor reverse at 100%"));
  motor.setSpeed(-100);
  delay(2000);

  // Brake motor
  Serial.println(F("Braking motor"));
  motor.brake();
  delay(2000);
}
