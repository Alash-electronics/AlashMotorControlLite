/*
 * Language: English | Русский: ../RU/ESP32_ZK5AD_DualMotor/ | Қазақ: ../KZ/ESP32_ZK5AD_DualMotor/
 *
 * Example of controlling two motors on ESP32 with ZK-5AD driver
 * ZK-5AD driver uses PWM_PWM mode for motor control
 *
 * Connection:
 * Motor 1: IN1 -> GPIO 32, IN2 -> GPIO 33
 * Motor 2: IN1 -> GPIO 25, IN2 -> GPIO 26
 *
 * Driver power:
 * VCC -> 5V (or 3.3V depending on driver)
 * GND -> GND
 * VM -> Motor power (6-12V)
 *
 * Code written for Alash engineering
 */

#include "AlashMotorControlLite.h"

// Create objects for two motors in PWM_PWM mode
// Motor 1: GPIO 32 (IN1), GPIO 33 (IN2)
AlashMotorControlLite motor1(PWM_PWM, 32, 33);

// Motor 2: GPIO 25 (IN1), GPIO 26 (IN2)
AlashMotorControlLite motor2(PWM_PWM, 25, 26);

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 + ZK-5AD Dual Motor Control"));
  Serial.println(F("Speed range: -100 to 100"));
  delay(1000);
}

void loop() {
  // Test 1: Both motors forward at 50% speed
  Serial.println(F("Both motors forward at 50%"));
  motor1.setSpeed(50);
  motor2.setSpeed(50);
  delay(2000);

  // Test 2: Both motors forward at full speed
  Serial.println(F("Both motors forward at 100%"));
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  delay(2000);

  // Test 3: Coast stop
  Serial.println(F("Stopping motors"));
  motor1.stop();
  motor2.stop();
  delay(1000);

  // Test 4: Both motors reverse at 50% speed
  Serial.println(F("Both motors reverse at 50%"));
  motor1.setSpeed(-50);
  motor2.setSpeed(-50);
  delay(2000);

  // Test 5: Both motors reverse at full speed
  Serial.println(F("Both motors reverse at 100%"));
  motor1.setSpeed(-100);
  motor2.setSpeed(-100);
  delay(2000);

  // Test 6: Braking
  Serial.println(F("Braking motors"));
  motor1.brake();
  motor2.brake();
  delay(1000);

  // Test 7: Turn in place (one forward, one reverse)
  Serial.println(F("Turn in place (rotating right)"));
  motor1.setSpeed(70);   // Left motor forward
  motor2.setSpeed(-70);  // Right motor reverse
  delay(2000);

  Serial.println(F("Turn in place (rotating left)"));
  motor1.setSpeed(-70);  // Left motor reverse
  motor2.setSpeed(70);   // Right motor forward
  delay(2000);

  // Test 8: Smooth acceleration
  Serial.println(F("Smooth acceleration"));
  for(int speed = 0; speed <= 100; speed += 10) {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    Serial.print(F("Speed: "));
    Serial.println(speed);
    delay(300);
  }

  // Test 9: Smooth deceleration
  Serial.println(F("Smooth deceleration"));
  for(int speed = 100; speed >= 0; speed -= 10) {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    Serial.print(F("Speed: "));
    Serial.println(speed);
    delay(300);
  }

  motor1.brake();
  motor2.brake();

  Serial.println(F("Cycle complete. Pause 2 seconds...\n"));
  delay(2000);
}
