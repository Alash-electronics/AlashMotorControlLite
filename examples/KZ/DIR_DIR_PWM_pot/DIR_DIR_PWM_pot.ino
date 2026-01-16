/*
 * Language: Қазақ | English: ../EN/DIR_DIR_PWM_pot/ | Русский: ../RU/DIR_DIR_PWM_pot/
 *
 * Код AlashMotorControlLite кітапханасын пайдаланып қозғалтқышты басқаруды көрсетеді.
 * Аналогтық кіріс көрсеткіштерін пайдаланып, қозғалтқыштың жылдамдығы мен айналу бағытын өзгертеді.
 * Код Alash engineering үшін жазылған.
 */

#include "AlashMotorControlLite.h"
// DIR_DIR_PWM режимі және inA = 4, inB = 5, PWM = 6 пиндерімен қозғалтқыш объектісін жасаймыз
AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);
void setup() {
  Serial.begin(9600); // 9600 бод жылдамдығында сериялық портты инициализациялау
}
void loop() {
  int speed = map(analogRead(A0), 0, 1023, -100, 100); // A0 аналогтық кірістен мәнді оқып, оны -100-ден 100-ге дейінгі диапазонға түрлендіреміз
  motor.setSpeed(speed); // Қозғалтқыштың жылдамдығын орнатамыз
  Serial.println(speed); // Ағымдағы жылдамдықты порт мониторына шығарамыз
  delay(1000); // 1 секунд кідіріс
}
