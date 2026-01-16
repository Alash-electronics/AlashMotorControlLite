/*
 * Language: Қазақ | English: ../EN/PWM_PWM_DualMotor/ | Русский: ../RU/PWM_PWM_DualMotor/
 *
 * Бұл код AlashMotorControlLite кітапханасын пайдаланып екі қозғалтқышты басқаруды көрсетеді.
 * Әрбір қозғалтқыш үшін әртүрлі айналу жылдамдықтары жылдамдық өзгерістері арасында кідірістермен орнатылады.
 * Код Alash engineering үшін жазылған.
 */
#include "AlashMotorControlLite.h"
// PWM_PWM режимімен motorLeft және motorRight объектілерін жасаймыз
// motorLeft пиндері: PWM1 = 9, PWM2 = 10
// motorRight пиндері: PWM1 = 5, PWM2 = 6
AlashMotorControlLite motorLeft(PWM_PWM, 9, 10);
AlashMotorControlLite motorRight(PWM_PWM, 5, 6);
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
