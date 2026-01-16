// Language: English | Русский: ../RU/SpeedLimits/ | Қазақ: ../KZ/SpeedLimits/

/*
 * Example demonstrates automatic speed limiting
 *
 * The library automatically limits speed values to -100 to 100 range:
 * - Values > 100 are automatically set to 100
 * - Values < -100 are automatically set to -100
 * - This protects against programming errors
 *
 * This example shows how the protection works and how to properly
 * use the speed range.
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

void testSpeed(int requestedSpeed) {
  motor.setSpeed(requestedSpeed);
  int actualSpeed = motor.getSpeed();

  Serial.print(F("Requested: "));
  if (requestedSpeed >= 0) Serial.print(F(" "));
  Serial.print(requestedSpeed);
  Serial.print(F("  →  Set to: "));
  if (actualSpeed >= 0) Serial.print(F(" "));
  Serial.print(actualSpeed);

  if (requestedSpeed != actualSpeed) {
    Serial.print(F("  ⚠ LIMITED!"));
  } else {
    Serial.print(F("  ✓"));
  }

  Serial.println();
  delay(500);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  AUTOMATIC SPEED LIMITING                     ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== TESTING VALID VALUES ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("VALID VALUES (from -100 to 100)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Testing positive speeds:"));
  testSpeed(0);
  testSpeed(25);
  testSpeed(50);
  testSpeed(75);
  testSpeed(100);

  Serial.println(F("\nTesting negative speeds:"));
  testSpeed(0);
  testSpeed(-25);
  testSpeed(-50);
  testSpeed(-75);
  testSpeed(-100);

  motor.stop();
  delay(2000);

  // ========== TESTING UPPER LIMIT OVERFLOW ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("EXCEEDING UPPER LIMIT (+100)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Library will automatically limit values:\n"));

  testSpeed(100);   // Normal
  testSpeed(101);   // Will be limited to 100
  testSpeed(120);   // Will be limited to 100
  testSpeed(150);   // Will be limited to 100
  testSpeed(200);   // Will be limited to 100
  testSpeed(255);   // Will be limited to 100
  testSpeed(500);   // Will be limited to 100
  testSpeed(1000);  // Will be limited to 100
  testSpeed(32767); // Will be limited to 100

  motor.stop();
  delay(2000);

  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("EXCEEDING LOWER LIMIT (-100)"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Library will automatically limit values:\n"));

  testSpeed(-100);   // Normal
  testSpeed(-101);   // Will be limited to -100
  testSpeed(-120);   // Will be limited to -100
  testSpeed(-150);   // Will be limited to -100
  testSpeed(-200);   // Will be limited to -100
  testSpeed(-255);   // Will be limited to -100
  testSpeed(-500);   // Will be limited to -100
  testSpeed(-1000);  // Will be limited to -100
  testSpeed(-32768); // Will be limited to -100

  motor.stop();
  delay(2000);

  // ========== PRACTICAL EXAMPLES ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("PRACTICAL EXAMPLES"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Example 1: Safe speed summation\n"));

  Serial.println(F("int baseSpeed = 80;"));
  Serial.println(F("int boost = 30;"));
  Serial.println(F("motor.setSpeed(baseSpeed + boost);  // 80 + 30 = 110\n"));

  int baseSpeed = 80;
  int boost = 30;

  Serial.print(F("Result: "));
  testSpeed(baseSpeed + boost);  // Automatically limited to 100

  Serial.println(F("\nLibrary protects against overflow!\n"));
  delay(2000);

  Serial.println(F("Example 2: Using percentages\n"));

  Serial.println(F("int userInput = 150;  // User entered 150%"));
  Serial.println(F("motor.setSpeed(userInput);\n"));

  int userInput = 150;
  Serial.print(F("Result: "));
  testSpeed(userInput);  // Automatically limited to 100

  Serial.println(F("\nEven incorrect input is safe!\n"));
  delay(2000);

  Serial.println(F("Example 3: Mathematical calculations\n"));

  Serial.println(F("int sensorValue = analogRead(A0);  // 0-1023"));
  Serial.println(F("int speed = map(sensorValue, 0, 1023, -200, 200);"));
  Serial.println(F("motor.setSpeed(speed);\n"));

  // Simulate different sensor values
  Serial.println(F("With sensorValue = 0:"));
  testSpeed(-200);  // Limited to -100

  Serial.println(F("With sensorValue = 512:"));
  testSpeed(0);     // Middle

  Serial.println(F("With sensorValue = 1023:"));
  testSpeed(200);   // Limited to 100

  Serial.println(F("\nEven with incorrect map() protection works!\n"));

  motor.stop();
  delay(2000);

  // ========== BOUNDARY VALUES ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("BOUNDARY VALUES"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Exact range boundaries:\n"));

  testSpeed(99);    // Last valid before maximum
  testSpeed(100);   // Maximum
  testSpeed(101);   // First limited

  Serial.println();

  testSpeed(-99);   // Last valid before minimum
  testSpeed(-100);  // Minimum
  testSpeed(-101);  // First limited

  motor.stop();
  delay(2000);

  // ========== RECOMMENDATIONS ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║        USAGE RECOMMENDATIONS                  ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  Speed range: -100 to 100                     ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Values:                                       ║"));
  Serial.println(F("║    -100 = Full speed backward                 ║"));
  Serial.println(F("║      -50 = 50% backward                       ║"));
  Serial.println(F("║        0 = Stop                               ║"));
  Serial.println(F("║      +50 = 50% forward                        ║"));
  Serial.println(F("║     +100 = Full speed forward                 ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Protection works automatically:              ║"));
  Serial.println(F("║    • Values > 100 → set to 100                ║"));
  Serial.println(F("║    • Values < -100 → set to -100              ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Good practice:                               ║"));
  Serial.println(F("║    ✓ Use constrain() before setSpeed()        ║"));
  Serial.println(F("║    ✓ Check map() for correctness             ║"));
  Serial.println(F("║    ✓ Validate user input                     ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  But even if you forget - protection works!  ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  // ========== CODE EXAMPLES ==========
  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║              CODE EXAMPLES                    ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("// Correct: with validation"));
  Serial.println(F("int speed = analogRead(A0);"));
  Serial.println(F("speed = map(speed, 0, 1023, -100, 100);"));
  Serial.println(F("motor.setSpeed(speed);\n"));

  Serial.println(F("// Also works: library will protect"));
  Serial.println(F("int speed = analogRead(A0);"));
  Serial.println(F("speed = map(speed, 0, 1023, -200, 200);"));
  Serial.println(F("motor.setSpeed(speed);  // Limited automatically\n"));

  Serial.println(F("// With additional protection:"));
  Serial.println(F("int speed = getUserInput();"));
  Serial.println(F("speed = constrain(speed, -100, 100);"));
  Serial.println(F("motor.setSpeed(speed);  // Double protection\n"));

  Serial.println(F("Cycle complete. Repeating in 5 seconds...\n\n"));
  delay(5000);
}
