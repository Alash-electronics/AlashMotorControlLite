/*
 * Language: Русский | English: ../EN/DIR_DIR_PWM/ | Қазақ: ../KZ/DIR_DIR_PWM/
 *
 * Этот код демонстрирует управление мотором с использованием библиотеки AlashMotorControlLite.
 * Устанавливаются различные скорости вращения мотора с задержками между ними.
 * Код написан для Alash engineering.
 */
#include "AlashMotorControlLite.h"
// Создаем объект мотора с режимом DIR_DIR_PWM и пинами inA = 4, inB = 5, PWM = 6
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);
void setup() {
}
void loop() {
  motor.setSpeed(100); // Установить скорость вращения вперед
  delay(3000); // Задержка 3 секунды

  motor.setSpeed(0); // Остановить мотор
  delay(3000); // Задержка 3 секунды

  motor.setSpeed(-100); // Установить скорость вращения назад
  delay(3000); // Задержка 3 секунды

  motor.setSpeed(0); // Остановить мотор
  delay(3000); // Задержка 3 секунды
}
