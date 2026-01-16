/*
 * Language: Қазақ | English: ../EN/DIR_DIR_PWM_DualMotor/ | Русский: ../RU/DIR_DIR_PWM_DualMotor/
 *
 * TODO: Translate comments to Kazakh
 *
 * Этот код демонстрирует управление двумя моторами с использованием библиотеки AlashMotorControlLite.
 * Устанавливаются различные скорости вращения для двух моторов с задержками между ними.
 * Код написан для Alash engineering.
 */

#include "AlashMotorControlLite.h"
// Создаем объект motorLeft с режимом DIR_DIR_PWM и пинами inA = 4, inB = 5, PWM = 6
AlashMotorControlLite motorLeft(DIR_DIR_PWM, 4, 5, 6);
// Создаем объект motorRight с режимом DIR_DIR_PWM и пинами inA = 7, inB = 8, PWM = 9
AlashMotorControlLite motorRight(DIR_DIR_PWM, 7, 8, 9);
void setup() {
  // Нет инициализации в этой функции, оставлена пустой
}
void loop() {
  motorLeft.setSpeed(100); // Установить скорость вращения вперед для левого мотора
  motorRight.setSpeed(100); // Установить скорость вращения вперед для правого мотора
  delay(3000); // Задержка 3 секунды

  motorLeft.setSpeed(0); // Остановить левый мотор
  motorRight.setSpeed(0); // Остановить правый мотор
  delay(3000); // Задержка 3 секунды

  motorLeft.setSpeed(-100); // Установить скорость вращения назад для левого мотора
  motorRight.setSpeed(-100); // Установить скорость вращения назад для правого мотора
  delay(3000); // Задержка 3 секунды

  motorLeft.setSpeed(0); // Остановить левый мотор
  motorRight.setSpeed(0); // Остановить правый мотор
  delay(3000); // Задержка 3 секунды
}
