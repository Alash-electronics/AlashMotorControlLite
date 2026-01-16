// Language: English | Русский: ../RU/StopVsBrake/ | Қазақ: ../KZ/StopVsBrake/
/*
 * Example demonstrates the difference between stop() and brake() methods
 *
 * stop()  - Coast stop
 *           Motor is disabled and stops by inertia
 *           Used for smooth stop without mechanical stress
 *
 * brake() - Active braking
 *           Motor actively brakes, creating resistance
 *           Used for quick stop or position holding
 *
 * Wiring:
 * Arduino: Motor DIR -> Pin 4, PWM -> Pin 3 (DIR_PWM mode)
 * ESP32:   Motor IN1 -> GPIO 32, IN2 -> GPIO 33 (PWM_PWM mode)
 *
 * IMPORTANT: Difference is most noticeable at high speeds and high inertia!
 *
 * Code written for Alash engineering
 */

#include "AlashMotorControlLite.h"

// Select mode for your platform:
#if defined(ARDUINO_ARCH_ESP32)
  // ESP32 - PWM_PWM mode
  AlashMotorControlLite motor(PWM_PWM, 32, 33);
#else
  // Arduino - DIR_PWM mode
  AlashMotorControlLite motor(DIR_PWM, 4, 3);
#endif

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║      COMPARISON stop() VS brake()            ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("This example shows the difference between two motor stopping methods.\n"));
  delay(2000);
}

void loop() {
  // ========== TEST 1: Coast stop stop() ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("TEST 1: Coast stop - stop()"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Motor accelerating to 100%..."));

  motor.setSpeed(100);
  delay(2000);  // Let motor accelerate

  Serial.println(F("→ Calling motor.stop()"));
  Serial.println(F("  Motor disables and stops by inertia"));
  Serial.println(F("  Observe: smooth stop, long coast\n"));

  motor.stop();  // Coast stop
  delay(4000);   // Wait for complete stop

  Serial.println(F("Pause 2 seconds...\n"));
  delay(2000);

  // ========== TEST 2: Active braking brake() ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("TEST 2: Active braking - brake()"));
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("Motor accelerating to 100%..."));

  motor.setSpeed(100);
  delay(2000);  // Let motor accelerate

  Serial.println(F("→ Calling motor.brake()"));
  Serial.println(F("  Motor actively brakes"));
  Serial.println(F("  Observe: quick stop, short coast\n"));

  motor.brake();  // Active braking
  delay(4000);    // Wait for complete stop

  Serial.println(F("Pause 2 seconds...\n"));
  delay(2000);

  // ========== COMPARISON IN REVERSE DIRECTION ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("TEST 3: Comparison in reverse motion"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  // Reverse with stop()
  Serial.println(F("Reverse 100% → stop()"));
  motor.setSpeed(-100);
  delay(2000);
  motor.stop();
  delay(3000);

  Serial.println(F("Pause...\n"));
  delay(2000);

  // Reverse with brake()
  Serial.println(F("Reverse 100% → brake()"));
  motor.setSpeed(-100);
  delay(2000);
  motor.brake();
  delay(3000);

  // ========== RECOMMENDATIONS ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║           WHEN TO USE WHAT?                   ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  stop() - Coast stop:                         ║"));
  Serial.println(F("║    ✓ Smooth stop without jerks                ║"));
  Serial.println(F("║    ✓ Less mechanical stress                   ║"));
  Serial.println(F("║    ✓ Energy saving                            ║"));
  Serial.println(F("║    ✗ Slow stop                                ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  brake() - Active braking:                    ║"));
  Serial.println(F("║    ✓ Quick stop                               ║"));
  Serial.println(F("║    ✓ Position holding under load              ║"));
  Serial.println(F("║    ✓ Precise stopping                         ║"));
  Serial.println(F("║    ✗ More mechanical stress                   ║"));
  Serial.println(F("║    ✗ Higher power consumption                 ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Cycle complete. Repeating in 5 seconds...\n\n"));
  delay(5000);
}
