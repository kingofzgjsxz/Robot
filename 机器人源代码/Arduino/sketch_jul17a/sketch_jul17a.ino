#include <Servo.h>

Servo myservo1;
Servo myservo2;

bool a=true;

void setup() {
  myservo1.attach(12);
  myservo2.attach(11);
  myservo1.write(0);
  myservo2.write(180);
}

void loop() {  
}
