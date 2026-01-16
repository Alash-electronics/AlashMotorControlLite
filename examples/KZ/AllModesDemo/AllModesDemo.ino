/*
 * Language: Қазақ | English: ../EN/AllModesDemo/ | Русский: ../RU/AllModesDemo/
 *
 * Бұл мысал қозғалтқыш драйверлерінің барлық 4 режимін көрсетеді:
 * 1. DIR_PWM      - 1 цифрлық + 1 ШИМ пин
 * 2. PWM_PWM      - 2 ШИМ пин
 * 3. DIR_DIR_PWM  - 2 цифрлық + 1 ШИМ пин
 * 4. DIR_DIR      - 2 цифрлық пин (ШИМ-сыз)
 *
 * Әрбір режим белгілі бір драйвер түрлеріне сәйкес келеді.
 * Драйверіңізге сәйкес режимді таңдаңыз!
 *
 * МАҢЫЗДЫ: Бұл мысал көрсету үшін. Нақты жобада
 * драйверіңіз үшін тек БІР режимді қолданыңыз!
 *
 * Код Alash engineering үшін жазылған
 */

#include "AlashMotorControlLite.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  БАРЛЫҚ ЖҰМЫС РЕЖИМДЕРІН САЛЫСТЫРУ            ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== РЕЖИМ 1: DIR_PWM ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("РЕЖИМ 1: DIR_PWM"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Сипаттамасы:"));
  Serial.println(F("  • 1 цифрлық пин (DIR) - бағыт"));
  Serial.println(F("  • 1 ШИМ пин (PWM) - жылдамдық\n"));

  Serial.println(F("Қосылым:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(DIR_PWM, 4, 3);"));
  Serial.println(F("           PIN 4 → DIR (бағыт)"));
  Serial.println(F("           PIN 3 → PWM (жылдамдық)\n"));

  Serial.println(F("Үйлесімді драйверлер:"));
  Serial.println(F("  • TB6612FNG"));
  Serial.println(F("  • DRV8833"));
  Serial.println(F("  • Көпшілік H-Bridge модульдері\n"));

  Serial.println(F("Жұмыс принципі:"));
  Serial.println(F("  DIR=LOW,  PWM=128 → Алға 50%"));
  Serial.println(F("  DIR=HIGH, PWM=128 → Артқа 50%"));
  Serial.println(F("  DIR=X,    PWM=0   → Тоқтату\n"));

  Serial.println(F("Артықшылықтары:"));
  Serial.println(F("  ✓ Қарапайым қосылым"));
  Serial.println(F("  ✓ Интуитивті түсінікті логика"));
  Serial.println(F("  ✓ Пиндерді үнемдеу\n"));

  Serial.println(F("Кемшіліктері:"));
  Serial.println(F("  ✗ Жылдамдық үшін ШИМ пин қажет\n"));

  delay(5000);

  // ========== РЕЖИМ 2: PWM_PWM ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РЕЖИМ 2: PWM_PWM"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Сипаттамасы:"));
  Serial.println(F("  • 2 ШИМ пин (IN1, IN2)"));
  Serial.println(F("  • Әрбір пин бағытты басқарады\n"));

  Serial.println(F("Қосылым:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(PWM_PWM, 9, 10);"));
  Serial.println(F("           PIN 9  → IN1"));
  Serial.println(F("           PIN 10 → IN2\n"));

  Serial.println(F("  ESP32:   AlashMotorControlLite motor(PWM_PWM, 32, 33);"));
  Serial.println(F("           GPIO 32 → IN1"));
  Serial.println(F("           GPIO 33 → IN2\n"));

  Serial.println(F("Үйлесімді драйверлер:"));
  Serial.println(F("  • ZK-5AD ★ ESP32 ҮШІН ҰСЫНЫЛАДЫ"));
  Serial.println(F("  • L298N"));
  Serial.println(F("  • BTS7960"));
  Serial.println(F("  • Екі арналы H-Bridge\n"));

  Serial.println(F("Жұмыс принципі:"));
  Serial.println(F("  IN1=128, IN2=0   → Алға 50%"));
  Serial.println(F("  IN1=0,   IN2=128 → Артқа 50%"));
  Serial.println(F("  IN1=0,   IN2=0   → Тоқтату"));
  Serial.println(F("  IN1=255, IN2=255 → Тежеу\n"));

  Serial.println(F("Артықшылықтары:"));
  Serial.println(F("  ✓ Бағыттарды тәуелсіз басқару"));
  Serial.println(F("  ✓ Тежеуді жақсы басқару"));
  Serial.println(F("  ✓ ESP32 үшін өте жақсы (көп ШИМ арналар)\n"));

  Serial.println(F("Кемшіліктері:"));
  Serial.println(F("  ✗ 2 ШИМ пин қажет"));
  Serial.println(F("  ✗ Arduino-да ШИМ пиндер шектеулі\n"));

  delay(5000);

  // ========== РЕЖИМ 3: DIR_DIR_PWM ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РЕЖИМ 3: DIR_DIR_PWM"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Сипаттамасы:"));
  Serial.println(F("  • 2 цифрлық пин (IN1, IN2) - бағыт"));
  Serial.println(F("  • 1 ШИМ пин (PWM/EN) - жылдамдық\n"));

  Serial.println(F("Қосылым:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);"));
  Serial.println(F("           PIN 4 → IN1 (бағыт 1)"));
  Serial.println(F("           PIN 5 → IN2 (бағыт 2)"));
  Serial.println(F("           PIN 6 → PWM/EN (жылдамдық)\n"));

  Serial.println(F("Үйлесімді драйверлер:"));
  Serial.println(F("  • L298N (EN пинімен)"));
  Serial.println(F("  • L293D"));
  Serial.println(F("  • Бөлек Enable пині бар драйверлер\n"));

  Serial.println(F("Жұмыс принципі:"));
  Serial.println(F("  IN1=HIGH, IN2=LOW,  PWM=128 → Алға 50%"));
  Serial.println(F("  IN1=LOW,  IN2=HIGH, PWM=128 → Артқа 50%"));
  Serial.println(F("  IN1=X,    IN2=X,    PWM=0   → Тоқтату"));
  Serial.println(F("  IN1=HIGH, IN2=HIGH, PWM=255 → Тежеу\n"));

  Serial.println(F("Артықшылықтары:"));
  Serial.println(F("  ✓ Бағыт пен жылдамдықты анық бөлу"));
  Serial.println(F("  ✓ ШИМ пиндерді үнемдеу (тек 1)"));
  Serial.println(F("  ✓ Жақсы үйлесімділік\n"));

  Serial.println(F("Кемшіліктері:"));
  Serial.println(F("  ✗ Қозғалтқышқа 3 пин қажет"));
  Serial.println(F("  ✗ Қосылым біршама күрделі\n"));

  delay(5000);

  // ========== РЕЖИМ 4: DIR_DIR ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РЕЖИМ 4: DIR_DIR"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Сипаттамасы:"));
  Serial.println(F("  • 2 цифрлық пин (IN1, IN2)"));
  Serial.println(F("  • ШИМ-СЫЗ - тек қосу/өшіру және бағыт\n"));

  Serial.println(F("Қосылым:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(DIR_DIR, 4, 5);"));
  Serial.println(F("           PIN 4 → IN1"));
  Serial.println(F("           PIN 5 → IN2\n"));

  Serial.println(F("Үйлесімді драйверлер:"));
  Serial.println(F("  • Релейлік модульдер"));
  Serial.println(F("  • ШИМ-сыз қарапайым H-Bridge"));
  Serial.println(F("  • Ішкі жылдамдық контроллері бар драйверлер\n"));

  Serial.println(F("Жұмыс принципі:"));
  Serial.println(F("  IN1=HIGH, IN2=LOW  → Алға (толық жылдамдық)"));
  Serial.println(F("  IN1=LOW,  IN2=HIGH → Артқа (толық жылдамдық)"));
  Serial.println(F("  IN1=LOW,  IN2=LOW  → Тоқтату"));
  Serial.println(F("  IN1=HIGH, IN2=HIGH → Тежеу\n"));

  Serial.println(F("МАҢЫЗДЫ: Бұл режимде setSpeed() келесідей жұмыс істейді:"));
  Serial.println(F("  speed > 0  → Алға (толық)"));
  Serial.println(F("  speed < 0  → Артқа (толық)"));
  Serial.println(F("  speed == 0 → Тоқтату"));
  Serial.println(F("  Жылдамдық мәні ескерілмейді!\n"));

  Serial.println(F("Артықшылықтары:"));
  Serial.println(F("  ✓ ШИМ пиндер қажет емес"));
  Serial.println(F("  ✓ Ең қарапайым қосылым"));
  Serial.println(F("  ✓ ШИМ кірісі жоқ драйверлер үшін\n"));

  Serial.println(F("Кемшіліктері:"));
  Serial.println(F("  ✗ Жылдамдықты реттеу жоқ"));
  Serial.println(F("  ✗ Тек толық жылдамдық қосу/өшіру\n"));

  delay(5000);

  // ========== САЛЫСТЫРМАЛЫ КЕСТЕ ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════════════════╗"));
  Serial.println(F("║              САЛЫСТЫРМАЛЫ КЕСТЕ                           ║"));
  Serial.println(F("╠═══════════════╦═══════╦═══════╦═══════════╦═══════════════╣"));
  Serial.println(F("║ Режим         ║ Пиндер║ ШИМ   ║ Жылдамдық ║ Қолдану       ║"));
  Serial.println(F("╠═══════════════╬═══════╬═══════╬═══════════╬═══════════════╣"));
  Serial.println(F("║ DIR_PWM       ║  2    ║  1    ║ Иә        ║ Әмбебап       ║"));
  Serial.println(F("║ PWM_PWM       ║  2    ║  2    ║ Иә        ║ ESP32 + ZK-5AD║"));
  Serial.println(F("║ DIR_DIR_PWM   ║  3    ║  1    ║ Иә        ║ L298N с EN    ║"));
  Serial.println(F("║ DIR_DIR       ║  2    ║  0    ║ Жоқ       ║ Реле/On-Off   ║"));
  Serial.println(F("╚═══════════════╩═══════╩═══════╩═══════════╩═══════════════╝\n"));

  // ========== ҰСЫНЫСТАР ==========
  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║           РЕЖИМДІ ҚАЛАЙ ТАҢДАУ КЕРЕК?         ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  1. Драйверіңіздің datasheet-ін қараңыз      ║"));
  Serial.println(F("║  2. Кіріс түрін анықтаңыз:                    ║"));
  Serial.println(F("║     • DIR + PWM → DIR_PWM                     ║"));
  Serial.println(F("║     • IN1 + IN2 (екеуі де ШИМ) → PWM_PWM      ║"));
  Serial.println(F("║     • IN1 + IN2 + EN → DIR_DIR_PWM            ║"));
  Serial.println(F("║     • Тек қосу/өшіру → DIR_DIR                ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Танымал драйверлер:                          ║"));
  Serial.println(F("║  • L298N        → DIR_DIR_PWM немесе PWM_PWM  ║"));
  Serial.println(F("║  • TB6612FNG    → DIR_PWM                     ║"));
  Serial.println(F("║  • ZK-5AD       → PWM_PWM                     ║"));
  Serial.println(F("║  • DRV8833      → DIR_PWM                     ║"));
  Serial.println(F("║  • BTS7960      → PWM_PWM                     ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл аяқталды. 10 секундтан кейін қайталау...\n\n"));
  delay(10000);
}
