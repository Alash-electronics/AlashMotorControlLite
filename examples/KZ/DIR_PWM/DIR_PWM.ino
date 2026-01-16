/*
 * Language: Қазақ | English: ../EN/DIR_PWM/ | Русский: ../RU/DIR_PWM/
 *
 * TODO: Translate comments to Kazakh
 *
 * Этот код демонстрирует управление мотором с использованием библиотеки AlashMotorControlLite.
 * Устанавливаются различные скорости вращения мотора с задержками между ними.
 * Код написан для Alash engineering.
 */
#include "AlashMotorControlLite.h"
// Создаем объект мотора с режимом DIR_PWM и пинами inA = 4, PWM = 3
AlashMotorControlLite motor(DIR_PWM, 4, 3);
void setup() {   // Нет инициализации в этой функции, оставлена пустой
}
void loop() {
  motor.setSpeed(50);   // Вращение вперед на 50% скорости
  delay(1000);          // Задержка 1 секунда

  motor.setSpeed(100);  // Вращение вперед на полной скорости
  delay(1000);          // Задержка 1 секунда

  motor.stop();         // Остановка мотора (свободная остановка)
  delay(1000);          // Задержка 1 секунда

  motor.setSpeed(-50);  // Вращение назад на 50% скорости
  delay(1000);          // Задержка 1 секунда

  motor.setSpeed(-100); // Вращение назад на полной скорости
  delay(1000);          // Задержка 1 секунда

  motor.brake();        // Торможение мотора
  delay(1000);          // Задержка 1 секунда
}
