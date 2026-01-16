// Language: Қазақ | English: ../EN/GettersDemo/ | Русский: ../RU/GettersDemo/
/*
 * Бұл мысал кітапхананың getter-әдістерін қолдануды көрсетеді:
 * - getSpeed() - қозғалтқыштың ағымдағы жылдамдығын алу
 * - getMode()  - драйвердің жұмыс режимін алу
 *
 * Бұл әдістер пайдалы:
 * - Қозғалтқыштардың күйін бақылау үшін
 * - Бағдарламаны жөндеу үшін
 * - Телеметрия жасау үшін
 * - Күйге негізделген шартты логика үшін
 *
 * Қосылым:
 * Arduino: Motor DIR -> Pin 4, PWM -> Pin 3 (режим DIR_PWM)
 * ESP32:   Motor IN1 -> GPIO 32, IN2 -> GPIO 33 (режим PWM_PWM)
 *
 * Код Alash engineering үшін жазылған
 */

#include "AlashMotorControlLite.h"

// Платформаңыз үшін режимді таңдаңыз:
#if defined(ARDUINO_ARCH_ESP32)
  AlashMotorControlLite motor(PWM_PWM, 32, 33);
#else
  AlashMotorControlLite motor(DIR_PWM, 4, 3);
#endif

// Қозғалтқыштың ағымдағы күйін шығару функциясы
void printMotorStatus() {
  int16_t currentSpeed = motor.getSpeed();
  MODE currentMode = motor.getMode();

  Serial.print(F("┌─────────────────────────────────┐\n"));
  Serial.print(F("│ ҚОЗҒАЛТҚЫШ КҮЙІ                 │\n"));
  Serial.print(F("├─────────────────────────────────┤\n"));
  Serial.print(F("│ Жылдамдық: "));
  Serial.print(currentSpeed);
  Serial.print(F(" "));

  // Бағыт индикаторы
  if (currentSpeed > 0) {
    Serial.print(F("→ Алға"));
  } else if (currentSpeed < 0) {
    Serial.print(F("← Артқа"));
  } else {
    Serial.print(F("■ Тоқтатылған"));
  }

  // Туралау үшін бос орындармен толтырамыз
  int spaces = 15 - String(currentSpeed).length();
  if (currentSpeed >= 0) spaces -= 7;  // "→ Алға"
  else spaces -= 9;                     // "← Артқа"
  if (currentSpeed == 0) spaces = 5;    // "■ Тоқтатылған"

  for (int i = 0; i < spaces; i++) {
    Serial.print(F(" "));
  }
  Serial.print(F("│\n"));

  Serial.print(F("│ Режим:     "));

  switch(currentMode) {
    case DIR_PWM:
      Serial.print(F("DIR_PWM"));
      Serial.print(F("          "));
      break;
    case PWM_PWM:
      Serial.print(F("PWM_PWM"));
      Serial.print(F("          "));
      break;
    case DIR_DIR_PWM:
      Serial.print(F("DIR_DIR_PWM"));
      Serial.print(F("      "));
      break;
    case DIR_DIR:
      Serial.print(F("DIR_DIR"));
      Serial.print(F("          "));
      break;
  }

  Serial.print(F("│\n"));
  Serial.print(F("└─────────────────────────────────┘\n\n"));
}

// Жылдамдық графигін көрсету функциясы
void printSpeedGraph() {
  int16_t speed = motor.getSpeed();
  Serial.print(F("График: "));

  // -100 ден +100 дейінгі графикті көрсетеміз
  if (speed < 0) {
    // Артқа қозғалыс
    int bars = map(abs(speed), 0, 100, 0, 20);
    for (int i = 20; i > bars; i--) Serial.print(F(" "));
    for (int i = 0; i < bars; i++) Serial.print(F("◄"));
    Serial.print(F("|"));
    for (int i = 0; i < 20; i++) Serial.print(F(" "));
  } else if (speed > 0) {
    // Алға қозғалыс
    for (int i = 0; i < 20; i++) Serial.print(F(" "));
    Serial.print(F("|"));
    int bars = map(speed, 0, 100, 0, 20);
    for (int i = 0; i < bars; i++) Serial.print(F("►"));
  } else {
    // Тоқтату
    for (int i = 0; i < 20; i++) Serial.print(F(" "));
    Serial.print(F("|"));
  }

  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  GETTER-ӘДІСТЕРДІ КӨРСЕТУ                     ║"));
  Serial.println(F("║  getSpeed() және getMode()                    ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== getSpeed() КӨРСЕТУ ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("getSpeed() КӨРСЕТУ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Алға жылдамдықты біртіндеп арттыру\n"));

  for (int speed = 0; speed <= 100; speed += 20) {
    motor.setSpeed(speed);

    Serial.print(F("motor.setSpeed("));
    Serial.print(speed);
    Serial.print(F(") → getSpeed() қайтарады: "));
    Serial.println(motor.getSpeed());

    printSpeedGraph();
    Serial.println();

    delay(1000);
  }

  delay(1000);

  Serial.println(F("\n→ Артқа жылдамдықты біртіндеп арттыру\n"));

  for (int speed = 0; speed >= -100; speed -= 20) {
    motor.setSpeed(speed);

    Serial.print(F("motor.setSpeed("));
    Serial.print(speed);
    Serial.print(F(") → getSpeed() қайтарады: "));
    Serial.println(motor.getSpeed());

    printSpeedGraph();
    Serial.println();

    delay(1000);
  }

  motor.stop();
  delay(2000);

  // ========== БАҚЫЛАУ КӨРСЕТУ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ҚОЗҒАЛТҚЫШ КҮЙІН БАҚЫЛАУ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ 75% дейін жеделдету"));
  motor.setSpeed(75);
  delay(500);
  printMotorStatus();

  Serial.println(F("→ 50% дейін төмендету"));
  motor.setSpeed(50);
  delay(500);
  printMotorStatus();

  Serial.println(F("→ -80% дейін реверс"));
  motor.setSpeed(-80);
  delay(500);
  printMotorStatus();

  Serial.println(F("→ Тоқтату"));
  motor.stop();
  delay(500);
  printMotorStatus();

  // ========== ШАРТТЫ ЛОГИКА ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("getSpeed() НЕГІЗІНДЕГІ ШАРТТЫ ЛОГИКА"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  motor.setSpeed(100);
  delay(500);

  if (motor.getSpeed() > 50) {
    Serial.println(F("✓ Жылдамдық жоғары (>50), LED қосамыз"));
  }

  if (motor.getSpeed() > 0) {
    Serial.println(F("✓ Қозғалтқыш алға қозғалады"));
  } else if (motor.getSpeed() < 0) {
    Serial.println(F("✓ Қозғалтқыш артқа қозғалады"));
  } else {
    Serial.println(F("✓ Қозғалтқыш тоқтатылған"));
  }

  delay(2000);
  motor.setSpeed(-60);
  delay(500);

  if (motor.getSpeed() < -50) {
    Serial.println(F("⚠ Артқа жоғары жылдамдық, абай болыңыз!"));
  }

  delay(2000);
  motor.brake();
  delay(500);

  if (motor.getSpeed() == 0) {
    Serial.println(F("✓ Қозғалтқыш толығымен тоқтатылды"));
  }

  // ========== getMode() КӨРСЕТУ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("getMode() КӨРСЕТУ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Драйвердің ағымдағы жұмыс режимі:"));
  printMotorStatus();

  Serial.println(F("Режим қозғалтқыш объектісін жасау кезінде орнатылады"));
  Serial.println(F("және жұмыс кезінде өзгертілмейді.\n"));

  Serial.println(F("Режим пайдалы:"));
  Serial.println(F("  • Қосылымды жөндеу"));
  Serial.println(F("  • Параметрлерді автоматты баптау"));
  Serial.println(F("  • Конфигурацияны құжаттау\n"));

  // ========== ҰСЫНЫСТАР ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║         GETTER-ӘДІСТЕРДІ ҚОЛДАНУ              ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  getSpeed():                                  ║"));
  Serial.println(F("║    • Ағымдағы жылдамдықты бақылау             ║"));
  Serial.println(F("║    • Шартты логика                            ║"));
  Serial.println(F("║    • Телеметрия және логтау                   ║"));
  Serial.println(F("║    • Күйді тексеру                            ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  getMode():                                    ║"));
  Serial.println(F("║    • Конфигурацияны тексеру                   ║"));
  Serial.println(F("║    • Жөндеу                                   ║"));
  Serial.println(F("║    • Әмбебап функциялар                       ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл аяқталды. 5 секундтан кейін қайталау...\n\n"));
  delay(5000);
}
