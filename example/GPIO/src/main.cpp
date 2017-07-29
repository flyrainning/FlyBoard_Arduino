#include <Arduino.h>
#include "flyboard.h"

GPIO d3(3);//pin 3

void setup() {

  Serial.begin(9600);

  d3.output();//设置为输出
  d3.high();//输出高电平
  delay(1000);
  d3.low();//输出低电平



  GPIO d4;
  d4.bind(4);//绑定 pin 4
  d4.input();//设置为输入
  int a=d4.get();
  if (a==1) Serial.println("pin 4 is high");
  if (d4.isHigh()) Serial.println("pin 4 is high");
  if (d4.isLow()) Serial.println("pin 4 is low");

  GPIO d5;
  d5.bind(5);//绑定 pin 4
  d5.pullup();//设置为输入，内部上拉

  if (d5.waitLow(1000)){//等待变为低电平，返回true  最长等待1000ms，超时返回false
    Serial.println("pin 4 is low");
  }
  if (d5.waitHigh()){//等待高电平返回true，无超时
    Serial.println("pin 4 is high");
  }

  GPIO d6;
  d6.bind(13);//绑定 pin 4
  d6.in();//设置为输入 in() 等同input()  out()等同output()
  d6.A();//设置为模拟
  int d=d6.get();//取得模拟输入
  d6.set(10);//模拟输出
  d6.D();//切换到数字模式
  d6.low();
  d6.set(0);//等同d6.low();
  d6.set(1);//等同d6.high();

}

void loop() {

  delay(500);

}
