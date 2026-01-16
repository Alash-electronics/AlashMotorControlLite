/*
 * Language: English | Русский: ../RU/AllModesDemo/ | Қазақ: ../KZ/AllModesDemo/
 *
 * This example demonstrates all 4 motor driver operating modes:
 * 1. DIR_PWM      - 1 digital + 1 PWM pin
 * 2. PWM_PWM      - 2 PWM pins
 * 3. DIR_DIR_PWM  - 2 digital + 1 PWM pin
 * 4. DIR_DIR      - 2 digital pins (no PWM)
 *
 * Each mode is suitable for specific types of drivers.
 * Choose the mode according to your driver!
 *
 * IMPORTANT: This example is for demonstration. In a real project
 * use only ONE mode for your driver!
 *
 * Code written for Alash engineering
 */

#include "AlashMotorControlLite.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║  COMPARISON OF ALL OPERATING MODES            ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  delay(2000);
}

void loop() {
  // ========== MODE 1: DIR_PWM ==========
  Serial.println(F("═══════════════════════════════════════════════"));
  Serial.println(F("MODE 1: DIR_PWM"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Description:"));
  Serial.println(F("  • 1 digital pin (DIR) - direction"));
  Serial.println(F("  • 1 PWM pin (PWM) - speed\n"));

  Serial.println(F("Connection:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(DIR_PWM, 4, 3);"));
  Serial.println(F("           PIN 4 → DIR (direction)"));
  Serial.println(F("           PIN 3 → PWM (speed)\n"));

  Serial.println(F("Compatible drivers:"));
  Serial.println(F("  • TB6612FNG"));
  Serial.println(F("  • DRV8833"));
  Serial.println(F("  • Most H-Bridge modules\n"));

  Serial.println(F("Operating principle:"));
  Serial.println(F("  DIR=LOW,  PWM=128 → Forward at 50%"));
  Serial.println(F("  DIR=HIGH, PWM=128 → Reverse at 50%"));
  Serial.println(F("  DIR=X,    PWM=0   → Stop\n"));

  Serial.println(F("Advantages:"));
  Serial.println(F("  ✓ Simple connection"));
  Serial.println(F("  ✓ Intuitive logic"));
  Serial.println(F("  ✓ Pin saving\n"));

  Serial.println(F("Disadvantages:"));
  Serial.println(F("  ✗ Requires PWM pin for speed\n"));

  delay(5000);

  // ========== MODE 2: PWM_PWM ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("MODE 2: PWM_PWM"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Description:"));
  Serial.println(F("  • 2 PWM pins (IN1, IN2)"));
  Serial.println(F("  • Each pin controls direction\n"));

  Serial.println(F("Connection:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(PWM_PWM, 9, 10);"));
  Serial.println(F("           PIN 9  → IN1"));
  Serial.println(F("           PIN 10 → IN2\n"));

  Serial.println(F("  ESP32:   AlashMotorControlLite motor(PWM_PWM, 32, 33);"));
  Serial.println(F("           GPIO 32 → IN1"));
  Serial.println(F("           GPIO 33 → IN2\n"));

  Serial.println(F("Compatible drivers:"));
  Serial.println(F("  • ZK-5AD ★ RECOMMENDED for ESP32"));
  Serial.println(F("  • L298N"));
  Serial.println(F("  • BTS7960"));
  Serial.println(F("  • Dual-channel H-Bridge\n"));

  Serial.println(F("Operating principle:"));
  Serial.println(F("  IN1=128, IN2=0   → Forward at 50%"));
  Serial.println(F("  IN1=0,   IN2=128 → Reverse at 50%"));
  Serial.println(F("  IN1=0,   IN2=0   → Stop"));
  Serial.println(F("  IN1=255, IN2=255 → Brake\n"));

  Serial.println(F("Advantages:"));
  Serial.println(F("  ✓ Independent direction control"));
  Serial.println(F("  ✓ Better braking control"));
  Serial.println(F("  ✓ Ideal for ESP32 (many PWM channels)\n"));

  Serial.println(F("Disadvantages:"));
  Serial.println(F("  ✗ Requires 2 PWM pins"));
  Serial.println(F("  ✗ Limited PWM pins on Arduino\n"));

  delay(5000);

  // ========== MODE 3: DIR_DIR_PWM ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("MODE 3: DIR_DIR_PWM"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Description:"));
  Serial.println(F("  • 2 digital pins (IN1, IN2) - direction"));
  Serial.println(F("  • 1 PWM pin (PWM/EN) - speed\n"));

  Serial.println(F("Connection:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(DIR_DIR_PWM, 4, 5, 6);"));
  Serial.println(F("           PIN 4 → IN1 (direction 1)"));
  Serial.println(F("           PIN 5 → IN2 (direction 2)"));
  Serial.println(F("           PIN 6 → PWM/EN (speed)\n"));

  Serial.println(F("Compatible drivers:"));
  Serial.println(F("  • L298N (with EN pin)"));
  Serial.println(F("  • L293D"));
  Serial.println(F("  • Drivers with separate Enable pin\n"));

  Serial.println(F("Operating principle:"));
  Serial.println(F("  IN1=HIGH, IN2=LOW,  PWM=128 → Forward at 50%"));
  Serial.println(F("  IN1=LOW,  IN2=HIGH, PWM=128 → Reverse at 50%"));
  Serial.println(F("  IN1=X,    IN2=X,    PWM=0   → Stop"));
  Serial.println(F("  IN1=HIGH, IN2=HIGH, PWM=255 → Brake\n"));

  Serial.println(F("Advantages:"));
  Serial.println(F("  ✓ Clear separation of direction and speed"));
  Serial.println(F("  ✓ PWM pin saving (only 1)"));
  Serial.println(F("  ✓ Good compatibility\n"));

  Serial.println(F("Disadvantages:"));
  Serial.println(F("  ✗ Requires 3 pins per motor"));
  Serial.println(F("  ✗ Slightly more complex connection\n"));

  delay(5000);

  // ========== MODE 4: DIR_DIR ==========
  Serial.println(F("\n═══════════════════════════════════════════════"));
  Serial.println(F("MODE 4: DIR_DIR"));
  Serial.println(F("═══════════════════════════════════════════════\n"));

  Serial.println(F("Description:"));
  Serial.println(F("  • 2 digital pins (IN1, IN2)"));
  Serial.println(F("  • NO PWM - only on/off and direction\n"));

  Serial.println(F("Connection:"));
  Serial.println(F("  Arduino: AlashMotorControlLite motor(DIR_DIR, 4, 5);"));
  Serial.println(F("           PIN 4 → IN1"));
  Serial.println(F("           PIN 5 → IN2\n"));

  Serial.println(F("Compatible drivers:"));
  Serial.println(F("  • Relay modules"));
  Serial.println(F("  • Simple H-Bridge without PWM"));
  Serial.println(F("  • Drivers with built-in speed controller\n"));

  Serial.println(F("Operating principle:"));
  Serial.println(F("  IN1=HIGH, IN2=LOW  → Forward (full speed)"));
  Serial.println(F("  IN1=LOW,  IN2=HIGH → Reverse (full speed)"));
  Serial.println(F("  IN1=LOW,  IN2=LOW  → Stop"));
  Serial.println(F("  IN1=HIGH, IN2=HIGH → Brake\n"));

  Serial.println(F("IMPORTANT: In this mode setSpeed() works as:"));
  Serial.println(F("  speed > 0  → Forward (full)"));
  Serial.println(F("  speed < 0  → Reverse (full)"));
  Serial.println(F("  speed == 0 → Stop"));
  Serial.println(F("  Speed value is ignored!\n"));

  Serial.println(F("Advantages:"));
  Serial.println(F("  ✓ No PWM pins required"));
  Serial.println(F("  ✓ Simplest connection"));
  Serial.println(F("  ✓ For drivers without PWM input\n"));

  Serial.println(F("Disadvantages:"));
  Serial.println(F("  ✗ No speed control"));
  Serial.println(F("  ✗ Only full speed on/off\n"));

  delay(5000);

  // ========== COMPARISON TABLE ==========
  Serial.println(F("\n╔═══════════════════════════════════════════════════════════╗"));
  Serial.println(F("║              COMPARISON TABLE                             ║"));
  Serial.println(F("╠═══════════════╦═══════╦═══════╦═══════════╦═══════════════╣"));
  Serial.println(F("║ Mode          ║ Pins  ║ PWM   ║ Speed     ║ Application   ║"));
  Serial.println(F("╠═══════════════╬═══════╬═══════╬═══════════╬═══════════════╣"));
  Serial.println(F("║ DIR_PWM       ║  2    ║  1    ║ Yes       ║ Universal     ║"));
  Serial.println(F("║ PWM_PWM       ║  2    ║  2    ║ Yes       ║ ESP32 + ZK-5AD║"));
  Serial.println(F("║ DIR_DIR_PWM   ║  3    ║  1    ║ Yes       ║ L298N with EN ║"));
  Serial.println(F("║ DIR_DIR       ║  2    ║  0    ║ No        ║ Relay/On-Off  ║"));
  Serial.println(F("╚═══════════════╩═══════╩═══════╩═══════════╩═══════════════╝\n"));

  // ========== RECOMMENDATIONS ==========
  Serial.println(F("╔═══════════════════════════════════════════════╗"));
  Serial.println(F("║           HOW TO CHOOSE A MODE?               ║"));
  Serial.println(F("╠═══════════════════════════════════════════════╣"));
  Serial.println(F("║  1. Check your driver's datasheet             ║"));
  Serial.println(F("║  2. Determine input type:                     ║"));
  Serial.println(F("║     • DIR + PWM → DIR_PWM                     ║"));
  Serial.println(F("║     • IN1 + IN2 (both PWM) → PWM_PWM          ║"));
  Serial.println(F("║     • IN1 + IN2 + EN → DIR_DIR_PWM            ║"));
  Serial.println(F("║     • Only on/off → DIR_DIR                   ║"));
  Serial.println(F("║                                                ║"));
  Serial.println(F("║  Popular drivers:                             ║"));
  Serial.println(F("║  • L298N        → DIR_DIR_PWM or PWM_PWM      ║"));
  Serial.println(F("║  • TB6612FNG    → DIR_PWM                     ║"));
  Serial.println(F("║  • ZK-5AD       → PWM_PWM                     ║"));
  Serial.println(F("║  • DRV8833      → DIR_PWM                     ║"));
  Serial.println(F("║  • BTS7960      → PWM_PWM                     ║"));
  Serial.println(F("╚═══════════════════════════════════════════════╝\n"));

  Serial.println(F("Cycle complete. Repeating in 10 seconds...\n\n"));
  delay(10000);
}
