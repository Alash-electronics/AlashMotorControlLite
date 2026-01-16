/*
 * Language: Қазақ | English: ../EN/ESP32_ZK5AD_SingleMotor/ | Русский: ../RU/ESP32_ZK5AD_SingleMotor/
 *
 * ZK-5AD драйверімен ESP32-де бір қозғалтқышты басқарудың қарапайым мысалы
 * ZK-5AD драйвері қозғалтқышты басқару үшін PWM_PWM режимін қолданады
 *
 * Қосылым:
 * Қозғалтқыш: IN1 -> GPIO 32, IN2 -> GPIO 33
 *
 * Драйвер қуаттандыруы:
 * VCC -> 5V (немесе драйверге байланысты 3.3V)
 * GND -> GND
 * VM -> Қозғалтқыш қуаттандыруы (6-12V)
 *
 * Код Alash engineering үшін жазылған
 */

#include "AlashMotorControlLite.h"

// PWM_PWM режимінде қозғалтқыш объектісін жасаймыз
// GPIO 32 (IN1), GPIO 33 (IN2)
AlashMotorControlLite motor(PWM_PWM, 32, 33);

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 + ZK-5AD қозғалтқышты басқару"));
  Serial.println(F("Жылдамдық диапазоны: -100-ден 100-ге"));
  delay(1000);
}

void loop() {
  // Алға 50% жылдамдықпен айналу
  Serial.println(F("Қозғалтқыш алға 50%"));
  motor.setSpeed(50);
  delay(2000);

  // Алға толық жылдамдықпен айналу
  Serial.println(F("Қозғалтқыш алға 100%"));
  motor.setSpeed(100);
  delay(2000);

  // Қозғалтқышты тоқтату
  Serial.println(F("Қозғалтқышты тоқтату"));
  motor.stop();
  delay(1000);

  // Артқа 50% жылдамдықпен айналу
  Serial.println(F("Қозғалтқыш артқа 50%"));
  motor.setSpeed(-50);
  delay(2000);

  // Артқа толық жылдамдықпен айналу
  Serial.println(F("Қозғалтқыш артқа 100%"));
  motor.setSpeed(-100);
  delay(2000);

  // Қозғалтқышты тежеу
  Serial.println(F("Қозғалтқышты тежеу"));
  motor.brake();
  delay(2000);
}
