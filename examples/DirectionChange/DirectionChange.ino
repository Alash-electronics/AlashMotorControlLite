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

  Serial.println("╔═══════════════════════════════════════════════╗");
  Serial.println("║  ДЕМОНСТРАЦИЯ СМЕНЫ НАПРАВЛЕНИЯ               ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  delay(2000);
}

void loop() {
  // ========== СПОСОБ 1: РЕЗКАЯ СМЕНА (ОПАСНО!) ==========
  Serial.println("═══════════════════════════════════════════════");
  Serial.println("СПОСОБ 1: Резкая смена направления ❌ ОПАСНО!");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("⚠ НЕ ИСПОЛЬЗУЙТЕ В РЕАЛЬНЫХ ПРОЕКТАХ!\n");

  Serial.println("→ Разгон вперед до 100%");
  motor.setSpeed(100);
  delay(2000);

  Serial.println("⚠ РЕЗКАЯ смена на -100% (мгновенный реверс)");
  Serial.println("  Опасно для:");
  Serial.println("  • Моторов (перегрузка)");
  Serial.println("  • Редукторов (ударная нагрузка)");
  Serial.println("  • Драйвера (пиковый ток)");
  Serial.println("  • Механики (износ)\n");

  motor.setSpeed(-100);  // ПЛОХО!
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== СПОСОБ 2: С ОСТАНОВКОЙ (БЕЗОПАСНО) ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("СПОСОБ 2: Смена с остановкой ✓ БЕЗОПАСНО");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Разгон вперед до 80%");
  motor.setSpeed(80);
  delay(2000);

  Serial.println("→ Остановка");
  motor.stop();
  delay(500);  // Пауза для полной остановки

  Serial.println("✓ Пауза 500мс для полной остановки");
  delay(500);

  Serial.println("→ Разгон назад до 80%");
  motor.setSpeed(-80);
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== СПОСОБ 3: ПЛАВНАЯ СМЕНА (РЕКОМЕНДУЕТСЯ) ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("СПОСОБ 3: Плавная смена ★ РЕКОМЕНДУЕТСЯ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Плавный разгон вперед до 70%");
  smoothSetSpeed(70, 2000);
  delay(1500);

  Serial.println("→ Плавная смена на -70% (через ноль)");
  Serial.println("  Преимущества:");
  Serial.println("  ✓ Защита механики");
  Serial.println("  ✓ Плавное движение");
  Serial.println("  ✓ Низкий пиковый ток");
  Serial.println("  ✓ Долгий срок службы\n");

  smoothSetSpeed(-70, 3000);  // ОТЛИЧНО!
  delay(1500);

  Serial.println("→ Плавная остановка");
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== РАЗНЫЕ СКОРОСТИ РЕВЕРСА ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("РАЗНЫЕ СКОРОСТИ РЕВЕРСА");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Быстрый реверс (1.5 секунды):");
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 1500);
  delay(1000);
  smoothSetSpeed(0, 1000);
  delay(1000);

  Serial.println("\n→ Средний реверс (3 секунды):");
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 3000);
  delay(1000);
  smoothSetSpeed(0, 1500);
  delay(1000);

  Serial.println("\n→ Медленный реверс (5 секунд):");
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 5000);
  delay(1000);
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== ЧАСТЫЕ РЕВЕРСЫ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("ЧАСТЫЕ РЕВЕРСЫ (маятниковое движение)");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Демонстрация: вперед-назад 5 раз\n");

  for (int i = 1; i <= 5; i++) {
    Serial.print("Цикл ");
    Serial.print(i);
    Serial.println("/5:");

    Serial.println("  → Вперед");
    smoothSetSpeed(50, 1000);
    delay(800);

    Serial.println("  ← Назад");
    smoothSetSpeed(-50, 2000);
    delay(800);

    Serial.println();
  }

  Serial.println("→ Остановка");
  smoothSetSpeed(0, 1000);
  delay(2000);

  // ========== РАЗНЫЕ СКОРОСТИ ВПЕРЕД/НАЗАД ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("РАЗНЫЕ СКОРОСТИ ПРИ РЕВЕРСЕ");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("→ Вперед 80%");
  smoothSetSpeed(80, 2000);
  delay(1000);

  Serial.println("→ Реверс на -40% (меньшая скорость)");
  smoothSetSpeed(-40, 3000);
  delay(1000);

  Serial.println("→ Обратно вперед 60%");
  smoothSetSpeed(60, 2500);
  delay(1000);

  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== РЕВЕРС ПОД НАГРУЗКОЙ ==========
  Serial.println("\n═══════════════════════════════════════════════");
  Serial.println("РЕВЕРС ПОД НАГРУЗКОЙ (особые случаи)");
  Serial.println("═══════════════════════════════════════════════\n");

  Serial.println("Если мотор под нагрузкой (робот толкает что-то):");
  Serial.println("  1. Увеличьте время реверса");
  Serial.println("  2. Добавьте паузу в нулевой точке");
  Serial.println("  3. Используйте brake() перед реверсом\n");

  Serial.println("Пример:\n");

  Serial.println("→ Вперед 70% (под нагрузкой)");
  smoothSetSpeed(70, 2000);
  delay(2000);

  Serial.println("→ Активное торможение");
  motor.brake();
  delay(300);  // Активное торможение

  Serial.println("→ Пауза для полной остановки");
  motor.stop();
  delay(500);  // Дополнительная пауза

  Serial.println("→ Медленный разгон назад");
  smoothSetSpeed(-50, 3000);  // Медленный разгон
  delay(1500);

  smoothSetSpeed(0, 2000);
  delay(2000);

  // ========== РЕКОМЕНДАЦИИ ==========
  Serial.println("\n╔═══════════════════════════════════════════════╗");
  Serial.println("║        РЕКОМЕНДАЦИИ ПО СМЕНЕ НАПРАВЛЕНИЯ      ║");
  Serial.println("╠═══════════════════════════════════════════════╣");
  Serial.println("║  НИКОГДА не делайте:                          ║");
  Serial.println("║    ✗ motor.setSpeed(100);                     ║");
  Serial.println("║      motor.setSpeed(-100);  // Плохо!         ║");
  Serial.println("║                                                ║");
  Serial.println("║  ВСЕГДА используйте:                          ║");
  Serial.println("║    ✓ Плавный переход через ноль               ║");
  Serial.println("║    ✓ Остановку между реверсами                ║");
  Serial.println("║    ✓ Brake() для быстрой остановки            ║");
  Serial.println("║                                                ║");
  Serial.println("║  Рекомендуемые времена реверса:               ║");
  Serial.println("║    • Легкие роботы: 1.5-2 секунды             ║");
  Serial.println("║    • Средние роботы: 2-3 секунды              ║");
  Serial.println("║    • Тяжелые роботы: 3-5 секунд               ║");
  Serial.println("║    • Под нагрузкой: +50% времени              ║");
  Serial.println("║                                                ║");
  Serial.println("║  Последовательность для нагруженного мотора:  ║");
  Serial.println("║    1. smoothSetSpeed() к нулю                 ║");
  Serial.println("║    2. brake() - активное торможение           ║");
  Serial.println("║    3. delay() - пауза 300-500мс               ║");
  Serial.println("║    4. stop() - отключение                     ║");
  Serial.println("║    5. delay() - пауза 300-500мс               ║");
  Serial.println("║    6. smoothSetSpeed() в обратную сторону     ║");
  Serial.println("╚═══════════════════════════════════════════════╝\n");

  Serial.println("Цикл завершен. Повтор через 5 секунд...\n\n");
  delay(5000);
}
