#include <CPPM.h>

void setup() {
  attachCPPM(A0, 8);

  Serial.begin(115200);
  Serial.println("CPPM Library by David Hasko");
}

void loop() {
  for (byte i = 0; i < 8; i++) {
    Serial.print(CPPMget(i));
    Serial.write('\t');
  }
  Serial.println();
  delay(10);
}
