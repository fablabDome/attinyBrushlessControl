#include <Servo.h>

const uint8_t VescOutputPin = 9;

const uint8_t PotentiometerPin = A0;

Servo esc;

void setup() {

  esc.attach(VescOutputPin);

  esc.writeMicroseconds(1500);
  delay(1000);
  Serial.begin(9600);

}

void loop() 
{
  int potVal = analogRead(A0);
  
  int result = map(potVal, 0 , 1023, 1000, 2000);
  result = constrain(result, 1000, 2000);
  Serial.println(result);
  esc.writeMicroseconds(result);

}
