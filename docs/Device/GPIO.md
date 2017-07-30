# GPIO

### 功能

对IO的抽象层

### 实例

```
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

```

### 主要方法

#### GPIO(int _pin);

实例化并直接绑定到一个IO口

#### void bind(int _pin);

绑定到一个IO口

#### void A();

设置为模拟模式

#### void D();

设置为数字模式，初始化默认为数字模式

#### void input();

设置为输入模式

#### void output();

设置为输出模式

#### void pullup();

设置为带内部上拉的输入模式

#### void set(int c);

设置电平

#### int get();

获取电平

#### void high();

设置为高电平

#### void low();

设置为低电平

#### bool isHigh();

当前是否是高电平，高电平返回true

#### bool isLow();

当前是否是底电平，底电平返回true

#### bool waitHigh(long max_ms=-1);

等待，直到IO输入为高电平后返回true，可设置超时时间，超时后返回false

#### bool waitLow(long max_ms=-1);

等待，直到IO输入为底电平后返回true，可设置超时时间，超时后返回false
