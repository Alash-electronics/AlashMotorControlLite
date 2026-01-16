// Language: Қазақ | English: ../EN/SpeedLimits/ | Русский: ../RU/SpeedLimits/
/*
 * Мысал жылдамдықты автоматты шектеуді көрсетеді
 *
 * Кітапхана жылдамдық мәндерін -100-ден 100-ге дейінгі аралықта автоматты шектейді:
 * - > 100 мәндер автоматты түрде 100 ретінде орнатылады
 * - < -100 мәндер автоматты түрде -100 ретінде орнатылады
 * - Бұл программалау қателіктерінен қорғайды
 *
 * Бұл мысал қорғаудың қалай жұмыс істейтінін және жылдамдық
 * аралығын қалай дұрыс пайдалану керектігін көрсетеді.
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

void testSpeed(int requestedSpeed) {
  motor.setSpeed(requestedSpeed);
  int actualSpeed = motor.getSpeed();

  Serial.print(F("Сұралды: "));
  if (requestedSpeed >= 0) Serial.print(F(" "));
  Serial.print(requestedSpeed);
  Serial.print(F("  →  Орнатылды: "));
  if (actualSpeed >= 0) Serial.print(F(" "));
  Serial.print(actualSpeed);

  if (requestedSpeed != actualSpeed) {
    Serial.print(F("  ⚠ ШЕКТЕЛДІ!"));
  } else {
    Serial.print(F("  ✓"));
  }

  Serial.println();
  delay(500);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  ЖЫЛДАМДЫҚТЫ АВТОМАТТЫ ШЕКТЕУ                 ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== РҰҚСАТ ЕТІЛГЕН МӘНДЕРДІ ТЕСТІЛЕУ ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("РҰҚСАТ ЕТІЛГЕН МӘНДЕР (-100-ден 100-ге дейін)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Оң жылдамдықтарды тестілеу:"));
  testSpeed(0);
  testSpeed(25);
  testSpeed(50);
  testSpeed(75);
  testSpeed(100);

  Serial.println(F("\nТеріс жылдамдықтарды тестілеу:"));
  testSpeed(0);
  testSpeed(-25);
  testSpeed(-50);
  testSpeed(-75);
  testSpeed(-100);

  motor.stop();
  delay(2000);

  // ========== ШЕКТЕН АСУДЫ ТЕСТІЛЕУ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ЖОҒАРЫ ШЕКТЕН АСУЫ (+100)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Кітапхана мәндерді автоматты түрде шектейді:\n"));

  testSpeed(100);   // Норма
  testSpeed(101);   // 100-ге дейін шектеледі
  testSpeed(120);   // 100-ге дейін шектеледі
  testSpeed(150);   // 100-ге дейін шектеледі
  testSpeed(200);   // 100-ге дейін шектеледі
  testSpeed(255);   // 100-ге дейін шектеледі
  testSpeed(500);   // 100-ге дейін шектеледі
  testSpeed(1000);  // 100-ге дейін шектеледі
  testSpeed(32767); // 100-ге дейін шектеледі

  motor.stop();
  delay(2000);

  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ТӨМЕНГІ ШЕКТЕН АСУЫ (-100)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Кітапхана мәндерді автоматты түрде шектейді:\n"));

  testSpeed(-100);   // Норма
  testSpeed(-101);   // -100-ге дейін шектеледі
  testSpeed(-120);   // -100-ге дейін шектеледі
  testSpeed(-150);   // -100-ге дейін шектеледі
  testSpeed(-200);   // -100-ге дейін шектеледі
  testSpeed(-255);   // -100-ге дейін шектеледі
  testSpeed(-500);   // -100-ге дейін шектеледі
  testSpeed(-1000);  // -100-ге дейін шектеледі
  testSpeed(-32768); // -100-ге дейін шектеледі

  motor.stop();
  delay(2000);

  // ========== ПРАКТИКАЛЫҚ МЫСАЛДАР ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ПРАКТИКАЛЫҚ МЫСАЛДАР"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Мысал 1: Жылдамдықтарды қауіпсіз қосу\n"));

  Serial.println(F("int baseSpeed = 80;"));
  Serial.println(F("int boost = 30;"));
  Serial.println(F("motor.setSpeed(baseSpeed + boost);  // 80 + 30 = 110\n"));

  int baseSpeed = 80;
  int boost = 30;

  Serial.print(F("Нәтиже: "));
  testSpeed(baseSpeed + boost);  // Автоматты 100-ге дейін шектеледі

  Serial.println(F("\nКітапхана асып кетуден қорғайды!\n"));
  delay(2000);

  Serial.println(F("Мысал 2: Пайыздарды пайдалану\n"));

  Serial.println(F("int userInput = 150;  // Пайдаланушы 150% енгізді"));
  Serial.println(F("motor.setSpeed(userInput);\n"));

  int userInput = 150;
  Serial.print(F("Нәтиже: "));
  testSpeed(userInput);  // Автоматты 100-ге дейін шектеледі

  Serial.println(F("\nДұрыс емес енгізу де қауіпсіз!\n"));
  delay(2000);

  Serial.println(F("Мысал 3: Математикалық есептеулер\n"));

  Serial.println(F("int sensorValue = analogRead(A0);  // 0-1023"));
  Serial.println(F("int speed = map(sensorValue, 0, 1023, -200, 200);"));
  Serial.println(F("motor.setSpeed(speed);\n"));

  // Датчиктің әртүрлі мәндерін имитациялаймыз
  Serial.println(F("sensorValue = 0 кезінде:"));
  testSpeed(-200);  // -100-ге дейін шектеледі

  Serial.println(F("sensorValue = 512 кезінде:"));
  testSpeed(0);     // Ортасы

  Serial.println(F("sensorValue = 1023 кезінде:"));
  testSpeed(200);   // 100-ге дейін шектеледі

  Serial.println(F("\nДұрыс емес map() кезінде де қорғау жұмыс істейді!\n"));

  motor.stop();
  delay(2000);

  // ========== ШЕКАРАЛЫҚ МӘНДЕР ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ШЕКАРАЛЫҚ МӘНДЕР"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Аралықтың нақты шекаралары:\n"));

  testSpeed(99);    // Максимумға дейін соңғы рұқсат етілген
  testSpeed(100);   // Максимум
  testSpeed(101);   // Бірінші шектелетін

  Serial.println();

  testSpeed(-99);   // Минимумға дейін соңғы рұқсат етілген
  testSpeed(-100);  // Минимум
  testSpeed(-101);  // Бірінші шектелетін

  motor.stop();
  delay(2000);

  // ========== ҰСЫНЫСТАР ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║        ПАЙДАЛАНУ БОЙЫНША ҰСЫНЫСТАР            ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  Жылдамдық аралығы: -100-ден 100-ге дейін     ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Мәндер:                                       ║"));
  Serial.println(F("║    -100 = Артқа толық жылдамдық               ║"));
  Serial.println(F("║      -50 = 50% артқа                          ║"));
  Serial.println(F("║        0 = Тоқтау                             ║"));
  Serial.println(F("║      +50 = 50% алға                           ║"));
  Serial.println(F("║     +100 = Алға толық жылдамдық               ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Қорғау автоматты жұмыс істейді:              ║"));
  Serial.println(F("║    • > 100 мәндер → 100 орнатылады            ║"));
  Serial.println(F("║    • < -100 мәндер → -100 орнатылады          ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Жақсы практика:                              ║"));
  Serial.println(F("║    ✓ setSpeed() алдында constrain() қолданыңыз ║"));
  Serial.println(F("║    ✓ map() дұрыстығын тексеріңіз             ║"));
  Serial.println(F("║    ✓ Пайдаланушы енгізуін тексеріңіз         ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Бірақ ұмытсаңыз да - қорғау іске қосылады!   ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  // ========== КОД МЫСАЛЫ ==========
  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║              КОД МЫСАЛДАРЫ                    ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("// Дұрыс: тексерумен"));
  Serial.println(F("int speed = analogRead(A0);"));
  Serial.println(F("speed = map(speed, 0, 1023, -100, 100);"));
  Serial.println(F("motor.setSpeed(speed);\n"));

  Serial.println(F("// Бұл да жұмыс істейді: кітапхана қорғайды"));
  Serial.println(F("int speed = analogRead(A0);"));
  Serial.println(F("speed = map(speed, 0, 1023, -200, 200);"));
  Serial.println(F("motor.setSpeed(speed);  // Автоматты шектеледі\n"));

  Serial.println(F("// Қосымша қорғаумен:"));
  Serial.println(F("int speed = getUserInput();"));
  Serial.println(F("speed = constrain(speed, -100, 100);"));
  Serial.println(F("motor.setSpeed(speed);  // Қос қорғау\n"));

  Serial.println(F("Цикл аяқталды. 5 секундтан кейін қайталау...\n\n"));
  delay(5000);
}
