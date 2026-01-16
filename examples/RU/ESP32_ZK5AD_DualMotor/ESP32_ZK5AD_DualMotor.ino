/*
 * Language: Русский | English: ../EN/ESP32_ZK5AD_DualMotor/ | Қазақ: ../KZ/ESP32_ZK5AD_DualMotor/
 *
 * Пример управления двумя моторами на ESP32 с драйвером ZK-5AD
 * Драйвер ZK-5AD использует режим PWM_PWM для управления моторами
 *
 * Подключение:
 * Мотор 1: IN1 -> GPIO 32, IN2 -> GPIO 33
 * Мотор 2: IN1 -> GPIO 25, IN2 -> GPIO 26
 *
 * Питание драйвера:
 * VCC -> 5V (или 3.3V в зависимости от драйвера)
 * GND -> GND
 * VM -> Питание моторов (6-12V)
 *
 * Код написан для Alash engineering
 */

#include "AlashMotorControlLite.h"

// Создаем объекты для двух моторов в режиме PWM_PWM
// Мотор 1: GPIO 32 (IN1), GPIO 33 (IN2)
AlashMotorControlLite motor1(PWM_PWM, 32, 33);

// Мотор 2: GPIO 25 (IN1), GPIO 26 (IN2)
AlashMotorControlLite motor2(PWM_PWM, 25, 26);

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 + ZK-5AD управление двумя моторами"));
  Serial.println(F("Диапазон скорости: -100 до 100"));
  delay(1000);
}

void loop() {
  // Тест 1: Оба мотора вперед на 50% скорости
  Serial.println(F("Оба мотора вперед на 50%"));
  motor1.setSpeed(50);
  motor2.setSpeed(50);
  delay(2000);

  // Тест 2: Оба мотора вперед на полной скорости
  Serial.println(F("Оба мотора вперед на 100%"));
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  delay(2000);

  // Тест 3: Свободная остановка
  Serial.println(F("Остановка моторов"));
  motor1.stop();
  motor2.stop();
  delay(1000);

  // Тест 4: Оба мотора назад на 50% скорости
  Serial.println(F("Оба мотора назад на 50%"));
  motor1.setSpeed(-50);
  motor2.setSpeed(-50);
  delay(2000);

  // Тест 5: Оба мотора назад на полной скорости
  Serial.println(F("Оба мотора назад на 100%"));
  motor1.setSpeed(-100);
  motor2.setSpeed(-100);
  delay(2000);

  // Тест 6: Торможение
  Serial.println(F("Торможение моторов"));
  motor1.brake();
  motor2.brake();
  delay(1000);

  // Тест 7: Поворот на месте (один вперед, другой назад)
  Serial.println(F("Поворот на месте (вращение вправо)"));
  motor1.setSpeed(70);   // Левый мотор вперед
  motor2.setSpeed(-70);  // Правый мотор назад
  delay(2000);

  Serial.println(F("Поворот на месте (вращение влево)"));
  motor1.setSpeed(-70);  // Левый мотор назад
  motor2.setSpeed(70);   // Правый мотор вперед
  delay(2000);

  // Тест 8: Плавное ускорение
  Serial.println(F("Плавное ускорение"));
  for(int speed = 0; speed <= 100; speed += 10) {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    Serial.print(F("Скорость: "));
    Serial.println(speed);
    delay(300);
  }

  // Тест 9: Плавное замедление
  Serial.println(F("Плавное замедление"));
  for(int speed = 100; speed >= 0; speed -= 10) {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    Serial.print(F("Скорость: "));
    Serial.println(speed);
    delay(300);
  }

  motor1.brake();
  motor2.brake();

  Serial.println(F("Цикл завершен. Пауза 2 секунды...\n"));
  delay(2000);
}
