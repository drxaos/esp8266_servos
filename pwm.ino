#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void initPwm() {

  // D1=SCL D2=SDA

  pwm.begin();
  pwm.reset();
  pwm.setPWMFreq(60);
}

void pwmBegin() {
  pwm.begin();
  Serial.println("begin: ok");
}

void pwmFreq(int f) {
  pwm.setPWMFreq(f);
  Serial.printf("freq: %d\n", f);
}

void mov(long x, long y) {
  Serial.printf("mov: %d, %d\n", x, y);

  // from 0 to 4095 inclusive
  pwm.setPWM(0, 0, x);
  pwm.setPWM(1, 0, y);
}

void pwmWrite(int n, int on, int off) {
  Serial.printf("write: n=%d, on=%d, off=%d\n", n, on, off);
  pwm.setPWM(n, on, off);
}

int pwmRead(int n) {
  Serial.printf("read: n=%d\n", n);
  int st = pwm.getPWM(n);
  Serial.printf("state %d: %d\n", n, st);
}
