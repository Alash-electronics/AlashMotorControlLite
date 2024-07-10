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
    AlashMotorControlLite(MODE mode, uint8_t pin_pwm, uint8_t pin1, uint8_t pin2);
    void setSpeed(int16_t speed);
    void brake();
    
  protected:
    MODE _mode;
    uint8_t _pin_pwm;
  	uint8_t _pin1;
    uint8_t _pin2;
};
#endif
