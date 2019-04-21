#include<Servo.h>

Servo gearleft;
Servo gearright;
Servo catchleft;
Servo catchright;

//定义灰度传感器数值
int greysensorfleft;
int greysensorfright;
int greysensorbleft;
int greysensorbright;

//定义判断路口的判断器数值
int crossing=0;

//定义灰度传感器见到黑线的数值
int greysensorfleftblack=0;
int greysensorfrightblack=0;
int greysensorbleftblack=0;
int greysensorbrightblack=0;

//定义是否直着向前
bool chogostraight=true;

//定义是否轻度修正右偏
bool chofixrightlight;

//定义是否重度修正右偏
bool chofixrightheavy;

int s0=3,s1=4,s2=5,s3=6;
int out=2;
int flag=0;
byte counter=0;
byte countR=0,countG=0,countB=0;

int red;
int blue;
int green;

int good1R;
int good1B;
int good1G;

int good2R;
int good2B;
int good2G;

int good3R;
int good3B;
int good3G;


void setup() {
  gearleft.attach(13);
  gearright.attach(12);
  catchleft.attach(11);
  catchright.attach(10);

  pinMode(s0,OUTPUT);
 pinMode(s1,OUTPUT); 
 pinMode(s2,OUTPUT);
 pinMode(s3,OUTPUT);



}




void TCS()
 {
 flag=0;  
 digitalWrite(s1,HIGH);
 digitalWrite(s0,HIGH);
 digitalWrite(s2,LOW);
 digitalWrite(s3,LOW);
 attachInterrupt(0, ISR_INTO, LOW);
 timer0_init();

 }
void ISR_INTO()
 {
 counter++;
 }
 void timer0_init(void)
 {
  TCCR2A=0x00;
  TCCR2B=0x07;   //the clock frequency source 1024 points
  TCNT2= 100;    //10 ms overflow again
  TIMSK2 = 0x01; //allow interrupt
 }
 int i=0;
 ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
    TCNT2=100;
    flag++;
 if(flag==1)
  {
    countR=counter;
    red=countR;
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
  }
  else if(flag==2)
   {
    countG=counter;
    green=countG;
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
   }
   else if(flag==3)
    {
    countB=counter;
    blue=countB;
    Serial.println("\n"); 
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
   
    }
    else if(flag==4)
     {
     flag=0;
     }
       counter=0;
}




void loop() {
  greysensorfleft=analogRead(0)/100;
  greysensorfright=analogRead(1)/100;
  greysensorbleft=analogRead(3)/100;
  greysensorbright=analogRead(4)/100;

//正常直行
  if(greysensorfleft>=7&&greysensorfright>=7){
    gostraight();
  }



//修复轻度右偏
  if(greysensorfleft>=7&&greysensorfright<7&&crossing<3){
    fixrightlight();
  }

//修复重度右偏
  if(greysensorbleft>=7&&crossing<3){
    fixrightheavy();
  }


//修复轻度左偏
  if(greysensorfright>=7&&greysensorfleft<7&&crossing<3){
    fixleftlight();
  }

//修复重度右偏
  if(greysensorbright>=7&&crossing<3){
    fixleftheavy();
  }

//路口检测
  if(greysensorbleft>=7&&greysensorbright>=7){
    crossing+=1;
  }


  if(crossing==4){
    gearstop();
    turna();
    goturna();
    crossing=5;
  }

  

  if(crossing==5){
    catchleft.write(60);
    catchright.write(60);
    delay(5000);
    gearleft.write(20);
    gearright.write(160);
    crossing=6;
    delay(5000);
  }

  if(crossing==6){
    gearstop();
    gearleft.write(180);
    gearright.write(0);
    delay(3000);
    gearleft.write(100);
    gearright.write(30);
    delay(1600);
    gearstop();
    gearleft.write(180);
    gearright.write(0);
    delay(3000);
    gearstop();
    catchleft.write(180);
    catchright.write(180);
    gearleft.write(0);
    gearright.write(180);
    delay(5000);
    gearleft.write(130);
    gearright.write(50);
    delay(3000);
    gearstop();
    crossing=7;
  }

  if(crossing==7){
    gearleft.write(180);
    gearright.write(30);
    delay(4000);
    gearstop();
    catchleft.write(60);
    catchright.write(60);
    gearleft.write(0);
    gearright.write(180);
    delay(7000);
    gearstop();
    gearleft.write(150);
    gearright.write(150);
    delay(2000);
    catchleft.write(180);
    catchright.write(180);
    gearleft.write(150);
    gearright.write(150);
    delay(2000);
    crossing=8;
  }

  if(crossing==8){
    gearstop();
    turnb();
    goturnb();
    crossing=9;
  }

  

  if(crossing==9){
    catchleft.write(60);
    catchright.write(60);
    delay(5000);
    gearleft.write(20);
    gearright.write(160);
    crossing=10;
    delay(5000);
    gearstop();
  }

  if(crossing==10){
    gearstop();
    gearleft.write(180);
    gearright.write(0);
    delay(3000);
    gearleft.write(30);
    gearright.write(100);
    delay(1600);
    gearstop();
    gearleft.write(180);
    gearright.write(0);
    delay(3000);
    gearstop();
    catchleft.write(180);
    catchright.write(180);
    gearleft.write(0);
    gearright.write(180);
    delay(5000);
    gearstop();
    crossing=11;
  }
  

  

  
  

}


void gostraight(){
  gearleft.write(180);
  gearright.write(0);
}

void gearstop(){
  gearleft.write(90);
  gearright.write(90);
}

void goturna(){
  gearleft.write(134);
  gearright.write(40);
  delay(2000);
  gearstop();
}

void goturnb(){
  gearleft.write(140);
  gearright.write(40);
  delay(2000);
  gearstop();
}


void fixrightlight(){
  gearleft.write(170);
  gearright.write(0);
}

void fixrightheavy(){
  gearleft.write(160);
  gearright.write(0);
}



void fixleftlight(){
  gearleft.write(180);
  gearright.write(10);
}

void fixleftheavy(){
  gearleft.write(180);
  gearright.write(20);
}

void turna(){
  gearleft.write(120);
  gearright.write(0);
  //控制时间****************************************************
  delay(30);
}

void turnb(){
  gearleft.write(0);
  gearright.write(120);
  //控制时间****************************************************
  delay(30);
}

