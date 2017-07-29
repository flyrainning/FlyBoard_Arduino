# FBSerial

### 功能
提供统一的串口抽象，实现HardwareSerial、SoftwareSerial和AltSoftSerial混用，并可在使用过程中更换。

> 关于 [AltSoftSerial](https://github.com/PaulStoffregen/AltSoftSerial)

### 使用方法

实例化FBSerial，调用bind()与已知的HardwareSerial、SoftwareSerial或AltSoftSerial进行绑定，即可像使用普通串口一样使用FBSerial

### 实例

```

void setup() {

  FBSerial serial;
  serial.bind(115200);
  serial.println("HardwareSerial");

  FBSerial serial1;
  serial1.bind(Serial);
  serial1.begin(115200);
  serial.println("HardwareSerial");

  FBSerial serial2(Serial);
  serial1.begin(115200);
  serial.println("HardwareSerial");

  FBSerial serial3;
  serial3.bind(3,4,9600);
  serial3.println("SoftwareSerial RX 3,TX 4");

  SoftwareSerial softs(3,4);
  softs.begin(115200);
  FBSerial serial4;
  serial4.bind(softs);
  serial4.println("SoftwareSerial");

  FBSerial serial5;
  serial5.bindAlt(9600);
  serial5.println("AltSoftSerial");

}


```

### 主要方法

#### void bind

绑定到已经存在的串口，可以有以下形式
```

void bind(SoftwareSerial &_S);
void bind(HardwareSerial &_S);
void bind(AltSoftSerial &_S);
void bind(int RX,int TX,long baudrate=9600);
void bind(long baudrate=9600);

```
#### void bindAlt()

创建并绑定AltSoftSerial

#### void begin(long speed)

若绑定的串口没有调用过begin()，需调用以便打开串口
