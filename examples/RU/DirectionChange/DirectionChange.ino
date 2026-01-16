// Language: Русский | English: ../EN/DirectionChange/ | Қазақ: ../KZ/DirectionChange/
/*
 * Пример демонстрирует различные способы смены направления движения мотора
 *
 * Смена направления может выполняться:
 * 1. Резко (мгновенно) - НЕ РЕКОМЕНДУЕТСЯ
 * 2. С остановкой между - БЕЗОПАСНО
 * 3. Плавно через ноль - РЕКОМЕНДУЕТСЯ
 *
 * Правильная смена направления важна для:
 * - Защиты механики от ударных нагрузок
 * - Продления срока службы моторов
 * - Предотвращения повреждения редукторов
 * - Снижения пикового потребления тока
 *
 * Подключение:
 * Arduino: Motor DIR -> Pin 4, PWM -> Pin 3 (режим DIR_PWM)
 * ESP32:   Motor IN1 -> GPIO 32, IN2 -> GPIO 33 (режим PWM_PWM)
 *
 * Код написан для Alash engineering
 */

#include "AlashMotorControlLite.h"

// Выберите режим для вашей платформы:
#if defined(ARDUINO_ARCH_ESP32)
  AlashMotorControlLite motor(PWM_PWM, 32, 33);
#else
  AlashMotorControlLite motor(DIR_PWM, 4, 3);
#endif

// Функция для плавного изменения скорости
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
  Serial.println(F("║  ДЕМОНСТРАЦИЯ СМЕНЫ НАПРАВЛЕНИЯ               ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== СПОСОБ 1: РЕЗКАЯ СМЕНА (ОПАСНО!) ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("СПОСОБ 1: Резкая смена направления ❌ ОПАСНО!"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("⚠ НЕ ИСПОЛЬЗУЙТЕ В РЕАЛЬНЫХ ПРОЕКТАХ!\n"));

  Serial.println(F("→ Разгон вперед до 100%"));
  motor.setSpeed(100);
  delay(2000);

  Serial.println(F("⚠ РЕЗКАЯ смена на -100% (мгновенный реверс)"));
  Serial.println(F("  Опасно для:"));
  Serial.println(F("  • Моторов (перегрузка)"));
  Serial.println(F("  • Редукторов (ударная нагрузка)"));
  Serial.println(F("  • Драйвера (пиковый ток)"));
  Serial.println(F("  • Механики (износ)\n"));

  motor.setSpeed(-100);  // ПЛОХО!
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== СПОСОБ 2: С ОСТАНОВКОЙ (БЕЗОПАСНО) ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("СПОСОБ 2: Смена с остановкой ✓ БЕЗОПАСНО"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Разгон вперед до 80%"));
  motor.setSpeed(80);
  delay(2000);

  Serial.println(F("→ Остановка"));
  motor.stop();
  delay(500);  // Пауза для полной остановки

  Serial.println(F("✓ Пауза 500мс для полной остановки"));
  delay(500);

  Serial.println(F("→ Разгон назад до 80%"));
  motor.setSpeed(-80);
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== СПОСОБ 3: ПЛАВНАЯ СМЕНА (РЕКОМЕНДУЕТСЯ) ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("СПОСОБ 3: Плавная смена ★ РЕКОМЕНДУЕТСЯ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Плавный разгон вперед до 70%"));
  smoothSetSpeed(70, 2000);
  delay(1500);

  Serial.println(F("→ Плавная смена на -70% (через ноль)"));
  Serial.println(F("  Преимущества:"));
  Serial.println(F("  ✓ Защита механики"));
  Serial.println(F("  ✓ Плавное движение"));
  Serial.println(F("  ✓ Низкий пиковый ток"));
  Serial.println(F("  ✓ Долгий срок службы\n"));

  smoothSetSpeed(-70, 3000);  // ОТЛИЧНО!
  delay(1500);

  Serial.println(F("→ Плавная остановка"));
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== РАЗНЫЕ СКОРОСТИ РЕВЕРСА ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РАЗНЫЕ СКОРОСТИ РЕВЕРСА"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Быстрый реверс (1.5 секунды):"));
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 1500);
  delay(1000);
  smoothSetSpeed(0, 1000);
  delay(1000);

  Serial.println(F("\n→ Средний реверс (3 секунды):"));
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 3000);
  delay(1000);
  smoothSetSpeed(0, 1500);
  delay(1000);

  Serial.println(F("\n→ Медленный реверс (5 секунд):"));
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 5000);
  delay(1000);
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== ЧАСТЫЕ РЕВЕРСЫ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ЧАСТЫЕ РЕВЕРСЫ (маятниковое движение)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Демонстрация: вперед-назад 5 раз\n"));

  for (int i = 1; i <= 5; i++) {
    Serial.print(F("Цикл "));
    Serial.print(i);
    Serial.println(F("/5:"));

    Serial.println(F("  → Вперед"));
    smoothSetSpeed(50, 1000);
    delay(800);

    Serial.println(F("  ← Назад"));
    smoothSetSpeed(-50, 2000);
    delay(800);

    Serial.println();
  }

  Serial.println(F("→ Остановка"));
  smoothSetSpeed(0, 1000);
  delay(2000);

  // ========== РАЗНЫЕ СКОРОСТИ ВПЕРЕД/НАЗАД ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РАЗНЫЕ СКОРОСТИ ПРИ РЕВЕРСЕ"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Вперед 80%"));
  smoothSetSpeed(80, 2000);
  delay(1000);

  Serial.println(F("→ Реверс на -40% (меньшая скорость)"));
  smoothSetSpeed(-40, 3000);
  delay(1000);

  Serial.println(F("→ Обратно вперед 60%"));
  smoothSetSpeed(60, 2500);
  delay(1000);

  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== РЕВЕРС ПОД НАГРУЗКОЙ ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("РЕВЕРС ПОД НАГРУЗКОЙ (особые случаи)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Если мотор под нагрузкой (робот толкает что-то):"));
  Serial.println(F("  1. Увеличьте время реверса"));
  Serial.println(F("  2. Добавьте паузу в нулевой точке"));
  Serial.println(F("  3. Используйте brake() перед реверсом\n"));

  Serial.println(F("Пример:\n"));

  Serial.println(F("→ Вперед 70% (под нагрузкой)"));
  smoothSetSpeed(70, 2000);
  delay(2000);

  Serial.println(F("→ Активное торможение"));
  motor.brake();
  delay(300);  // Активное торможение

  Serial.println(F("→ Пауза для полной остановки"));
  motor.stop();
  delay(500);  // Дополнительная пауза

  Serial.println(F("→ Медленный разгон назад"));
  smoothSetSpeed(-50, 3000);  // Медленный разгон
  delay(1500);

  smoothSetSpeed(0, 2000);
  delay(2000);

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║        РЕКОМЕНДАЦИИ ПО СМЕНЕ НАПРАВЛЕНИЯ      ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  НИКОГДА не делайте:                          ║"));
  Serial.println(F("║    ✗ motor.setSpeed(100);                     ║"));
  Serial.println(F("║      motor.setSpeed(-100);  // Плохо!         ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  ВСЕГДА используйте:                          ║"));
  Serial.println(F("║    ✓ Плавный переход через ноль               ║"));
  Serial.println(F("║    ✓ Остановку между реверсами                ║"));
  Serial.println(F("║    ✓ Brake() для быстрой остановки            ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Рекомендуемые времена реверса:               ║"));
  Serial.println(F("║    • Легкие роботы: 1.5-2 секунды             ║"));
  Serial.println(F("║    • Средние роботы: 2-3 секунды              ║"));
  Serial.println(F("║    • Тяжелые роботы: 3-5 секунд               ║"));
  Serial.println(F("║    • Под нагрузкой: +50% времени              ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Последовательность для нагруженного мотора:  ║"));
  Serial.println(F("║    1. smoothSetSpeed() к нулю                 ║"));
  Serial.println(F("║    2. brake() - активное торможение           ║"));
  Serial.println(F("║    3. delay() - пауза 300-500мс               ║"));
  Serial.println(F("║    4. stop() - отключение                     ║"));
  Serial.println(F("║    5. delay() - пауза 300-500мс               ║"));
  Serial.println(F("║    6. smoothSetSpeed() в обратную сторону     ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Цикл завершен. Повтор через 5 секунд...\n\n"));
  delay(5000);
}
