/*
 * Language: Русский | English: ../EN/DIR_DIR_PWM_pot/ | Қазақ: ../KZ/DIR_DIR_PWM_pot/
 *
 * Код демонстрирует управление мотором с использованием библиотеки AlashMotorControlLite.
 * Используя показания аналогового входа, изменяет скорость и направление вращения мотора.
 * Код написан для Alash engineering.
 */

#include "AlashMotorControlLite.h"
// Создаем объект мотора с режимом DIR_DIR_PWM и пинами inA = 4, inB = 5, PWM = 6
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);
void setup() {
  Serial.begin(9600); // Инициализация последовательного порта на скорости 9600 бод
}
void loop() {
  int speed = map(analogRead(A0), 0, 1023, -100, 100); // Считываем значение с аналогового входа A0 и преобразуем его в диапазон -100 до 100
  motor.setSpeed(speed); // Устанавливаем скорость мотора
  Serial.println(speed); // Выводим текущую скорость в монитор порта
  delay(1000); // Задержка 1 секунда
}
