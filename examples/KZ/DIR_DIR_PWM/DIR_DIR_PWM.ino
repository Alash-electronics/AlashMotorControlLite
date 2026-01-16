/*
 * Language: Қазақ | English: ../EN/DIR_DIR_PWM/ | Русский: ../RU/DIR_DIR_PWM/
 *
 * Бұл код AlashMotorControlLite кітапханасын пайдаланып қозғалтқышты басқаруды көрсетеді.
 * Қозғалтқыштың әртүрлі айналу жылдамдықтары кідірістермен орнатылады.
 * Код Alash engineering үшін жазылған.
 */
#include "AlashMotorControlLite.h"
// DIR_DIR_PWM режимі және inA = 4, inB = 5, PWM = 6 пиндерімен қозғалтқыш объектісін жасаймыз
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);
void setup() {
}
void loop() {
  motor.setSpeed(100); // Алға айналу жылдамдығын орнату
  delay(3000); // 3 секунд кідіріс

  motor.setSpeed(0); // Қозғалтқышты тоқтату
  delay(3000); // 3 секунд кідіріс

  motor.setSpeed(-100); // Артқа айналу жылдамдығын орнату
  delay(3000); // 3 секунд кідіріс

  motor.setSpeed(0); // Қозғалтқышты тоқтату
  delay(3000); // 3 секунд кідіріс
}
