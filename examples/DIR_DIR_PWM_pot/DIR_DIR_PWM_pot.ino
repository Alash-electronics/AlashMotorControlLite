/*
 * Код демонстрирует управление двигателем с помощью библиотеки AlashMotorControlLite.
 * Используя показания аналогового входа, он изменяет скорость и направление вращения двигателя.
 * Код написан для Alash engineering.
 */

#include "AlashMotorControlLite.h"
// Создаем объект motor с режимом DIR_DIR_PWM и пинами inA = 4, inB = 5, PWM = 6
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);
void setup() {
  Serial.begin(9600); // Инициализация последовательного порта со скоростью 9600 бит/с
}
void loop() {
  int speed = map(analogRead(A0), 0, 1023, -100, 100); // Считывание значения с аналогового входа A0 и его преобразование в диапазон от -100 до 100
  motor.setSpeed(speed); // Установка скорости двигателя
  Serial.println(speed); // Вывод текущей скорости в монитор последовательного порта
  delay(1000); // Задержка 1 секунда
}
