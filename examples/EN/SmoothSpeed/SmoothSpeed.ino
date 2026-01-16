// Language: English | Русский: ../RU/SmoothSpeed/ | Қазақ: ../KZ/SmoothSpeed/

/*
 * Example demonstrates smooth speed change (Ramping)
 *
 * Smooth speed change is important for:
 * - Protecting mechanics from jerks and shock loads
 * - Extending motor and gearbox lifespan
 * - Preventing wheel slippage
 * - Smooth robot movement
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
// targetSpeed: target speed (-100 to 100)
// rampTime: acceleration/deceleration time in milliseconds
void smoothSetSpeed(int targetSpeed, unsigned long rampTime) {
  int currentSpeed = motor.getSpeed();
  int speedDiff = targetSpeed - currentSpeed;
  int steps = abs(speedDiff);

  if (steps == 0) return;  // Already at target speed

  unsigned long stepDelay = rampTime / steps;

  Serial.print(F("Smooth change: "));
  Serial.print(currentSpeed);
  Serial.print(F(" → "));
  Serial.print(targetSpeed);
  Serial.print(F(" in "));
  Serial.print(rampTime);
  Serial.println(F(" ms"));

  if (speedDiff > 0) {
    // Increase speed
    for (int speed = currentSpeed + 1; speed <= targetSpeed; speed++) {
      motor.setSpeed(speed);
      delay(stepDelay);
    }
  } else {
    // Decrease speed
    for (int speed = currentSpeed - 1; speed >= targetSpeed; speed--) {
      motor.setSpeed(speed);
      delay(stepDelay);
    }
  }

  Serial.println(F("  ✓ Target speed reached\n"));
}

// Function for smooth speed change with specified acceleration
// targetSpeed: target speed (-100 to 100)
// acceleration: acceleration (speed units per step)
// stepDelay: delay between steps in milliseconds
void smoothSetSpeedAccel(int targetSpeed, int acceleration, unsigned long stepDelay) {
  int currentSpeed = motor.getSpeed();

  Serial.print(F("Smooth change with acceleration "));
  Serial.print(acceleration);
  Serial.print(F(": "));
  Serial.print(currentSpeed);
  Serial.print(F(" → "));
  Serial.println(targetSpeed);

  while (currentSpeed != targetSpeed) {
    int diff = targetSpeed - currentSpeed;

    if (abs(diff) <= acceleration) {
      // Reach target speed
      currentSpeed = targetSpeed;
    } else if (diff > 0) {
      // Increase speed
      currentSpeed += acceleration;
    } else {
      // Decrease speed
      currentSpeed -= acceleration;
    }

    motor.setSpeed(currentSpeed);
    delay(stepDelay);
  }

  Serial.println(F("  ✓ Target speed reached\n"));
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  SMOOTH SPEED CHANGE (RAMPING)                ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== COMPARISON: Abrupt VS Smooth ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("COMPARISON: Abrupt vs Smooth change"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("❌ ABRUPT change (may damage mechanics):"));
  motor.setSpeed(0);
  delay(500);
  Serial.println(F("motor.setSpeed(100) - instant jerk!"));
  motor.setSpeed(100);
  delay(2000);

  motor.stop();
  delay(1000);

  Serial.println(F("\n✓ SMOOTH change (safe for mechanics):"));
  motor.setSpeed(0);
  delay(500);
  smoothSetSpeed(100, 2000);  // Smooth acceleration in 2 seconds
  delay(2000);

  motor.stop();
  delay(2000);

  // ========== DIFFERENT ACCELERATION TIMES ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("DIFFERENT ACCELERATION TIMES"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Fast acceleration (1 second):"));
  smoothSetSpeed(80, 1000);
  delay(1000);
  smoothSetSpeed(0, 1000);
  delay(1000);

  Serial.println(F("→ Medium acceleration (2 seconds):"));
  smoothSetSpeed(80, 2000);
  delay(1000);
  smoothSetSpeed(0, 2000);
  delay(1000);

  Serial.println(F("→ Slow acceleration (3 seconds):"));
  smoothSetSpeed(80, 3000);
  delay(1000);
  smoothSetSpeed(0, 3000);
  delay(2000);

  // ========== ACCELERATION ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("ACCELERATION CONTROL"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Low acceleration (smooth):"));
  smoothSetSpeedAccel(90, 2, 50);  // +2 units every 50ms
  delay(1000);
  smoothSetSpeedAccel(0, 2, 50);
  delay(1000);

  Serial.println(F("→ Medium acceleration:"));
  smoothSetSpeedAccel(90, 5, 50);  // +5 units every 50ms
  delay(1000);
  smoothSetSpeedAccel(0, 5, 50);
  delay(1000);

  Serial.println(F("→ High acceleration (fast):"));
  smoothSetSpeedAccel(90, 10, 50);  // +10 units every 50ms
  delay(1000);
  smoothSetSpeedAccel(0, 10, 50);
  delay(2000);

  // ========== REVERSE ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("SMOOTH REVERSE"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Acceleration forward:"));
  smoothSetSpeed(70, 2000);
  delay(1000);

  Serial.println(F("→ Smooth stop:"));
  smoothSetSpeed(0, 1500);
  delay(500);

  Serial.println(F("→ Acceleration backward:"));
  smoothSetSpeed(-70, 2000);
  delay(1000);

  Serial.println(F("→ Smooth stop:"));
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== DIRECT REVERSE ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("DIRECT REVERSE (through zero)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Forward 60%:"));
  smoothSetSpeed(60, 1500);
  delay(1000);

  Serial.println(F("→ Direct transition to -60% (through 0):"));
  smoothSetSpeed(-60, 3000);  // Smoothly pass through 0
  delay(1000);

  Serial.println(F("→ Stop:"));
  smoothSetSpeed(0, 1500);
  delay(2000);

  // ========== S-CURVE ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("S-CURVE (advanced technique)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Slow start → fast acceleration → smooth stop\n"));

  // Slow start
  Serial.println(F("  Phase 1: Slow start"));
  smoothSetSpeedAccel(30, 1, 100);
  delay(500);

  // Fast acceleration
  Serial.println(F("  Phase 2: Fast acceleration"));
  smoothSetSpeedAccel(90, 5, 50);
  delay(1000);

  // Smooth deceleration
  Serial.println(F("  Phase 3: Smooth deceleration"));
  smoothSetSpeedAccel(30, 3, 70);
  delay(500);

  // Soft stop
  Serial.println(F("  Phase 4: Soft stop"));
  smoothSetSpeedAccel(0, 1, 100);
  delay(2000);

  // ========== RECOMMENDATIONS ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║        USAGE RECOMMENDATIONS                  ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  ALWAYS use smooth change for:                ║"));
  Serial.println(F("║    ✓ Starting from stop (0 → speed)           ║"));
  Serial.println(F("║    ✓ Stopping (speed → 0)                     ║"));
  Serial.println(F("║    ✓ Reversing (+ → -)                        ║"));
  Serial.println(F("║    ✓ High speeds                              ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Recommended acceleration times:              ║"));
  Serial.println(F("║    • Light robots: 1-2 seconds                ║"));
  Serial.println(F("║    • Medium robots: 2-3 seconds               ║"));
  Serial.println(F("║    • Heavy robots: 3-5 seconds                ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Advantages:                                  ║"));
  Serial.println(F("║    • Protects mechanics from wear             ║"));
  Serial.println(F("║    • Reduces peak current                     ║"));
  Serial.println(F("║    • Better wheel traction                    ║"));
  Serial.println(F("║    • Smooth movement                          ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Cycle complete. Repeating in 5 seconds...\n\n"));
  delay(5000);
}
