
#include <dummy.h>
#include <FS.h>

#define AC_DEBUG
#define DEBUG

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
      //mov();
    }

    while (Serial.available()) {
      Serial.read();
    }

    analogWrite(D4, 999);
  }

}
