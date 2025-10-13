/*
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

  Serial.println("╔═══════════════════════════════════════════════╗");
  Serial.println("║  СРАВНЕНИЕ ВСЕХ РЕЖИМОВ РАБОТЫ                ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  delay(2000);
}

void loop() {
  // ========== РЕЖИМ 1: DIR_PWM ==========
  Serial.println("═══════════════════════════════════════════════");
  Serial.println("РЕЖИМ 1: DIR_PWM");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Описание:");
  Serial.println("  • 1 цифровой пин (DIR) - направление");
  Serial.println("  • 1 ШИМ пин (PWM) - скорость\n");

  Serial.println("Подключение:");
  Serial.println("  Arduino: AlashMotorControlLite motor(DIR_PWM, 4, 3);");
  Serial.println("           PIN 4 → DIR (направление)");
  Serial.println("           PIN 3 → PWM (скорость)\n");

  Serial.println("Совместимые драйверы:");
  Serial.println("  • TB6612FNG");
  Serial.println("  • DRV8833");
  Serial.println("  • Большинство H-Bridge модулей\n");

  Serial.println("Принцип работы:");
  Serial.println("  DIR=LOW,  PWM=128 → Вперед на 50%");
  Serial.println("  DIR=HIGH, PWM=128 → Назад на 50%");
  Serial.println("  DIR=X,    PWM=0   → Остановка\n");

  Serial.println("Преимущества:");
  Serial.println("  ✓ Простое подключение");
  Serial.println("  ✓ Интуитивно понятная логика");
  Serial.println("  ✓ Экономия пинов\n");

  Serial.println("Недостатки:");
  Serial.println("  ✗ Требует ШИМ пин для скорости\n");

  delay(5000);

  // ========== РЕЖИМ 2: PWM_PWM ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("РЕЖИМ 2: PWM_PWM");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Описание:");
  Serial.println("  • 2 ШИМ пина (IN1, IN2)");
  Serial.println("  • Каждый пин управляет направлением\n");

  Serial.println("Подключение:");
  Serial.println("  Arduino: AlashMotorControlLite motor(PWM_PWM, 9, 10);");
  Serial.println("           PIN 9  → IN1");
  Serial.println("           PIN 10 → IN2\n");

  Serial.println("  ESP32:   AlashMotorControlLite motor(PWM_PWM, 32, 33);");
  Serial.println("           GPIO 32 → IN1");
  Serial.println("           GPIO 33 → IN2\n");

  Serial.println("Совместимые драйверы:");
  Serial.println("  • ZK-5AD ★ РЕКОМЕНДУЕТСЯ для ESP32");
  Serial.println("  • L298N");
  Serial.println("  • BTS7960");
  Serial.println("  • Двухканальные H-Bridge\n");

  Serial.println("Принцип работы:");
  Serial.println("  IN1=128, IN2=0   → Вперед на 50%");
  Serial.println("  IN1=0,   IN2=128 → Назад на 50%");
  Serial.println("  IN1=0,   IN2=0   → Остановка");
  Serial.println("  IN1=255, IN2=255 → Торможение\n");

  Serial.println("Преимущества:");
  Serial.println("  ✓ Независимое управление направлениями");
  Serial.println("  ✓ Лучший контроль торможения");
  Serial.println("  ✓ Идеален для ESP32 (много ШИМ каналов)\n");

  Serial.println("Недостатки:");
  Serial.println("  ✗ Требует 2 ШИМ пина");
  Serial.println("  ✗ На Arduino ограниченно ШИМ пинов\n");

  delay(5000);

  // ========== РЕЖИМ 3: DIR_DIR_PWM ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("РЕЖИМ 3: DIR_DIR_PWM");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Описание:");
  Serial.println("  • 2 цифровых пина (IN1, IN2) - направление");
  Serial.println("  • 1 ШИМ пин (PWM/EN) - скорость\n");

  Serial.println("Подключение:");
  Serial.println("  Arduino: AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);");
  Serial.println("           PIN 4 → IN1 (направление 1)");
  Serial.println("           PIN 5 → IN2 (направление 2)");
  Serial.println("           PIN 6 → PWM/EN (скорость)\n");

  Serial.println("Совместимые драйверы:");
  Serial.println("  • L298N (с пином EN)");
  Serial.println("  • L293D");
  Serial.println("  • Драйверы с отдельным Enable пином\n");

  Serial.println("Принцип работы:");
  Serial.println("  IN1=HIGH, IN2=LOW,  PWM=128 → Вперед на 50%");
  Serial.println("  IN1=LOW,  IN2=HIGH, PWM=128 → Назад на 50%");
  Serial.println("  IN1=X,    IN2=X,    PWM=0   → Остановка");
  Serial.println("  IN1=HIGH, IN2=HIGH, PWM=255 → Торможение\n");

  Serial.println("Преимущества:");
  Serial.println("  ✓ Четкое разделение направления и скорости");
  Serial.println("  ✓ Экономия ШИМ пинов (только 1)");
  Serial.println("  ✓ Хорошая совместимость\n");

  Serial.println("Недостатки:");
  Serial.println("  ✗ Требует 3 пина на мотор");
  Serial.println("  ✗ Немного сложнее подключение\n");

  delay(5000);

  // ========== РЕЖИМ 4: DIR_DIR ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("РЕЖИМ 4: DIR_DIR");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Описание:");
  Serial.println("  • 2 цифровых пина (IN1, IN2)");
  Serial.println("  • БЕЗ ШИМ - только вкл/выкл и направление\n");

  Serial.println("Подключение:");
  Serial.println("  Arduino: AlashMotorControlLite motor(DIR_DIR, 4, 5);");
  Serial.println("           PIN 4 → IN1");
  Serial.println("           PIN 5 → IN2\n");

  Serial.println("Совместимые драйверы:");
  Serial.println("  • Релейные модули");
  Serial.println("  • Простые H-Bridge без ШИМ");
  Serial.println("  • Драйверы со встроенным контроллером скорости\n");

  Serial.println("Принцип работы:");
  Serial.println("  IN1=HIGH, IN2=LOW  → Вперед (полная скорость)");
  Serial.println("  IN1=LOW,  IN2=HIGH → Назад (полная скорость)");
  Serial.println("  IN1=LOW,  IN2=LOW  → Остановка");
  Serial.println("  IN1=HIGH, IN2=HIGH → Торможение\n");

  Serial.println("ВАЖНО: В этом режиме setSpeed() работает как:");
  Serial.println("  speed > 0  → Вперед (полная)");
  Serial.println("  speed < 0  → Назад (полная)");
  Serial.println("  speed == 0 → Остановка");
  Serial.println("  Значение скорости игнорируется!\n");

  Serial.println("Преимущества:");
  Serial.println("  ✓ Не требует ШИМ пинов");
  Serial.println("  ✓ Простейшее подключение");
  Serial.println("  ✓ Для драйверов без ШИМ входа\n");

  Serial.println("Недостатки:");
  Serial.println("  ✗ Нет регулировки скорости");
  Serial.println("  ✗ Только полная скорость вкл/выкл\n");

  delay(5000);

  // ========== СРАВНИТЕЛЬНАЯ ТАБЛИЦА ==========
  Serial.println("\n╔═══════════════════════════════════════════════════════════╗");
  Serial.println("║              СРАВНИТЕЛЬНАЯ ТАБЛИЦА                        ║");
  Serial.println("╠═══════════════╦═══════╦═══════╦═══════════╦═══════════════╣");
  Serial.println("║ Режим         ║ Пины  ║ ШИМ   ║ Скорость  ║ Применение    ║");
  Serial.println("╠═══════════════╬═══════╬═══════╬═══════════╬═══════════════╣");
  Serial.println("║ DIR_PWM       ║  2    ║  1    ║ Да        ║ Универсальный ║");
  Serial.println("║ PWM_PWM       ║  2    ║  2    ║ Да        ║ ESP32 + ZK-5AD║");
  Serial.println("║ DIR_DIR_PWM   ║  3    ║  1    ║ Да        ║ L298N с EN    ║");
  Serial.println("║ DIR_DIR       ║  2    ║  0    ║ Нет       ║ Реле/On-Off   ║");
  Serial.println("╚═══════════════╩═══════╩═══════╩═══════════╩═══════════════╝\n");

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println("╔═══════════════════════════════════════════════╗");
  Serial.println("║           КАК ВЫБРАТЬ РЕЖИМ?                  ║");
  Serial.println("╠═══════════════════════════════════════════════╣");
  Serial.println("║  1. Посмотрите datasheet вашего драйвера      ║");
  Serial.println("║  2. Определите тип входов:                    ║");
  Serial.println("║     • DIR + PWM → DIR_PWM                     ║");
  Serial.println("║     • IN1 + IN2 (оба ШИМ) → PWM_PWM           ║");
  Serial.println("║     • IN1 + IN2 + EN → DIR_DIR_PWM            ║");
  Serial.println("║     • Только вкл/выкл → DIR_DIR               ║");
  Serial.println("║                                                ║");
  Serial.println("║  Популярные драйверы:                         ║");
  Serial.println("║  • L298N        → DIR_DIR_PWM или PWM_PWM     ║");
  Serial.println("║  • TB6612FNG    → DIR_PWM                     ║");
  Serial.println("║  • ZK-5AD       → PWM_PWM                     ║");
  Serial.println("║  • DRV8833      → DIR_PWM                     ║");
  Serial.println("║  • BTS7960      → PWM_PWM                     ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  Serial.println("Цикл завершен. Повтор через 10 секунд...\n\n");
  delay(10000);
}
