// Language: English | Русский: ../RU/GettersDemo/ | Қазақ: ../KZ/GettersDemo/

/*
 * Example demonstrates the use of library getter methods:
 * - getSpeed() - get current motor speed
 * - getMode()  - get driver mode
 *
 * These methods are useful for:
 * - Monitoring motor status
 * - Program debugging
 * - Creating telemetry
 * - Conditional logic based on state
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

// Function to print current motor status
void printMotorStatus() {
  int16_t currentSpeed = motor.getSpeed();
  MODE currentMode = motor.getMode();

  Serial.print(F("┌─────────────────────────────────┐\n"));
  Serial.print(F("│ MOTOR STATUS                    │\n"));
  Serial.print(F("├─────────────────────────────────┤\n"));
  Serial.print(F("│ Speed: "));
  Serial.print(currentSpeed);
  Serial.print(F(" "));

  // Direction indicator
  if (currentSpeed > 0) {
    Serial.print(F("→ Forward"));
  } else if (currentSpeed < 0) {
    Serial.print(F("← Backward"));
  } else {
    Serial.print(F("■ Stopped"));
  }

  // Add spaces for alignment
  int spaces = 15 - String(currentSpeed).length();
  if (currentSpeed >= 0) spaces -= 8;  // "→ Forward"
  else spaces -= 7;                     // "← Backward"
  if (currentSpeed == 0) spaces = 7;    // "■ Stopped"

  for (int i = 0; i < spaces; i++) {
    Serial.print(F(" "));
  }
  Serial.print(F("│\n"));

  Serial.print(F("│ Mode:    "));

  switch(currentMode) {
    case DIR_PWM:
      Serial.print(F("DIR_PWM"));
      Serial.print(F("          "));
      break;
    case PWM_PWM:
      Serial.print(F("PWM_PWM"));
      Serial.print(F("          "));
      break;
    case DIR_DIR_PWM:
      Serial.print(F("DIR_DIR_PWM"));
      Serial.print(F("      "));
      break;
    case DIR_DIR:
      Serial.print(F("DIR_DIR"));
      Serial.print(F("          "));
      break;
  }

  Serial.print(F("│\n"));
  Serial.print(F("└─────────────────────────────────┘\n\n"));
}

// Function to display speed graph
void printSpeedGraph() {
  int16_t speed = motor.getSpeed();
  Serial.print(F("Graph: "));

  // Display graph from -100 to +100
  if (speed < 0) {
    // Backward movement
    int bars = map(abs(speed), 0, 100, 0, 20);
    for (int i = 20; i > bars; i--) Serial.print(F(" "));
    for (int i = 0; i < bars; i++) Serial.print(F("◄"));
    Serial.print(F("|"));
    for (int i = 0; i < 20; i++) Serial.print(F(" "));
  } else if (speed > 0) {
    // Forward movement
    for (int i = 0; i < 20; i++) Serial.print(F(" "));
    Serial.print(F("|"));
    int bars = map(speed, 0, 100, 0, 20);
    for (int i = 0; i < bars; i++) Serial.print(F("►"));
  } else {
    // Stopped
    for (int i = 0; i < 20; i++) Serial.print(F(" "));
    Serial.print(F("|"));
  }

  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  GETTER METHODS DEMONSTRATION                 ║"));
  Serial.println(F("║  getSpeed() and getMode()                     ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== DEMONSTRATION OF getSpeed() ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("getSpeed() DEMONSTRATION"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Gradually increasing forward speed\n"));

  for (int speed = 0; speed <= 100; speed += 20) {
    motor.setSpeed(speed);

    Serial.print(F("motor.setSpeed("));
    Serial.print(speed);
    Serial.print(F(") → getSpeed() returns: "));
    Serial.println(motor.getSpeed());

    printSpeedGraph();
    Serial.println();

    delay(1000);
  }

  delay(1000);

  Serial.println(F("\n→ Gradually increasing backward speed\n"));

  for (int speed = 0; speed >= -100; speed -= 20) {
    motor.setSpeed(speed);

    Serial.print(F("motor.setSpeed("));
    Serial.print(speed);
    Serial.print(F(") → getSpeed() returns: "));
    Serial.println(motor.getSpeed());

    printSpeedGraph();
    Serial.println();

    delay(1000);
  }

  motor.stop();
  delay(2000);

  // ========== MONITORING DEMONSTRATION ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("MOTOR STATUS MONITORING"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("→ Accelerating to 75%"));
  motor.setSpeed(75);
  delay(500);
  printMotorStatus();

  Serial.println(F("→ Reducing to 50%"));
  motor.setSpeed(50);
  delay(500);
  printMotorStatus();

  Serial.println(F("→ Reversing to -80%"));
  motor.setSpeed(-80);
  delay(500);
  printMotorStatus();

  Serial.println(F("→ Stopping"));
  motor.stop();
  delay(500);
  printMotorStatus();

  // ========== CONDITIONAL LOGIC ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("CONDITIONAL LOGIC BASED ON getSpeed()"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  motor.setSpeed(100);
  delay(500);

  if (motor.getSpeed() > 50) {
    Serial.println(F("✓ Speed is high (>50), turning on LED"));
  }

  if (motor.getSpeed() > 0) {
    Serial.println(F("✓ Motor moving forward"));
  } else if (motor.getSpeed() < 0) {
    Serial.println(F("✓ Motor moving backward"));
  } else {
    Serial.println(F("✓ Motor stopped"));
  }

  delay(2000);
  motor.setSpeed(-60);
  delay(500);

  if (motor.getSpeed() < -50) {
    Serial.println(F("⚠ High backward speed, caution!"));
  }

  delay(2000);
  motor.brake();
  delay(500);

  if (motor.getSpeed() == 0) {
    Serial.println(F("✓ Motor completely stopped"));
  }

  // ========== DEMONSTRATION OF getMode() ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("getMode() DEMONSTRATION"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Current driver mode:"));
  printMotorStatus();

  Serial.println(F("Mode is set when creating motor object"));
  Serial.println(F("and cannot be changed during runtime.\n"));

  Serial.println(F("Mode is useful for:"));
  Serial.println(F("  • Debugging connections"));
  Serial.println(F("  • Automatic parameter configuration"));
  Serial.println(F("  • Configuration documentation\n"));

  // ========== RECOMMENDATIONS ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║         GETTER METHODS APPLICATION            ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  getSpeed():                                  ║"));
  Serial.println(F("║    • Monitor current speed                    ║"));
  Serial.println(F("║    • Conditional logic                        ║"));
  Serial.println(F("║    • Telemetry and logging                    ║"));
  Serial.println(F("║    • Status checking                          ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  getMode():                                    ║"));
  Serial.println(F("║    • Check configuration                      ║"));
  Serial.println(F("║    • Debugging                                ║"));
  Serial.println(F("║    • Universal functions                      ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Cycle complete. Repeating in 5 seconds...\n\n"));
  delay(5000);
}
