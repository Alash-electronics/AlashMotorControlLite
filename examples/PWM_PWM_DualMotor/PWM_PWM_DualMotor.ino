/*
 * Этот код демонстрирует управление двумя моторами с помощью библиотеки AlashMotorControlLite.
 * Он устанавливает разные скорости вращения для каждого мотора с задержкой между изменениями скорости.
 * Код написан для Alash engineering.
 */
#include "AlashMotorControlLite.h"
// Создаем объекты motorLeft и motorRight с режимом PWM_PWM
// Пины для motorLeft: PWM1 = 9, PWM2 = 10
// Пины для motorRight: PWM1 = 5, PWM2 = 6
AlashMotorControlLite motorLeft(PWM_PWM, 9, 10);
AlashMotorControlLite motorRight(PWM_PWM, 5, 6);
void setup() {
  // В данной функции нет инициализации, оставлено пустым
}
void loop() {
  motorLeft.setSpeed(128);  // Вращение вперед на 50% скорости для левого мотора
  motorRight.setSpeed(128); // Вращение вперед на 50% скорости для правого мотора
  delay(1000);              // Задержка 1 секунда
  
  motorLeft.setSpeed(255);  // Вращение вперед на полной скорости для левого мотора
  motorRight.setSpeed(255); // Вращение вперед на полной скорости для правого мотора
  delay(1000);              // Задержка 1 секунда

  motorLeft.setSpeed(0);    // Остановка левого мотора
  motorRight.setSpeed(0);   // Остановка правого мотора
  delay(1000);              // Задержка 1 секунда

  motorLeft.setSpeed(-128); // Вращение назад на 50% скорости для левого мотора
  motorRight.setSpeed(-128);// Вращение назад на 50% скорости для правого мотора
  delay(1000);              // Задержка 1 секунда
  
  motorLeft.setSpeed(-255); // Вращение назад на полной скорости для левого мотора
  motorRight.setSpeed(-255);// Вращение назад на полной скорости для правого мотора
  delay(1000);              // Задержка 1 секунда

  motorLeft.setSpeed(0);    // Остановка левого мотора
  motorRight.setSpeed(0);   // Остановка правого мотора
  delay(1000);              // Задержка 1 секунда
}
