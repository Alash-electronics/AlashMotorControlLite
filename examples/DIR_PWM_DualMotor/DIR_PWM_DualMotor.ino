/*
 * Этот код демонстрирует управление двумя моторами с помощью библиотеки AlashMotorControlLite.
 * Он устанавливает разные скорости вращения для каждого мотора с задержкой между изменениями скорости.
 * Код написан для Alash engineering.
 */
#include "AlashMotorControlLite.h"
// Создаем объекты motorLeft и motorRight с режимом DIR_PWM
// Пины для motorLeft: inA = 4, PWM = 3
// Пины для motorRight: inA = 5, PWM = 6
AlashMotorControlLite motorLeft(DIR_PWM, 4, 3);
AlashMotorControlLite motorRight(DIR_PWM, 5, 6);
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
