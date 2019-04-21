#include <Servo.h>
Servo myservo;
int pos=0;
void setup() {
  myservo.attach(8);
  // put your setup code here, to run once:
}

void loop() {
  int val;
  val=analogRead(0);
  if(val>900){
    for(pos=0;pos<130;pos++)
    {
      myservo.write(pos);
      delay(15);
    }
    for(pos=180;pos>=50;pos-=1)
    {
      myservo.write(pos);
      delay(15);
    }
  }
  

}
