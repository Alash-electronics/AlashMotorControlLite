# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**AlashMotorControlLite** is an Arduino library for controlling DC motors through various motor driver chips. The library provides a unified API that abstracts different motor driver configurations, supporting both Arduino and ESP32 platforms.

**Key Design Goals:**
- Simple, intuitive speed control (-100 to 100 range)
- Support for multiple motor driver types through MODE enum
- Cross-platform compatibility (Arduino, ESP32)
- Protection against incorrect usage (automatic speed limiting, copy prevention)

## Core Architecture

### MODE System

The library uses a MODE enum to handle 4 different motor driver configurations:

1. **DIR_PWM** (2 pins): 1 digital direction pin + 1 PWM speed pin
   - Compatible with: TB6612FNG, DRV8833
   - Most common Arduino setup

2. **PWM_PWM** (2 pins): 2 PWM pins for bidirectional control
   - Compatible with: ZK-5AD, L298N, BTS7960
   - Recommended for ESP32 (abundant PWM channels)

3. **DIR_DIR_PWM** (3 pins): 2 digital direction pins + 1 PWM enable pin
   - Compatible with: L298N with EN pin, L293D
   - Clear separation of direction and speed

4. **DIR_DIR** (2 pins): 2 digital pins, no PWM (on/off only)
   - For relay modules or drivers without PWM input
   - Speed value ignored, only direction matters

### ESP32 Dual PWM API Support

The library supports both ESP32 Arduino Core versions:

- **ESP32 2.x** (old API): `ledcSetup()` + `ledcAttachPin()` + `ledcWrite(channel, duty)`
- **ESP32 3.x** (new API): `ledcAttach(pin, freq, res)` + `ledcWrite(pin, duty)`

This is handled via `ESP_ARDUINO_VERSION` macro checks throughout the codebase. When adding ESP32 PWM code, always include both API branches.

**ESP32 PWM Channel Management:**
- Static `_nextChannel` counter auto-assigns channels (ESP32 2.x only)
- PWM frequency: 5000 Hz, 8-bit resolution
- PWM_PWM mode uses 2 channels per motor instance

### Speed System

**User-facing API:** Speed range is -100 to 100
- Negative values = backward
- Positive values = forward
- Zero = stopped

**Internal implementation:** Speeds are mapped to 0-255 PWM duty cycle using Arduino's `map()` function.

**Automatic Protection:**
- Values > 100 are clamped to 100
- Values < -100 are clamped to -100
- `_currentSpeed` tracks the user-specified speed (not PWM value)

### Stop vs Brake

Two stopping methods with different behaviors:

- **stop()**: Coast stop - disables motor, allows free spinning
- **brake()**: Active braking - shorts motor terminals, rapid stop

Implementation varies by MODE but generally:
- `stop()`: Sets all control pins to LOW or PWM to 0
- `brake()`: Sets specific pin combinations that short the H-bridge

## Examples Structure

The library includes 17 examples organized into 3 categories:

**Базовые примеры (7):** Educational examples demonstrating library features
- StopVsBrake, GettersDemo, SmoothSpeed, AllModesDemo, SpeedLimits, DirectionChange, MultiMotorSync

**Режимы драйверов (6):** Examples for specific MODE configurations
- DIR_PWM, DIR_PWM_DualMotor, PWM_PWM_DualMotor, DIR_DIR_PWM, DIR_DIR_PWM_DualMotor, DIR_DIR_PWM_pot

**ESP32 специализированные (4):** Advanced ESP32 applications
- ESP32_ZK5AD_SingleMotor, ESP32_ZK5AD_DualMotor, ESP32_Mecanum_4WD_Demo, ESP32_Mecanum_Serial

### Example Conventions

- All examples include Russian comments (target audience)
- Serial output at 115200 baud
- Use `#if defined(ARDUINO_ARCH_ESP32)` for platform-specific code
- Include detailed connection diagrams in comments
- Demonstrate proper usage patterns (smooth ramping, synchronized multi-motor control, etc.)

## Building and Testing

This is an Arduino library. No traditional build system.

**To test locally:**
1. Symlink or copy library to Arduino libraries folder:
   - Windows: `Documents\Arduino\libraries\AlashMotorControlLite`
   - macOS: `~/Documents/Arduino/libraries/AlashMotorControlLite`
   - Linux: `~/Arduino/libraries/AlashMotorControlLite`

2. Open Arduino IDE and verify any example compiles:
   - File → Examples → AlashMotorControlLite → [example]
   - Select board (Arduino Uno, ESP32 Dev Module, etc.)
   - Sketch → Verify/Compile

3. For ESP32 testing, ensure ESP32 board package is installed:
   - File → Preferences → Additional Board Manager URLs
   - Add: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`

**No automated tests exist.** Testing requires physical hardware (motor + driver + microcontroller).

## Library Metadata Files

- **library.properties**: Arduino library metadata (version, author, category)
  - Update `version` field when releasing
  - Current: 1.0.7

- **keywords.txt**: Arduino IDE syntax highlighting
  - Format: `keyword<TAB>KEYWORD_TYPE`
  - Must include all public methods and MODE enum values

## Critical Implementation Details

### Constructor Overloading
Two constructors handle 2-pin and 3-pin configurations:
- `AlashMotorControlLite(MODE, pin1, pin2)` for DIR_PWM, PWM_PWM, DIR_DIR
- `AlashMotorControlLite(MODE, pin1, pin2, pin_pwm)` for DIR_DIR_PWM

**Parameter order is critical** - do not reorder pins as it breaks compatibility.

### Copy Prevention
Class has private copy constructor and assignment operator to prevent multiple objects controlling the same pins. Arduino doesn't have proper RAII, so copying would lead to pin conflicts.

### Static Channel Counter (ESP32)
The `_nextChannel` static variable ensures each motor instance gets unique PWM channels on ESP32 2.x. This is a global counter that never resets during runtime. If creating/destroying many motor objects, be aware of the 16-channel limit on ESP32.

## Common Modifications

### Adding a new MODE
1. Add enum value to `MODE` in AlashMotorControlLite.h
2. Add case to switch statements in: `setSpeed()`, `brake()`, `stop()`
3. Update constructor initialization if needed
4. Add to keywords.txt
5. Create example demonstrating the mode
6. Update AllModesDemo example

### Supporting new PWM API (future ESP32 versions)
Add another `#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(X, Y, Z)` branch in all PWM-related code sections (both constructors, setSpeed, brake, stop).

### Adding new methods
1. Declare in public section of AlashMotorControlLite.h
2. Implement in AlashMotorControlLite.cpp
3. Add to keywords.txt with appropriate KEYWORD type
4. Create demonstration example
5. Document in existing examples where relevant

## Language and Style

- **Comments in Russian** for target audience (Kazakhstan/Russia market)
- **Code in English** (class names, variables, functions)
- Examples use extensive Serial.println() with box-drawing characters for visual formatting
- Maintain consistent indentation (2 spaces in .cpp/.h files)
- Use descriptive variable names even if longer

## Platform-Specific Notes

**Arduino (AVR):**
- Limited PWM pins (usually 3, 5, 6, 9, 10, 11)
- Use `analogWrite()` directly
- DIR_PWM mode most common

**ESP32:**
- All pins support PWM (via LEDC peripheral)
- PWM_PWM mode recommended (2 pins instead of 1 PWM + 1 digital)
- Must handle API version differences (2.x vs 3.x)
- ZK-5AD driver popular in this ecosystem

## Repository Structure

```
AlashMotorControlLite/
├── src/
│   ├── AlashMotorControlLite.h    # Class declaration, MODE enum
│   └── AlashMotorControlLite.cpp  # Implementation with platform ifdefs
├── examples/                       # 17 examples (see Examples Structure)
├── library.properties              # Arduino library metadata
├── keywords.txt                    # IDE syntax highlighting
├── LICENSE                         # MIT license
└── README.md                       # Russian installation/usage guide
```

## External Resources

- Website: https://alash-electronics.kz/
- GitHub: https://github.com/Alash-electronics/AlashMotorControlLite
- Target market: Kazakhstan, Russia (hence Russian documentation)
