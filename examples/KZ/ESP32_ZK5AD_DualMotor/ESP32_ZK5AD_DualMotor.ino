// Language: Қазақ | English: ../EN/ESP32_ZK5AD_DualMotor/ | Русский: ../RU/ESP32_ZK5AD_DualMotor/
/*
 * ESP32-де ZK-5AD драйверімен екі қозғалтқышты басқару мысалы
 * ZK-5AD драйвері қозғалтқыштарды басқару үшін PWM_PWM режимін қолданады
 *
 * Қосылым:
 * Қозғалтқыш 1: IN1 -> GPIO 32, IN2 -> GPIO 33
 * Қозғалтқыш 2: IN1 -> GPIO 25, IN2 -> GPIO 26
 *
 * Драйвер қуаты:
 * VCC -> 5V (немесе драйверге байланысты 3.3V)
 * GND -> GND
 * VM -> Қозғалтқыш қуаты (6-12V)
 *
 * Код Alash engineering үшін жазылған
 */

#include "AlashMotorControlLite.h"

// PWM_PWM режимінде екі қозғалтқыш үшін объектілер жасаймыз
// Қозғалтқыш 1: GPIO 32 (IN1), GPIO 33 (IN2)
AlashMotorControlLite motor1(PWM_PWM, 32, 33);

// Қозғалтқыш 2: GPIO 25 (IN1), GPIO 26 (IN2)
AlashMotorControlLite motor2(PWM_PWM, 25, 26);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║   ESP32 + ZK-5AD - Екі қозғалтқыш мысалы      ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Бұл мысал ESP32-де ZK-5AD драйверімен екі DC қозғалтқышты басқаруды көрсетеді."));
  Serial.println(F("Әрбір қозғалтқыш тәуелсіз басқарылады, жылдамдық диапазоны -100-ден 100-ге дейін.\n"));

  delay(2000);
}

void loop() {
  // ========== СЫНАҚ 1: Екі қозғалтқыш алға қозғалады ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СЫНАҚ 1: Екеуі де алға жылдамдықта"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Қозғалтқыш 1: 70% алға"));
  Serial.println(F("Қозғалтқыш 2: 70% алға\n"));

  motor1.setSpeed(70);
  motor2.setSpeed(70);
  delay(3000);

  Serial.println(F("Екі қозғалтқыш тоқтады\n"));
  motor1.stop();
  motor2.stop();
  delay(2000);

  // ========== СЫНАҚ 2: Екі қозғалтқыш артқа қозғалады ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СЫНАҚ 2: Екеуі де артқа жылдамдықта"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Қозғалтқыш 1: 70% артқа"));
  Serial.println(F("Қозғалтқыш 2: 70% артқа\n"));

  motor1.setSpeed(-70);
  motor2.setSpeed(-70);
  delay(3000);

  Serial.println(F("Екі қозғалтқыш тоқтады\n"));
  motor1.stop();
  motor2.stop();
  delay(2000);

  // ========== СЫНАҚ 3: Әртүрлі жылдамдықта ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СЫНАҚ 3: Әртүрлі жылдамдықтар"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Қозғалтқыш 1: 50% алға"));
  Serial.println(F("Қозғалтқыш 2: 100% алға\n"));

  motor1.setSpeed(50);
  motor2.setSpeed(100);
  delay(3000);

  Serial.println(F("Қозғалтқыштар тоқтады\n"));
  motor1.stop();
  motor2.stop();
  delay(2000);

  // ========== СЫНАҚ 4: Қарама-қарсы бағыттар (робот бұрылуы) ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СЫНАҚ 4: Қарама-қарсы бағыттар (орнында бұрылу)"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Қозғалтқыш 1: 60% алға"));
  Serial.println(F("Қозғалтқыш 2: 60% артқа\n"));
  Serial.println(F("→ Робот сағат тілі бағытында айналады\n"));

  motor1.setSpeed(60);
  motor2.setSpeed(-60);
  delay(2000);

  Serial.println(F("Қозғалтқыштар тоқтады\n"));
  motor1.stop();
  motor2.stop();
  delay(2000);

  // ========== СЫНАҚ 5: Тежеу ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СЫНАҚ 5: Белсенді тежеу"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Қозғалтқыштар толық жылдамдықта жеделдетіледі...\n"));

  motor1.setSpeed(100);
  motor2.setSpeed(100);
  delay(2000);

  Serial.println(F("→ brake() шақырылды"));
  Serial.println(F("  Қозғалтқыштар белсенді тежеледі\n"));

  motor1.brake();
  motor2.brake();
  delay(2000);

  // ========== АҚПАРАТ ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║             ПАЙДАЛЫ КЕҢЕСТЕР                  ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  ZK-5AD екі DC қозғалтқышты басқара алады     ║"));
  Serial.println(F("║  Әрбір қозғалтқыш тәуелсіз басқарылады        ║"));
  Serial.println(F("║  PWM_PWM режимі - 2 пин әрбір қозғалтқышқа    ║"));
  Serial.println(F("║  Жылдамдық диапазоны: -100-ден 100-ге         ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Роботтар үшін:                               ║"));
  Serial.println(F("║    - Екеуі алға = түзу жүру                   ║"));
  Serial.println(F("║    - Екеуі артқа = кері жүру                  ║"));
  Serial.println(F("║    - Қарама-қарсы = орнында бұрылу            ║"));
  Serial.println(F("║    - Әртүрлі жылдамдық = қисық жүру           ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл аяқталды. 5 секундтан кейін қайталау...\n\n"));
  delay(5000);
}
