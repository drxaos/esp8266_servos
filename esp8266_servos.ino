
#include <dummy.h>
#include <FS.h>

#define AC_DEBUG
#define DEBUG
#define ENABLE_DEBUG_OUTPUT

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  SPIFFS.begin();
  Serial.println("spiffs listing /");
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    String str = "";
    str += dir.fileName();
    str += " / ";
    str += dir.fileSize();
    str += "\r\n";
    Serial.print(str);
  }
  Serial.println("listing end");

  pinMode(D4, OUTPUT);
  analogWriteFreq(500);
  analogWrite(D4, 999);

  initWifi();
  initWeb();
  initPwm();

  Serial.println("sketch started");
}

void loop() {
  loopWifi();

  if (Serial.available()) {
    analogWrite(D4, 1);

    String m = Serial.readStringUntil(' ');
    m.trim();

    if (m == "mov") {
      int x = Serial.parseInt();
      int y = Serial.parseInt();
      mov(x, y);
    }

    if (m == "write") {
      int n = Serial.parseInt();
      int on = Serial.parseInt();
      int off = Serial.parseInt();
      pwmWrite(n, on, off);
    }

    if (m == "read") {
      int n = Serial.parseInt();
      pwmRead(n);
    }

    if (m == "begin") {
      pwmBegin();
    }

    if (m == "freq") {
      int f = Serial.parseInt();
      pwmFreq(f);
    }

    if (m == "output") {
      int n = Serial.parseInt();
      int v = Serial.parseInt();
      pinMode(n, OUTPUT);
      digitalWrite(n, v);
      Serial.printf("output: %d = %d\n", n, v);
    }

    if (m == "input") {
      int n = Serial.parseInt();
      pinMode(n, INPUT);
      int v = digitalRead(n);
      Serial.printf("input: %d = %d\n", n, v);
    }

    while (Serial.available()) {
      Serial.read();
    }

    analogWrite(D4, 999);
  }

  yield();
}
