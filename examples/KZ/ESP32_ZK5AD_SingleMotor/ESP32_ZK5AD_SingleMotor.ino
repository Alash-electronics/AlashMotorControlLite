/*
 * Language: Қазақ | English: ../EN/ESP32_ZK5AD_SingleMotor/ | Русский: ../RU/ESP32_ZK5AD_SingleMotor/
 *
 * TODO: Translate comments to Kazakh
 *
 * Простой пример управления одним мотором на ESP32 с драйвером ZK-5AD
 * Драйвер ZK-5AD использует режим PWM_PWM для управления мотором
 *
 * Подключение:
 * Мотор: IN1 -> GPIO 32, IN2 -> GPIO 33
 *
 * Питание драйвера:
 * VCC -> 5V (или 3.3V в зависимости от драйвера)
 * GND -> GND
 * VM -> Питание моторов (6-12V)
 *
 * Код написан для Alash engineering
 */

#include "AlashMotorControlLite.h"

// Создаем объект мотора в режиме PWM_PWM
// GPIO 32 (IN1), GPIO 33 (IN2)
AlashMotorControlLite motor(PWM_PWM, 32, 33);

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 + ZK-5AD управление мотором"));
  Serial.println(F("Диапазон скорости: -100 до 100"));
  delay(1000);
}

void loop() {
  // Вращение вперед на 50% скорости
  Serial.println(F("Мотор вперед на 50%"));
  motor.setSpeed(50);
  delay(2000);

  // Вращение вперед на полной скорости
  Serial.println(F("Мотор вперед на 100%"));
  motor.setSpeed(100);
  delay(2000);

  // Остановка мотора
  Serial.println(F("Остановка мотора"));
  motor.stop();
  delay(1000);

  // Вращение назад на 50% скорости
  Serial.println(F("Мотор назад на 50%"));
  motor.setSpeed(-50);
  delay(2000);

  // Вращение назад на полной скорости
  Serial.println(F("Мотор назад на 100%"));
  motor.setSpeed(-100);
  delay(2000);

  // Торможение мотора
  Serial.println(F("Торможение мотора"));
  motor.brake();
  delay(2000);
}
