/*
 * Пример управления двумя моторами на ESP32 с драйвером ZK-5AD
 * Драйвер ZK-5AD использует режим PWM_PWM для управления моторами
 *
 * Подключение:
 * Motor 1: IN1 -> GPIO 32, IN2 -> GPIO 33
 * Motor 2: IN1 -> GPIO 25, IN2 -> GPIO 26
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
// Motor 1: GPIO 32 (IN1), GPIO 33 (IN2)
AlashMotorControlLite motor1(PWM_PWM, 32, 33);

// Motor 2: GPIO 25 (IN1), GPIO 26 (IN2)
AlashMotorControlLite motor2(PWM_PWM, 25, 26);

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 + ZK-5AD Dual Motor Control");
  Serial.println("Диапазон скорости: -100 до 100");
  delay(1000);
}

void loop() {
  // Тест 1: Оба мотора вперед на 50% скорости
  Serial.println("Оба мотора вперед на 50%");
  motor1.setSpeed(50);
  motor2.setSpeed(50);
  delay(2000);

  // Тест 2: Оба мотора вперед на полной скорости
  Serial.println("Оба мотора вперед на 100%");
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  delay(2000);

  // Тест 3: Свободная остановка
  Serial.println("Остановка моторов");
  motor1.stop();
  motor2.stop();
  delay(1000);

  // Тест 4: Оба мотора назад на 50% скорости
  Serial.println("Оба мотора назад на 50%");
  motor1.setSpeed(-50);
  motor2.setSpeed(-50);
  delay(2000);

  // Тест 5: Оба мотора назад на полной скорости
  Serial.println("Оба мотора назад на 100%");
  motor1.setSpeed(-100);
  motor2.setSpeed(-100);
  delay(2000);

  // Тест 6: Торможение
  Serial.println("Торможение моторов");
  motor1.brake();
  motor2.brake();
  delay(1000);

  // Тест 7: Поворот на месте (один вперед, другой назад)
  Serial.println("Поворот на месте (вращение вправо)");
  motor1.setSpeed(70);   // Левый мотор вперед
  motor2.setSpeed(-70);  // Правый мотор назад
  delay(2000);

  Serial.println("Поворот на месте (вращение влево)");
  motor1.setSpeed(-70);  // Левый мотор назад
  motor2.setSpeed(70);   // Правый мотор вперед
  delay(2000);

  // Тест 8: Плавный разгон
  Serial.println("Плавный разгон");
  for(int speed = 0; speed <= 100; speed += 10) {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    Serial.print("Скорость: ");
    Serial.println(speed);
    delay(300);
  }

  // Тест 9: Плавное торможение
  Serial.println("Плавное торможение");
  for(int speed = 100; speed >= 0; speed -= 10) {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    Serial.print("Скорость: ");
    Serial.println(speed);
    delay(300);
  }

  motor1.brake();
  motor2.brake();

  Serial.println("Цикл завершен. Пауза 2 секунды...\n");
  delay(2000);
}
