// Language: Қазақ | English: ../EN/StopVsBrake/ | Русский: ../RU/StopVsBrake/
/*
 * Пример демонстрирует разницу между методами stop() и brake()
 *
 * stop()  - Свободная остановка (coast)
 *           Мотор просто отключается и останавливается по инерции
 *           Используется для плавной остановки без нагрузки на механику
 *
 * brake() - Активное торможение
 *           Мотор активно тормозит, создавая сопротивление
 *           Используется для быстрой остановки или удержания позиции
 *
 * Подключение:
 * Arduino: Motor DIR -> Pin 4, PWM -> Pin 3 (режим DIR_PWM)
 * ESP32:   Motor IN1 -> GPIO 32, IN2 -> GPIO 33 (режим PWM_PWM)
 *
 * ВАЖНО: Разница наиболее заметна при высоких скоростях и большой инерции!
 *
 * Код написан для Alash engineering
 */

#include "AlashMotorControlLite.h"

// Выберите режим для вашей платформы:
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
  Serial.println(F("║    СРАВНЕНИЕ stop() VS brake()               ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Этот пример показывает разницу между двумя способами остановки мотора.\n"));
  delay(2000);
}

void loop() {
  // ========== ТЕСТ 1: Свободная остановка stop() ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("ТЕСТ 1: Свободная остановка - stop()"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Мотор разгоняется до 100%..."));

  motor.setSpeed(100);
  delay(2000);  // Даем мотору разогнаться

  Serial.println(F("→ Вызов motor.stop()"));
  Serial.println(F("  Мотор отключается и останавливается по инерции"));
  Serial.println(F("  Наблюдайте: плавная остановка, долгий выбег\n"));

  motor.stop();  // Свободная остановка
  delay(4000);   // Ждем полной остановки

  Serial.println(F("Пауза 2 секунды...\n"));
  delay(2000);

  // ========== ТЕСТ 2: Активное торможение brake() ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("ТЕСТ 2: Активное торможение - brake()"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Мотор разгоняется до 100%..."));

  motor.setSpeed(100);
  delay(2000);  // Даем мотору разогнаться

  Serial.println(F("→ Вызов motor.brake()"));
  Serial.println(F("  Мотор активно тормозит"));
  Serial.println(F("  Наблюдайте: быстрая остановка, короткий выбег\n"));

  motor.brake();  // Активное торможение
  delay(4000);    // Ждем полной остановки

  Serial.println(F("Пауза 2 секунды...\n"));
  delay(2000);

  // ========== СРАВНЕНИЕ В ОБРАТНОМ НАПРАВЛЕНИИ ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("ТЕСТ 3: Сравнение при движении назад"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  // Движение назад с stop()
  Serial.println(F("Назад 100% → stop()"));
  motor.setSpeed(-100);
  delay(2000);
  motor.stop();
  delay(3000);

  Serial.println(F("Пауза...\n"));
  delay(2000);

  // Движение назад с brake()
  Serial.println(F("Назад 100% → brake()"));
  motor.setSpeed(-100);
  delay(2000);
  motor.brake();
  delay(3000);

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║           КОГДА ЧТО ИСПОЛЬЗОВАТЬ?             ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  stop() - Свободная остановка:                ║"));
  Serial.println(F("║    ✓ Плавная остановка без рывков             ║"));
  Serial.println(F("║    ✓ Меньше нагрузка на механику              ║"));
  Serial.println(F("║    ✓ Экономия энергии                         ║"));
  Serial.println(F("║    ✗ Медленная остановка                      ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  brake() - Активное торможение:               ║"));
  Serial.println(F("║    ✓ Быстрая остановка                        ║"));
  Serial.println(F("║    ✓ Удержание позиции под нагрузкой          ║"));
  Serial.println(F("║    ✓ Точная остановка                         ║"));
  Serial.println(F("║    ✗ Больше нагрузка на механику              ║"));
  Serial.println(F("║    ✗ Больше потребление энергии               ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл завершен. Повтор через 5 секунд...\n\n"));
  delay(5000);
}
