/*
 * Этот код демонстрирует управление двигателем с помощью библиотеки AlashMotorControlLite.
 * Он устанавливает разные скорости вращения двигателя с задержкой между ними.
 * Код написан для Alash engineering.
 */
#include "AlashMotorControlLite.h"
// Создаем объект motor с режимом DIR_DIR_PWM и пинами inA = 4, inB = 5, PWM = 6
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);
void setup() {
}
void loop() {
  motor.setSpeed(100); // Установка скорости вращения вперед
  delay(3000); // Задержка 3 секунды

  motor.setSpeed(0); // Остановка двигателя
  delay(3000); // Задержка 3 секунды

  motor.setSpeed(-100); // Установка скорости вращения назад
  delay(3000); // Задержка 3 секунды

  motor.setSpeed(0); // Остановка двигателя
  delay(3000); // Задержка 3 секунды
}
