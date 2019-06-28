#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void initPwm() {
  Wire.begin(D1, D2);
  pwm.begin();
  pwm.setPWMFreq(500);
}

void mov(long x, long y) {
  Serial.printf("mov: %d, %d\n", x, y);

  // from 0 to 4095 inclusive
  pwm.setPin(0, x);
  pwm.setPin(1, y);
}
