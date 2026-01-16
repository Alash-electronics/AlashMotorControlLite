// Language: English | Русский: ../RU/DirectionChange/ | Қазақ: ../KZ/DirectionChange/

/*
 * Example demonstrates different ways to change motor direction
 *
 * Direction change can be performed:
 * 1. Abruptly (instantly) - NOT RECOMMENDED
 * 2. With stop in between - SAFE
 * 3. Smoothly through zero - RECOMMENDED
 *
 * Proper direction change is important for:
 * - Protecting mechanics from shock loads
 * - Extending motor lifespan
 * - Preventing gearbox damage
 * - Reducing peak current consumption
 *
 * Wiring:
 * Arduino: Motor DIR -> Pin 4, PWM -> Pin 3 (DIR_PWM mode)
 * ESP32:   Motor IN1 -> GPIO 32, IN2 -> GPIO 33 (PWM_PWM mode)
 *
 * Code written for Alash engineering
 */

#include "AlashMotorControlLite.h"

// Select mode for your platform:
#if defined(ARDUINO_ARCH_ESP32)
  AlashMotorControlLite motor(PWM_PWM, 32, 33);
#else
  AlashMotorControlLite motor(DIR_PWM, 4, 3);
#endif

// Function for smooth speed change
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
  Serial.println(F("║  DIRECTION CHANGE DEMONSTRATION               ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== METHOD 1: ABRUPT CHANGE (DANGEROUS!) ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("METHOD 1: Abrupt direction change ❌ DANGEROUS!"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("⚠ DO NOT USE IN REAL PROJECTS!\n"));

  Serial.println(F("→ Accelerating forward to 100%"));
  motor.setSpeed(100);
  delay(2000);

  Serial.println(F("⚠ ABRUPT change to -100% (instant reverse)"));
  Serial.println(F("  Dangerous for:"));
  Serial.println(F("  • Motors (overload)"));
  Serial.println(F("  • Gearboxes (shock load)"));
  Serial.println(F("  • Driver (peak current)"));
  Serial.println(F("  • Mechanics (wear)\n"));

  motor.setSpeed(-100);  // BAD!
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== METHOD 2: WITH STOP (SAFE) ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("METHOD 2: Change with stop ✓ SAFE"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Accelerating forward to 80%"));
  motor.setSpeed(80);
  delay(2000);

  Serial.println(F("→ Stopping"));
  motor.stop();
  delay(500);  // Pause for complete stop

  Serial.println(F("✓ 500ms pause for complete stop"));
  delay(500);

  Serial.println(F("→ Accelerating backward to 80%"));
  motor.setSpeed(-80);
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== METHOD 3: SMOOTH CHANGE (RECOMMENDED) ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("METHOD 3: Smooth change ★ RECOMMENDED"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Smooth acceleration forward to 70%"));
  smoothSetSpeed(70, 2000);
  delay(1500);

  Serial.println(F("→ Smooth change to -70% (through zero)"));
  Serial.println(F("  Advantages:"));
  Serial.println(F("  ✓ Protects mechanics"));
  Serial.println(F("  ✓ Smooth movement"));
  Serial.println(F("  ✓ Low peak current"));
  Serial.println(F("  ✓ Long lifespan\n"));

  smoothSetSpeed(-70, 3000);  // EXCELLENT!
  delay(1500);

  Serial.println(F("→ Smooth stop"));
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== DIFFERENT REVERSE SPEEDS ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("DIFFERENT REVERSE SPEEDS"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Fast reverse (1.5 seconds):"));
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 1500);
  delay(1000);
  smoothSetSpeed(0, 1000);
  delay(1000);

  Serial.println(F("\n→ Medium reverse (3 seconds):"));
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 3000);
  delay(1000);
  smoothSetSpeed(0, 1500);
  delay(1000);

  Serial.println(F("\n→ Slow reverse (5 seconds):"));
  smoothSetSpeed(60, 1000);
  delay(1000);
  smoothSetSpeed(-60, 5000);
  delay(1000);
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== FREQUENT REVERSALS ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("FREQUENT REVERSALS (pendulum motion)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Demonstration: forward-backward 5 times\n"));

  for (int i = 1; i <= 5; i++) {
    Serial.print(F("Cycle "));
    Serial.print(i);
    Serial.println(F("/5:"));

    Serial.println(F("  → Forward"));
    smoothSetSpeed(50, 1000);
    delay(800);

    Serial.println(F("  ← Backward"));
    smoothSetSpeed(-50, 2000);
    delay(800);

    Serial.println();
  }

  Serial.println(F("→ Stopping"));
  smoothSetSpeed(0, 1000);
  delay(2000);

  // ========== DIFFERENT FORWARD/BACKWARD SPEEDS ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("DIFFERENT SPEEDS DURING REVERSE"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Forward 80%"));
  smoothSetSpeed(80, 2000);
  delay(1000);

  Serial.println(F("→ Reverse to -40% (lower speed)"));
  smoothSetSpeed(-40, 3000);
  delay(1000);

  Serial.println(F("→ Back forward to 60%"));
  smoothSetSpeed(60, 2500);
  delay(1000);

  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== REVERSE UNDER LOAD ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("REVERSE UNDER LOAD (special cases)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("If motor is under load (robot pushing something):"));
  Serial.println(F("  1. Increase reverse time"));
  Serial.println(F("  2. Add pause at zero point"));
  Serial.println(F("  3. Use brake() before reverse\n"));

  Serial.println(F("Example:\n"));

  Serial.println(F("→ Forward 70% (under load)"));
  smoothSetSpeed(70, 2000);
  delay(2000);

  Serial.println(F("→ Active braking"));
  motor.brake();
  delay(300);  // Active braking

  Serial.println(F("→ Pause for complete stop"));
  motor.stop();
  delay(500);  // Additional pause

  Serial.println(F("→ Slow acceleration backward"));
  smoothSetSpeed(-50, 3000);  // Slow acceleration
  delay(1500);

  smoothSetSpeed(0, 2000);
  delay(2000);

  // ========== RECOMMENDATIONS ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║     DIRECTION CHANGE RECOMMENDATIONS          ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  NEVER do this:                               ║"));
  Serial.println(F("║    ✗ motor.setSpeed(100);                     ║"));
  Serial.println(F("║      motor.setSpeed(-100);  // Bad!           ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  ALWAYS use:                                  ║"));
  Serial.println(F("║    ✓ Smooth transition through zero           ║"));
  Serial.println(F("║    ✓ Stop between reversals                   ║"));
  Serial.println(F("║    ✓ Brake() for fast stop                    ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Recommended reverse times:                   ║"));
  Serial.println(F("║    • Light robots: 1.5-2 seconds              ║"));
  Serial.println(F("║    • Medium robots: 2-3 seconds               ║"));
  Serial.println(F("║    • Heavy robots: 3-5 seconds                ║"));
  Serial.println(F("║    • Under load: +50% time                    ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Sequence for loaded motor:                   ║"));
  Serial.println(F("║    1. smoothSetSpeed() to zero                ║"));
  Serial.println(F("║    2. brake() - active braking                ║"));
  Serial.println(F("║    3. delay() - pause 300-500ms               ║"));
  Serial.println(F("║    4. stop() - disable                        ║"));
  Serial.println(F("║    5. delay() - pause 300-500ms               ║"));
  Serial.println(F("║    6. smoothSetSpeed() in reverse direction   ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Cycle complete. Repeating in 5 seconds...\n\n"));
  delay(5000);
}
