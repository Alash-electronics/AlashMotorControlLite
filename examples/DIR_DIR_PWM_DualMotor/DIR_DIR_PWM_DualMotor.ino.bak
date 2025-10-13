/*
 * Этот код демонстрирует управление двумя двигателями с помощью библиотеки AlashMotorControlLite.
 * Он устанавливает разные скорости вращения для двух двигателей с задержкой между ними.
 * Код написан для Alash engineering.
 */

#include "AlashMotorControlLite.h"
// Создаем объект motorLeft с режимом DIR_DIR_PWM и пинами inA = 4, inB = 5, PWM = 6
AlashMotorControlLite motorLeft(DIR_DIR_PWM, 4, 5, 6);
// Создаем объект motorRight с режимом DIR_DIR_PWM и пинами inA = 7, inB = 8, PWM = 9
AlashMotorControlLite motorRight(DIR_DIR_PWM, 7, 8, 9);
void setup() {
  // В данной функции нет инициализации, оставлено пустым
}
void loop() {
  motorLeft.setSpeed(100); // Установка скорости вращения вперед для левого мотора
  motorRight.setSpeed(100); // Установка скорости вращения вперед для правого мотора
  delay(3000); // Задержка 3 секунды

  motorLeft.setSpeed(0); // Остановка левого мотора
  motorRight.setSpeed(0); // Остановка правого мотора
  delay(3000); // Задержка 3 секунды

  motorLeft.setSpeed(-100); // Установка скорости вращения назад для левого мотора
  motorRight.setSpeed(-100); // Установка скорости вращения назад для правого мотора
  delay(3000); // Задержка 3 секунды

  motorLeft.setSpeed(0); // Остановка левого мотора
  motorRight.setSpeed(0); // Остановка правого мотора
  delay(3000); // Задержка 3 секунды
}
