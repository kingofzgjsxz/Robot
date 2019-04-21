
#include <Servo.h>

Servo myservo3;
Servo myservo4;

int pos3=0;
int pos4=0;

void setup() {
  myservo3.attach(12);
  myservo4.attach(13);
}

void loop() {
  while(true){
    pos3+=360;
    pos4+=360;
    myservo3.write(pos3);
    myservo4.write(pos4);
  }
}
