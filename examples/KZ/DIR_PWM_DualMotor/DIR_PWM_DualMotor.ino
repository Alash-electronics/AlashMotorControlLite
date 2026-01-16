/*
 * Language: Қазақ | English: ../EN/DIR_PWM_DualMotor/ | Русский: ../RU/DIR_PWM_DualMotor/
 *
 * TODO: Translate comments to Kazakh
 *
 * Этот код демонстрирует управление двумя моторами с использованием библиотеки AlashMotorControlLite.
 * Устанавливаются различные скорости вращения для каждого мотора с задержками между изменениями скорости.
 * Код написан для Alash engineering.
 */
#include "AlashMotorControlLite.h"
// Создаем объекты motorLeft и motorRight с режимом DIR_PWM
// Пины для motorLeft: inA = 4, PWM = 3
// Пины для motorRight: inA = 5, PWM = 6
AlashMotorControlLite motorLeft(DIR_PWM, 4, 3);
AlashMotorControlLite motorRight(DIR_PWM, 5, 6);
void setup() {
  // Нет инициализации в этой функции, оставлена пустой
}
void loop() {
  motorLeft.setSpeed(50);   // Вращение вперед на 50% скорости для левого мотора
  motorRight.setSpeed(50);  // Вращение вперед на 50% скорости для правого мотора
  delay(1000);              // Задержка 1 секунда

  motorLeft.setSpeed(100);  // Вращение вперед на полной скорости для левого мотора
  motorRight.setSpeed(100); // Вращение вперед на полной скорости для правого мотора
  delay(1000);              // Задержка 1 секунда

  motorLeft.stop();         // Остановка левого мотора
  motorRight.stop();        // Остановка правого мотора
  delay(1000);              // Задержка 1 секунда

  motorLeft.setSpeed(-50);  // Вращение назад на 50% скорости для левого мотора
  motorRight.setSpeed(-50); // Вращение назад на 50% скорости для правого мотора
  delay(1000);              // Задержка 1 секунда

  motorLeft.setSpeed(-100); // Вращение назад на полной скорости для левого мотора
  motorRight.setSpeed(-100);// Вращение назад на полной скорости для правого мотора
  delay(1000);              // Задержка 1 секунда

  motorLeft.brake();        // Торможение левого мотора
  motorRight.brake();       // Торможение правого мотора
  delay(1000);              // Задержка 1 секунда
}
