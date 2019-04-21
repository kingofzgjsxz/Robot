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

void setup() {
  Serial.begin(9600);
}

void loop() {
  greysensorfleft=analogRead(0)/100;
  greysensorfright=analogRead(1)/100;
  greysensorbleft=analogRead(3)/100;
  greysensorbright=analogRead(4)/100;

  if(greysensorbleft>=7&&greysensorbleft>=7){
    crossing+=1;
  }

  Serial.print(cossing);

}
