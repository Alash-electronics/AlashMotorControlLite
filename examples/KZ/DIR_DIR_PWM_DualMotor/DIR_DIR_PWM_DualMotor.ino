/*
 * Language: Қазақ | English: ../EN/DIR_DIR_PWM_DualMotor/ | Русский: ../RU/DIR_DIR_PWM_DualMotor/
 *
 * Бұл код AlashMotorControlLite кітапханасын пайдаланып екі қозғалтқышты басқаруды көрсетеді.
 * Екі қозғалтқыш үшін әртүрлі айналу жылдамдықтары кідірістермен орнатылады.
 * Код Alash engineering үшін жазылған.
 */

#include "AlashMotorControlLite.h"
// DIR_DIR_PWM режимі және inA = 4, inB = 5, PWM = 6 пиндерімен motorLeft объектісін жасаймыз
AlashMotorControlLite motorLeft(DIR_DIR_PWM, 4, 5, 6);
// DIR_DIR_PWM режимі және inA = 7, inB = 8, PWM = 9 пиндерімен motorRight объектісін жасаймыз
AlashMotorControlLite motorRight(DIR_DIR_PWM, 7, 8, 9);
void setup() {
  // Бұл функцияда инициализация жоқ, бос қалдырылған
}
void loop() {
  motorLeft.setSpeed(100); // Сол қозғалтқыш үшін алға айналу жылдамдығын орнату
  motorRight.setSpeed(100); // Оң қозғалтқыш үшін алға айналу жылдамдығын орнату
  delay(3000); // 3 секунд кідіріс

  motorLeft.setSpeed(0); // Сол қозғалтқышты тоқтату
  motorRight.setSpeed(0); // Оң қозғалтқышты тоқтату
  delay(3000); // 3 секунд кідіріс

  motorLeft.setSpeed(-100); // Сол қозғалтқыш үшін артқа айналу жылдамдығын орнату
  motorRight.setSpeed(-100); // Оң қозғалтқыш үшін артқа айналу жылдамдығын орнату
  delay(3000); // 3 секунд кідіріс

  motorLeft.setSpeed(0); // Сол қозғалтқышты тоқтату
  motorRight.setSpeed(0); // Оң қозғалтқышты тоқтату
  delay(3000); // 3 секунд кідіріс
}
