// Language: Қазақ | English: ../EN/StopVsBrake/ | Русский: ../RU/StopVsBrake/
/*
 * Бұл мысал stop() және brake() әдістерінің айырмашылығын көрсетеді
 *
 * stop()  - Еркін тоқтату (coast)
 *           Қозғалтқыш өшеді және инерция бойынша тоқтайды
 *           Механикаға жүктемесіз тегіс тоқтату үшін қолданылады
 *
 * brake() - Белсенді тежеу
 *           Қозғалтқыш белсенді тежейді, кедергі жасайды
 *           Жылдам тоқтату немесе позицияны ұстап тұру үшін қолданылады
 *
 * Қосылым:
 * Arduino: Motor DIR -> Pin 4, PWM -> Pin 3 (режим DIR_PWM)
 * ESP32:   Motor IN1 -> GPIO 32, IN2 -> GPIO 33 (режим PWM_PWM)
 *
 * МАҢЫЗДЫ: Айырмашылық жоғары жылдамдықта және үлкен инерцияда айқын көрінеді!
 *
 * Код Alash engineering үшін жазылған
 */

#include "AlashMotorControlLite.h"

// Платформаңыз үшін режимді таңдаңыз:
#if defined(ARDUINO_ARCH_ESP32)
  // ESP32 - режим PWM_PWM
  AlashMotorControlLite motor(PWM_PWM, 32, 33);
#else
  // Arduino - режим DIR_PWM
  AlashMotorControlLite motor(DIR_PWM, 4, 3);
#endif

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║    stop() VS brake() САЛЫСТЫРУ                ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Бұл мысал қозғалтқышты тоқтатудың екі тәсілі арасындағы айырмашылықты көрсетеді.\n"));
  delay(2000);
}

void loop() {
  // ========== СЫНАҚ 1: Еркін тоқтату stop() ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СЫНАҚ 1: Еркін тоқтату - stop()"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Қозғалтқыш 100% дейін жеделдетеді..."));

  motor.setSpeed(100);
  delay(2000);  // Қозғалтқышқа жеделдету үшін уақыт береміз

  Serial.println(F("→ motor.stop() шақыру"));
  Serial.println(F("  Қозғалтқыш өшеді және инерция бойынша тоқтайды"));
  Serial.println(F("  Бақылаңыз: тегіс тоқтату, ұзақ тоқтау\n"));

  motor.stop();  // Еркін тоқтату
  delay(4000);   // Толық тоқтауын күтеміз

  Serial.println(F("2 секунд кідіріс...\n"));
  delay(2000);

  // ========== СЫНАҚ 2: Белсенді тежеу brake() ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СЫНАҚ 2: Белсенді тежеу - brake()"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Қозғалтқыш 100% дейін жеделдетеді..."));

  motor.setSpeed(100);
  delay(2000);  // Қозғалтқышқа жеделдету үшін уақыт береміз

  Serial.println(F("→ motor.brake() шақыру"));
  Serial.println(F("  Қозғалтқыш белсенді тежейді"));
  Serial.println(F("  Бақылаңыз: жылдам тоқтату, қысқа тоқтау\n"));

  motor.brake();  // Белсенді тежеу
  delay(4000);    // Толық тоқтауын күтеміз

  Serial.println(F("2 секунд кідіріс...\n"));
  delay(2000);

  // ========== КЕРІ БАҒЫТТА САЛЫСТЫРУ ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СЫНАҚ 3: Артқа қозғалыс кезінде салыстыру"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  // stop() арқылы артқа қозғалыс
  Serial.println(F("Артқа 100% → stop()"));
  motor.setSpeed(-100);
  delay(2000);
  motor.stop();
  delay(3000);

  Serial.println(F("Кідіріс...\n"));
  delay(2000);

  // brake() арқылы артқа қозғалыс
  Serial.println(F("Артқа 100% → brake()"));
  motor.setSpeed(-100);
  delay(2000);
  motor.brake();
  delay(3000);

  // ========== ҰСЫНЫСТАР ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║           ҚАШАН НЕНІ ҚОЛДАНУ КЕРЕК?           ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  stop() - Еркін тоқтату:                      ║"));
  Serial.println(F("║    ✓ Секірістерсіз тегіс тоқтату              ║"));
  Serial.println(F("║    ✓ Механикаға аз жүктеме                    ║"));
  Serial.println(F("║    ✓ Энергияны үнемдеу                        ║"));
  Serial.println(F("║    ✗ Баяу тоқтату                             ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  brake() - Белсенді тежеу:                    ║"));
  Serial.println(F("║    ✓ Жылдам тоқтату                           ║"));
  Serial.println(F("║    ✓ Жүктеме астында позицияны ұстау          ║"));
  Serial.println(F("║    ✓ Дәл тоқтату                              ║"));
  Serial.println(F("║    ✗ Механикаға көп жүктеме                   ║"));
  Serial.println(F("║    ✗ Энергияны көп тұтыну                     ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл аяқталды. 5 секундтан кейін қайталау...\n\n"));
  delay(5000);
}
