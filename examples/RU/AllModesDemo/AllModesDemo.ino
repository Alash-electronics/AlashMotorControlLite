/*
 * Language: Русский | English: ../EN/AllModesDemo/ | Қазақ: ../KZ/AllModesDemo/
 *
 * Пример демонстрирует все 4 режима работы драйверов моторов:
 * 1. DIR_PWM      - 1 цифровой + 1 ШИМ пин
 * 2. PWM_PWM      - 2 ШИМ пина
 * 3. DIR_DIR_PWM  - 2 цифровых + 1 ШИМ пин
 * 4. DIR_DIR      - 2 цифровых пина (без ШИМ)
 *
 * Каждый режим подходит для определенных типов драйверов.
 * Выберите режим в соответствии с вашим драйвером!
 *
 * ВАЖНО: Этот пример для демонстрации. В реальном проекте
 * используйте только ОДИН режим для вашего драйвера!
 *
 * Код написан для Alash engineering
 */

#include "AlashMotorControlLite.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  СРАВНЕНИЕ ВСЕХ РЕЖИМОВ РАБОТЫ                ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== РЕЖИМ 1: DIR_PWM ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("РЕЖИМ 1: DIR_PWM"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Описание:"));
  Serial.println(F("  • 1 цифровой пин (DIR) - направление"));
  Serial.println(F("  • 1 ШИМ пин (PWM) - скорость\n"));

  Serial.println(F("Подключение:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(DIR_PWM, 4, 3);"));
  Serial.println(F("           PIN 4 → DIR (направление)"));
  Serial.println(F("           PIN 3 → PWM (скорость)\n"));

  Serial.println(F("Совместимые драйверы:"));
  Serial.println(F("  • TB6612FNG"));
  Serial.println(F("  • DRV8833"));
  Serial.println(F("  • Большинство H-Bridge модулей\n"));

  Serial.println(F("Принцип работы:"));
  Serial.println(F("  DIR=LOW,  PWM=128 → Вперед на 50%"));
  Serial.println(F("  DIR=HIGH, PWM=128 → Назад на 50%"));
  Serial.println(F("  DIR=X,    PWM=0   → Остановка\n"));

  Serial.println(F("Преимущества:"));
  Serial.println(F("  ✓ Простое подключение"));
  Serial.println(F("  ✓ Интуитивно понятная логика"));
  Serial.println(F("  ✓ Экономия пинов\n"));

  Serial.println(F("Недостатки:"));
  Serial.println(F("  ✗ Требует ШИМ пин для скорости\n"));

  delay(5000);

  // ========== РЕЖИМ 2: PWM_PWM ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РЕЖИМ 2: PWM_PWM"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Описание:"));
  Serial.println(F("  • 2 ШИМ пина (IN1, IN2)"));
  Serial.println(F("  • Каждый пин управляет направлением\n"));

  Serial.println(F("Подключение:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(PWM_PWM, 9, 10);"));
  Serial.println(F("           PIN 9  → IN1"));
  Serial.println(F("           PIN 10 → IN2\n"));

  Serial.println(F("  ESP32:   AlashMotorControlLite motor(PWM_PWM, 32, 33);"));
  Serial.println(F("           GPIO 32 → IN1"));
  Serial.println(F("           GPIO 33 → IN2\n"));

  Serial.println(F("Совместимые драйверы:"));
  Serial.println(F("  • ZK-5AD ★ РЕКОМЕНДУЕТСЯ для ESP32"));
  Serial.println(F("  • L298N"));
  Serial.println(F("  • BTS7960"));
  Serial.println(F("  • Двухканальные H-Bridge\n"));

  Serial.println(F("Принцип работы:"));
  Serial.println(F("  IN1=128, IN2=0   → Вперед на 50%"));
  Serial.println(F("  IN1=0,   IN2=128 → Назад на 50%"));
  Serial.println(F("  IN1=0,   IN2=0   → Остановка"));
  Serial.println(F("  IN1=255, IN2=255 → Торможение\n"));

  Serial.println(F("Преимущества:"));
  Serial.println(F("  ✓ Независимое управление направлениями"));
  Serial.println(F("  ✓ Лучший контроль торможения"));
  Serial.println(F("  ✓ Идеален для ESP32 (много ШИМ каналов)\n"));

  Serial.println(F("Недостатки:"));
  Serial.println(F("  ✗ Требует 2 ШИМ пина"));
  Serial.println(F("  ✗ На Arduino ограниченно ШИМ пинов\n"));

  delay(5000);

  // ========== РЕЖИМ 3: DIR_DIR_PWM ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РЕЖИМ 3: DIR_DIR_PWM"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Описание:"));
  Serial.println(F("  • 2 цифровых пина (IN1, IN2) - направление"));
  Serial.println(F("  • 1 ШИМ пин (PWM/EN) - скорость\n"));

  Serial.println(F("Подключение:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);"));
  Serial.println(F("           PIN 4 → IN1 (направление 1)"));
  Serial.println(F("           PIN 5 → IN2 (направление 2)"));
  Serial.println(F("           PIN 6 → PWM/EN (скорость)\n"));

  Serial.println(F("Совместимые драйверы:"));
  Serial.println(F("  • L298N (с пином EN)"));
  Serial.println(F("  • L293D"));
  Serial.println(F("  • Драйверы с отдельным Enable пином\n"));

  Serial.println(F("Принцип работы:"));
  Serial.println(F("  IN1=HIGH, IN2=LOW,  PWM=128 → Вперед на 50%"));
  Serial.println(F("  IN1=LOW,  IN2=HIGH, PWM=128 → Назад на 50%"));
  Serial.println(F("  IN1=X,    IN2=X,    PWM=0   → Остановка"));
  Serial.println(F("  IN1=HIGH, IN2=HIGH, PWM=255 → Торможение\n"));

  Serial.println(F("Преимущества:"));
  Serial.println(F("  ✓ Четкое разделение направления и скорости"));
  Serial.println(F("  ✓ Экономия ШИМ пинов (только 1)"));
  Serial.println(F("  ✓ Хорошая совместимость\n"));

  Serial.println(F("Недостатки:"));
  Serial.println(F("  ✗ Требует 3 пина на мотор"));
  Serial.println(F("  ✗ Немного сложнее подключение\n"));

  delay(5000);

  // ========== РЕЖИМ 4: DIR_DIR ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РЕЖИМ 4: DIR_DIR"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Описание:"));
  Serial.println(F("  • 2 цифровых пина (IN1, IN2)"));
  Serial.println(F("  • БЕЗ ШИМ - только вкл/выкл и направление\n"));

  Serial.println(F("Подключение:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(DIR_DIR, 4, 5);"));
  Serial.println(F("           PIN 4 → IN1"));
  Serial.println(F("           PIN 5 → IN2\n"));

  Serial.println(F("Совместимые драйверы:"));
  Serial.println(F("  • Релейные модули"));
  Serial.println(F("  • Простые H-Bridge без ШИМ"));
  Serial.println(F("  • Драйверы со встроенным контроллером скорости\n"));

  Serial.println(F("Принцип работы:"));
  Serial.println(F("  IN1=HIGH, IN2=LOW  → Вперед (полная скорость)"));
  Serial.println(F("  IN1=LOW,  IN2=HIGH → Назад (полная скорость)"));
  Serial.println(F("  IN1=LOW,  IN2=LOW  → Остановка"));
  Serial.println(F("  IN1=HIGH, IN2=HIGH → Торможение\n"));

  Serial.println(F("ВАЖНО: В этом режиме setSpeed() работает как:"));
  Serial.println(F("  speed > 0  → Вперед (полная)"));
  Serial.println(F("  speed < 0  → Назад (полная)"));
  Serial.println(F("  speed == 0 → Остановка"));
  Serial.println(F("  Значение скорости игнорируется!\n"));

  Serial.println(F("Преимущества:"));
  Serial.println(F("  ✓ Не требует ШИМ пинов"));
  Serial.println(F("  ✓ Простейшее подключение"));
  Serial.println(F("  ✓ Для драйверов без ШИМ входа\n"));

  Serial.println(F("Недостатки:"));
  Serial.println(F("  ✗ Нет регулировки скорости"));
  Serial.println(F("  ✗ Только полная скорость вкл/выкл\n"));

  delay(5000);

  // ========== СРАВНИТЕЛЬНАЯ ТАБЛИЦА ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════════════════╗"));
  Serial.println(F("║              СРАВНИТЕЛЬНАЯ ТАБЛИЦА                        ║"));
  Serial.println(F("╠═══════════════╦═══════╦═══════╦═══════════╦═══════════════╣"));
  Serial.println(F("║ Режим         ║ Пины  ║ ШИМ   ║ Скорость  ║ Применение    ║"));
  Serial.println(F("╠═══════════════╬═══════╬═══════╬═══════════╬═══════════════╣"));
  Serial.println(F("║ DIR_PWM       ║  2    ║  1    ║ Да        ║ Универсальный ║"));
  Serial.println(F("║ PWM_PWM       ║  2    ║  2    ║ Да        ║ ESP32 + ZK-5AD║"));
  Serial.println(F("║ DIR_DIR_PWM   ║  3    ║  1    ║ Да        ║ L298N с EN    ║"));
  Serial.println(F("║ DIR_DIR       ║  2    ║  0    ║ Нет       ║ Реле/On-Off   ║"));
  Serial.println(F("╚═══════════════╩═══════╩═══════╩═══════════╩═══════════════╝\n"));

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║           КАК ВЫБРАТЬ РЕЖИМ?                  ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  1. Посмотрите datasheet вашего драйвера      ║"));
  Serial.println(F("║  2. Определите тип входов:                    ║"));
  Serial.println(F("║     • DIR + PWM → DIR_PWM                     ║"));
  Serial.println(F("║     • IN1 + IN2 (оба ШИМ) → PWM_PWM           ║"));
  Serial.println(F("║     • IN1 + IN2 + EN → DIR_DIR_PWM            ║"));
  Serial.println(F("║     • Только вкл/выкл → DIR_DIR               ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Популярные драйверы:                         ║"));
  Serial.println(F("║  • L298N        → DIR_DIR_PWM или PWM_PWM     ║"));
  Serial.println(F("║  • TB6612FNG    → DIR_PWM                     ║"));
  Serial.println(F("║  • ZK-5AD       → PWM_PWM                     ║"));
  Serial.println(F("║  • DRV8833      → DIR_PWM                     ║"));
  Serial.println(F("║  • BTS7960      → PWM_PWM                     ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл завершен. Повтор через 10 секунд...\n\n"));
  delay(10000);
}
