// Language: Қазақ | English: ../EN/SmoothSpeed/ | Русский: ../RU/SmoothSpeed/
/*
 * Мысал жылдамдықтың тегіс өзгеруін көрсетеді (Ramping)
 *
 * Жылдамдықтың тегіс өзгеруі маңызды:
 * - Механиканы секірістер мен соққылық жүктемелерден қорғау үшін
 * - Қозғалтқыштар мен редукторлардың қызмет ету мерзімін ұзарту үшін
 * - Дөңгелектердің сырғуын болдырмау үшін
 * - Роботтың тегіс қозғалысы үшін
 * - Ток тұтынудың шыңын төмендету үшін
 *
 * Қосылу:
 * Arduino: Motor DIR -> Pin 4, PWM -> Pin 3 (DIR_PWM режимі)
 * ESP32:   Motor IN1 -> GPIO 32, IN2 -> GPIO 33 (PWM_PWM режимі)
 *
 * Код Alash engineering үшін жазылды
 */

#include "AlashMotorControlLite.h"

// Платформаңыз үшін режимді таңдаңыз:
#if defined(ARDUINO_ARCH_ESP32)
  AlashMotorControlLite motor(PWM_PWM, 32, 33);
#else
  AlashMotorControlLite motor(DIR_PWM, 4, 3);
#endif

// Жылдамдықты тегіс өзгерту функциясы
// targetSpeed: мақсатты жылдамдық (-100-ден 100-ге дейін)
// rampTime: үдеу/тежеу уақыты миллисекундпен
void smoothSetSpeed(int targetSpeed, unsigned long rampTime) {
  int currentSpeed = motor.getSpeed();
  int speedDiff = targetSpeed - currentSpeed;
  int steps = abs(speedDiff);

  if (steps == 0) return;  // Мақсатты жылдамдықта тұр

  unsigned long stepDelay = rampTime / steps;

  Serial.print(F("Тегіс өзгерту: "));
  Serial.print(currentSpeed);
  Serial.print(F(" → "));
  Serial.print(targetSpeed);
  Serial.print(F(" "));
  Serial.print(rampTime);
  Serial.println(F(" мс-та"));

  if (speedDiff > 0) {
    // Жылдамдықты арттырамыз
    for (int speed = currentSpeed + 1; speed <= targetSpeed; speed++) {
      motor.setSpeed(speed);
      delay(stepDelay);
    }
  } else {
    // Жылдамдықты азайтамыз
    for (int speed = currentSpeed - 1; speed >= targetSpeed; speed--) {
      motor.setSpeed(speed);
      delay(stepDelay);
    }
  }

  Serial.println(F("  ✓ Мақсатты жылдамдыққа жетті\n"));
}

// Белгіленген үдеумен жылдамдықты тегіс өзгерту функциясы
// targetSpeed: мақсатты жылдамдық (-100-ден 100-ге дейін)
// acceleration: үдеу (жылдамдық бірліктері әр қадамда)
// stepDelay: қадамдар арасындағы кідіріс миллисекундпен
void smoothSetSpeedAccel(int targetSpeed, int acceleration, unsigned long stepDelay) {
  int currentSpeed = motor.getSpeed();

  Serial.print(F("Үдеумен тегіс өзгерту "));
  Serial.print(acceleration);
  Serial.print(F(": "));
  Serial.print(currentSpeed);
  Serial.print(F(" → "));
  Serial.println(targetSpeed);

  while (currentSpeed != targetSpeed) {
    int diff = targetSpeed - currentSpeed;

    if (abs(diff) <= acceleration) {
      // Мақсатты жылдамдыққа жетеміз
      currentSpeed = targetSpeed;
    } else if (diff > 0) {
      // Жылдамдықты арттырамыз
      currentSpeed += acceleration;
    } else {
      // Жылдамдықты азайтамыз
      currentSpeed -= acceleration;
    }

    motor.setSpeed(currentSpeed);
    delay(stepDelay);
  }

  Serial.println(F("  ✓ Мақсатты жылдамдыққа жетілді\n"));
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  ЖЫЛДАМДЫҚТЫҢ ТЕГІС ӨЗГЕРУІ (RAMPING)         ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== САЛЫСТЫРУ: Кенеттік VS Тегіс ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("САЛЫСТЫРУ: Кенеттік vs Тегіс өзгеру"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("❌ КЕНЕТТІК өзгеру (механиканы зақымдауы мүмкін):"));
  motor.setSpeed(0);
  delay(500);
  Serial.println(F("motor.setSpeed(100) - лезде секіріс!"));
  motor.setSpeed(100);
  delay(2000);

  motor.stop();
  delay(1000);

  Serial.println(F("\n✓ ТЕГІС өзгеру (механикаға қауіпсіз):"));
  motor.setSpeed(0);
  delay(500);
  smoothSetSpeed(100, 2000);  // 2 секундта тегіс жеделдету
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== ӘРТҮРЛІ ЖЕДЕЛДЕТУ УАҚЫТТАРЫ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ӘРТҮРЛІ ЖЕДЕЛДЕТУ УАҚЫТТАРЫ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Жылдам жеделдету (1 секунд):"));
  smoothSetSpeed(80, 1000);
  delay(1000);
  smoothSetSpeed(0, 1000);
  delay(1000);

  Serial.println(F("→ Орташа жеделдету (2 секунд):"));
  smoothSetSpeed(80, 2000);
  delay(1000);
  smoothSetSpeed(0, 2000);
  delay(1000);

  Serial.println(F("→ Баяу жеделдету (3 секунд):"));
  smoothSetSpeed(80, 3000);
  delay(1000);
  smoothSetSpeed(0, 3000);
  delay(2000);

  // ========== ҮДЕУ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ҮДЕУДІ БАСҚАРУ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Кіші үдеу (тегіс):"));
  smoothSetSpeedAccel(90, 2, 50);  // +2 бірлік әр 50мс
  delay(1000);
  smoothSetSpeedAccel(0, 2, 50);
  delay(1000);

  Serial.println(F("→ Орташа үдеу:"));
  smoothSetSpeedAccel(90, 5, 50);  // +5 бірлік әр 50мс
  delay(1000);
  smoothSetSpeedAccel(0, 5, 50);
  delay(1000);

  Serial.println(F("→ Үлкен үдеу (жылдам):"));
  smoothSetSpeedAccel(90, 10, 50);  // +10 бірлік әр 50мс
  delay(1000);
  smoothSetSpeedAccel(0, 10, 50);
  delay(2000);

  // ========== РЕВЕРС ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ТЕГІС РЕВЕРС"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Алға жеделдету:"));
  smoothSetSpeed(70, 2000);
  delay(1000);

  Serial.println(F("→ Тегіс тоқтау:"));
  smoothSetSpeed(0, 1500);
  delay(500);

  Serial.println(F("→ Артқа жеделдету:"));
  smoothSetSpeed(-70, 2000);
  delay(1000);

  Serial.println(F("→ Тегіс тоқтау:"));
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== ТІКЕЛЕЙ РЕВЕРС ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ТІКЕЛЕЙ РЕВЕРС (нөл арқылы)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Алға 60%:"));
  smoothSetSpeed(60, 1500);
  delay(1000);

  Serial.println(F("→ -60%-ға тікелей өту (0 арқылы):"));
  smoothSetSpeed(-60, 3000);  // 0 арқылы тегіс өтеміз
  delay(1000);

  Serial.println(F("→ Тоқтату:"));
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== S-ҚИСЫҚ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("S-ҚИСЫҚ (жетілдірілген техника)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Баяу бастау → жылдам үдеу → тегіс тоқтау\n"));

  // Баяу бастау
  Serial.println(F("  Фаза 1: Баяу бастау"));
  smoothSetSpeedAccel(30, 1, 100);
  delay(500);

  // Жылдам үдеу
  Serial.println(F("  Фаза 2: Жылдам үдеу"));
  smoothSetSpeedAccel(90, 5, 50);
  delay(1000);

  // Тегіс баяулау
  Serial.println(F("  Фаза 3: Тегіс баяулау"));
  smoothSetSpeedAccel(30, 3, 70);
  delay(500);

  // Жұмсақ тоқтау
  Serial.println(F("  Фаза 4: Жұмсақ тоқтау"));
  smoothSetSpeedAccel(0, 1, 100);
  delay(2000);

  // ========== ҰСЫНЫСТАР ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║        ПАЙДАЛАНУ БОЙЫНША ҰСЫНЫСТАР            ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  ӘРҚАШАН тегіс өзгеруді қолданыңыз:           ║"));
  Serial.println(F("║    ✓ Орнынан бастау (0 → жылдамдық)           ║"));
  Serial.println(F("║    ✓ Тоқтату (жылдамдық → 0)                  ║"));
  Serial.println(F("║    ✓ Реверс (+ → -)                           ║"));
  Serial.println(F("║    ✓ Жоғары жылдамдықтар                      ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Ұсынылатын жеделдету уақыттары:              ║"));
  Serial.println(F("║    • Жеңіл роботтар: 1-2 секунд               ║"));
  Serial.println(F("║    • Орташа роботтар: 2-3 секунд              ║"));
  Serial.println(F("║    • Ауыр роботтар: 3-5 секунд                ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Артықшылықтары:                              ║"));
  Serial.println(F("║    • Механиканы тозудан қорғау                ║"));
  Serial.println(F("║    • Шың токты төмендету                      ║"));
  Serial.println(F("║    • Дөңгелектердің жақсы ілінуі             ║"));
  Serial.println(F("║    • Тегіс қозғалыс                           ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл аяқталды. 5 секундтан кейін қайталау...\n\n"));
  delay(5000);
}
