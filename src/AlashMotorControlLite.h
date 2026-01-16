#ifndef ALASHMOTORCONTROLLITE_H
#define ALASHMOTORCONTROLLITE_H

#include <Arduino.h>
#include <stdint.h>

enum MODE {
  DIR_PWM,
  PWM_PWM,
  DIR_DIR_PWM,
  DIR_DIR
};
class AlashMotorControlLite{
  public:
    AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2);
    AlashMotorControlLite(MODE mode, uint8_t pin1, uint8_t pin2, uint8_t pin_pwm);
    void setSpeed(int16_t speed);
    void brake();
    void stop();
    int16_t getSpeed() const;
    MODE getMode() const;

  protected:
    MODE _mode;
    uint8_t _pin_pwm;
    uint8_t _pin1;
    uint8_t _pin2;
    int16_t _currentSpeed;

#if defined(ARDUINO_ARCH_ESP32)
    uint8_t _pwm_channel;
    uint8_t _pwm_channel1;
    uint8_t _pwm_channel2;
    static uint8_t _nextChannel;
#endif

  private:
    // Copy prevention
    AlashMotorControlLite(const AlashMotorControlLite&);
    AlashMotorControlLite& operator=(const AlashMotorControlLite&);
};
#endif
