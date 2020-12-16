#include <TinyWireM.h>
#include <Tiny4kOLED.h>

void setup() {
  oled.begin();
  // Two fonts are supplied with Tiny4kOLED library, FONT8X16 and FONT6X8
  // Other fonts are available from the TinyOLED-Fonts library
  oled.setFont(FONT8X16);
  oled.on();
  //oled.invertOutput(false);
  delay(1000);
  oled.clear();
  oled.setCursor(0, 1);
  oled.invertOutput(false);
}

void loop() {
  int sensorValue = analogRead(A3);
  char buf[4];
  itoa(sensorValue, buf, 10);
  //sprintf(buf,"%d",sensorValue);
  if (sensorValue < 1000) buf[3] = ' ';
  if (sensorValue < 100) buf[2] = ' ';
  if (sensorValue < 10) buf[1] = ' ';
  oled.setCursor(15, 1);
  oled.print(buf);

}
