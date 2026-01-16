// Language: Қазақ | English: ../EN/DirectionChange/ | Русский: ../RU/DirectionChange/
/*
 * Бұл мысал қозғалтқыштың бағытын өзгертудің әртүрлі тәсілдерін көрсетеді
 *
 * Бағытты өзгерту келесідей орындалуы мүмкін:
 * 1. Кенет (лезде) - ҰСЫНЫЛМАЙДЫ
 * 2. Аралығында тоқтатумен - ҚАУІПСІЗ
 * 3. Нөл арқылы тегіс - ҰСЫНЫЛАДЫ
 *
 * Дұрыс бағытты өзгерту маңызды:
 * - Механиканы соққы жүктемелерінен қорғау үшін
 * - Қозғалтқыштардың қызмет ету мерзімін ұзарту үшін
 * - Редукторлардың зақымдалуын болдырмау үшін
 * - Шыңғы ток тұтынуын азайту үшін
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

// Жылдамдықты тегіс өзгерту функциясы
void smoothSetSpeed(int targetSpeed, unsigned long rampTime) {
  int currentSpeed = motor.getSpeed();
  int speedDiff = targetSpeed - currentSpeed;
  int steps = abs(speedDiff);

  if (steps == 0) return;

  unsigned long stepDelay = rampTime / steps;

  if (speedDiff > 0) {
    for (int speed = currentSpeed + 1; speed <= targetSpeed; speed++) {
      motor.setSpeed(speed);
      delay(stepDelay);
    }
  } else {
    for (int speed = currentSpeed - 1; speed >= targetSpeed; speed--) {
      motor.setSpeed(speed);
      delay(stepDelay);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  БАҒЫТТЫ ӨЗГЕРТУДІ КӨРСЕТУ                    ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== ТӘСІЛ 1: КЕНЕТ ӨЗГЕРТУ (ҚАУІПТІ!) ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("ТӘСІЛ 1: Бағытты кенет өзгерту ❌ ҚАУІПТІ!"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("⚠ НАҚТЫ ЖОБАЛАРДА ҚОЛДАНБАҢЫЗ!\n"));

  Serial.println(F("→ Алға 100% дейін жеделдету"));
  motor.setSpeed(100);
  delay(2000);

  Serial.println(F("⚠ КЕНЕТ -100% ға өзгерту (лездік реверс)"));
  Serial.println(F("  Қауіпті:"));
  Serial.println(F("  • Қозғалтқыштарға (шамадан тыс жүктеме)"));
  Serial.println(F("  • Редукторларға (соққы жүктемесі)"));
  Serial.println(F("  • Драйверге (шыңғы ток)"));
  Serial.println(F("  • Механикаға (тозу)\n"));

  motor.setSpeed(-100);  // НАШАР!
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== ТӘСІЛ 2: ТОҚТАТУМЕН (ҚАУІПСІЗ) ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ТӘСІЛ 2: Тоқтатумен өзгерту ✓ ҚАУІПСІЗ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Алға 80% дейін жеделдету"));
  motor.setSpeed(80);
  delay(2000);

  Serial.println(F("→ Тоқтату"));
  motor.stop();
  delay(500);  // Толық тоқтату үшін кідіріс

  Serial.println(F("✓ Толық тоқтату үшін 500мс кідіріс"));
  delay(500);

  Serial.println(F("→ Артқа 80% дейін жеделдету"));
  motor.setSpeed(-80);
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== ТӘСІЛ 3: ТЕГІС ӨЗГЕРТУ (ҰСЫНЫЛАДЫ) ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ТӘСІЛ 3: Тегіс өзгерту ★ ҰСЫНЫЛАДЫ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Алға 70% дейін тегіс жеделдету"));
  smoothSetSpeed(70, 2000);
  delay(1500);

  Serial.println(F("→ -70% ға тегіс өзгерту (нөл арқылы)"));
  Serial.println(F("  Артықшылықтары:"));
  Serial.println(F("  ✓ Механиканы қорғау"));
  Serial.println(F("  ✓ Тегіс қозғалыс"));
  Serial.println(F("  ✓ Төмен шыңғы ток"));
  Serial.println(F("  ✓ Ұзақ қызмет ету мерзімі\n"));

  smoothSetSpeed(-70, 3000);  // КЕРЕМЕТ!
  delay(1500);

  Serial.println(F("→ Тегіс тоқтату"));
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== РЕВЕРСТІҢ ӘРТҮРЛІ ЖЫЛДАМДЫҚТАРЫ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РЕВЕРСТІҢ ӘРТҮРЛІ ЖЫЛДАМДЫҚТАРЫ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Жылдам реверс (1.5 секунд):"));
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 1500);
  delay(1000);
  smoothSetSpeed(0, 1000);
  delay(1000);

  Serial.println(F("\n→ Орташа реверс (3 секунд):"));
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 3000);
  delay(1000);
  smoothSetSpeed(0, 1500);
  delay(1000);

  Serial.println(F("\n→ Баяу реверс (5 секунд):"));
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 5000);
  delay(1000);
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== ЖИІ РЕВЕРСТЕР ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ЖИІ РЕВЕРСТЕР (маятникті қозғалыс)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Көрсету: алға-артқа 5 рет\n"));

  for (int i = 1; i <= 5; i++) {
    Serial.print(F("Цикл "));
    Serial.print(i);
    Serial.println(F("/5:"));

    Serial.println(F("  → Алға"));
    smoothSetSpeed(50, 1000);
    delay(800);

    Serial.println(F("  ← Артқа"));
    smoothSetSpeed(-50, 2000);
    delay(800);

    Serial.println();
  }

  Serial.println(F("→ Тоқтату"));
  smoothSetSpeed(0, 1000);
  delay(2000);

  // ========== РЕВЕРСТЕ ӘРТҮРЛІ ЖЫЛДАМДЫҚТАР ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РЕВЕРСТЕ ӘРТҮРЛІ ЖЫЛДАМДЫҚТАР"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Алға 80%"));
  smoothSetSpeed(80, 2000);
  delay(1000);

  Serial.println(F("→ -40% ға реверс (төмен жылдамдық)"));
  smoothSetSpeed(-40, 3000);
  delay(1000);

  Serial.println(F("→ Қайта алға 60%"));
  smoothSetSpeed(60, 2500);
  delay(1000);

  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== ЖҮКТЕМЕ КЕЗІНДЕ РЕВЕРС ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ЖҮКТЕМЕ КЕЗІНДЕ РЕВЕРС (ерекше жағдайлар)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Егер қозғалтқыш жүктемеде болса (робот бірдеңені итереді):"));
  Serial.println(F("  1. Реверс уақытын ұлғайтыңыз"));
  Serial.println(F("  2. Нөлдік нүктеде кідіріс қосыңыз"));
  Serial.println(F("  3. Реверстен бұрын brake() қолданыңыз\n"));

  Serial.println(F("Мысал:\n"));

  Serial.println(F("→ Алға 70% (жүктемеде)"));
  smoothSetSpeed(70, 2000);
  delay(2000);

  Serial.println(F("→ Белсенді тежеу"));
  motor.brake();
  delay(300);  // Белсенді тежеу

  Serial.println(F("→ Толық тоқтату үшін кідіріс"));
  motor.stop();
  delay(500);  // Қосымша кідіріс

  Serial.println(F("→ Артқа баяу жеделдету"));
  smoothSetSpeed(-50, 3000);  // Баяу жеделдету
  delay(1500);

  smoothSetSpeed(0, 2000);
  delay(2000);

  // ========== ҰСЫНЫСТАР ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║        БАҒЫТТЫ ӨЗГЕРТУ БОЙЫНША ҰСЫНЫСТАР      ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  ЕШҚАШАН жасамаңыз:                           ║"));
  Serial.println(F("║    ✗ motor.setSpeed(100);                     ║"));
  Serial.println(F("║      motor.setSpeed(-100);  // Нашар!         ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  ӘРҚАШАН қолданыңыз:                          ║"));
  Serial.println(F("║    ✓ Нөл арқылы тегіс өту                     ║"));
  Serial.println(F("║    ✓ Реверстер арасында тоқтату               ║"));
  Serial.println(F("║    ✓ Brake() жылдам тоқтату үшін              ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Ұсынылатын реверс уақыттары:                 ║"));
  Serial.println(F("║    • Жеңіл роботтар: 1.5-2 секунд             ║"));
  Serial.println(F("║    • Орташа роботтар: 2-3 секунд              ║"));
  Serial.println(F("║    • Ауыр роботтар: 3-5 секунд                ║"));
  Serial.println(F("║    • Жүктемеде: +50% уақыт                    ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Жүктемедегі қозғалтқыш үшін реттілік:        ║"));
  Serial.println(F("║    1. smoothSetSpeed() нөлге дейін            ║"));
  Serial.println(F("║    2. brake() - белсенді тежеу                ║"));
  Serial.println(F("║    3. delay() - кідіріс 300-500мс             ║"));
  Serial.println(F("║    4. stop() - өшіру                          ║"));
  Serial.println(F("║    5. delay() - кідіріс 300-500мс             ║"));
  Serial.println(F("║    6. smoothSetSpeed() кері бағытқа           ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл аяқталды. 5 секундтан кейін қайталау...\n\n"));
  delay(5000);
}
