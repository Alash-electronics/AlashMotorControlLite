/*
 * Language: Қазақ | English: ../EN/DIR_PWM_DualMotor/ | Русский: ../RU/DIR_PWM_DualMotor/
 *
 * Бұл код AlashMotorControlLite кітапханасын пайдаланып екі қозғалтқышты басқаруды көрсетеді.
 * Әрбір қозғалтқыш үшін әртүрлі айналу жылдамдықтары жылдамдық өзгерістері арасында кідірістермен орнатылады.
 * Код Alash engineering үшін жазылған.
 */
#include "AlashMotorControlLite.h"
// DIR_PWM режимімен motorLeft және motorRight объектілерін жасаймыз
// motorLeft пиндері: inA = 4, PWM = 3
// motorRight пиндері: inA = 5, PWM = 6
AlashMotorControlLite motorLeft(DIR_PWM, 4, 3);
AlashMotorControlLite motorRight(DIR_PWM, 5, 6);
void setup() {
  // Бұл функцияда инициализация жоқ, бос қалдырылған
}
void loop() {
  motorLeft.setSpeed(50);   // Сол қозғалтқыш үшін алға 50% жылдамдықпен айналу
  motorRight.setSpeed(50);  // Оң қозғалтқыш үшін алға 50% жылдамдықпен айналу
  delay(1000);              // 1 секунд кідіріс

  motorLeft.setSpeed(100);  // Сол қозғалтқыш үшін алға толық жылдамдықпен айналу
  motorRight.setSpeed(100); // Оң қозғалтқыш үшін алға толық жылдамдықпен айналу
  delay(1000);              // 1 секунд кідіріс

  motorLeft.stop();         // Сол қозғалтқышты тоқтату
  motorRight.stop();        // Оң қозғалтқышты тоқтату
  delay(1000);              // 1 секунд кідіріс

  motorLeft.setSpeed(-50);  // Сол қозғалтқыш үшін артқа 50% жылдамдықпен айналу
  motorRight.setSpeed(-50); // Оң қозғалтқыш үшін артқа 50% жылдамдықпен айналу
  delay(1000);              // 1 секунд кідіріс

  motorLeft.setSpeed(-100); // Сол қозғалтқыш үшін артқа толық жылдамдықпен айналу
  motorRight.setSpeed(-100);// Оң қозғалтқыш үшін артқа толық жылдамдықпен айналу
  delay(1000);              // 1 секунд кідіріс

  motorLeft.brake();        // Сол қозғалтқышты тежеу
  motorRight.brake();       // Оң қозғалтқышты тежеу
  delay(1000);              // 1 секунд кідіріс
}
