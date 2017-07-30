# FBCmd

## 功能

FBCmd提供了一个简单的串口交互式命令行接口

可以实现人机命令行交互或设备与设备间的串口通讯

## 特点

- 定义标准的命令结构，支持接收命令和应答
- 支持自定义设备地址，支持一对一，一对多，多对一通讯，支持广播
- 可以通过插件扩展命令集，也可添加自定义命令
- 支持参数传递
- 支持命令应答回调
- 支持CRC校验

## 依赖

- FBSettings
- FBSerial

## 可选配置

```
  //单条命令的最大长度
  #define CMD_BUFFER_MAX  128 //max buffer

  //命令头标识符
  #define CMD_TYPE_SYN '-'

  //应答头标识符
  #define CMD_TYPE_ACK '+'

  //命令结束标识符
  #define CMD_FLAG_END ';'
```

## 命令发送与接受

通讯是以帧为单位，帧分为命令帧和应答帧

出于兼容性考虑，帧在通讯过程中采用字符串模式

FBCmd内部会自动将字符串帧解析为Cmd_Frame结构体


字符串模式下，命令帧与应答帧采用相同的格式

`<type>[{id}][target_address:][source_address:]cmd([data])[:crc];`

|      位置      | 必须 |              说明              |     取值范围      |                   备注                    |
| -------------- | ---- | ------------------------------ | ----------------- | ----------------------------------------- |
| type           | 必选 | 通讯类型，标示命令或应答       | SYN ACK           | 可以通过CMD_TYPE_SYN 和 CMD_TYPE_ACK 设置 |
| id             | 可选 | 命令id，可防止命令重复执行     | uint16_t 0-65535  |                                           |
| target_address | 可选 | 目标地址                       | 4Byte  默认"0000" | "0000" 为广播地址                         |
| source_address | 可选 | 源地址，应答帧将使用此地址应答 | 4Byte  默认"0000" | "0000" 为广播地址                         |
| cmd            | 必选 | 命令                           |                   |                                           |
| data           | 可选 | 参数，传递到命令函数中         | String类型        |                                           |
| crc            | 可选 | crc16                          | 16bit HEX         | 如果存在，则校验，失败直接丢弃            |


### 示例

以下命令和应答都是合法帧

命令：

- -{25}C001:A001:switch1(on):3649;
- -0000:0000:cmd1(data);
- -cmd2(data);
- -cmd3();

应答：
- +0000:0000:cmd1(data);
- +A001:C001:switch1(on);

### 规则

- 命令帧包含{id}，则应答帧也包含{id}，值为id+1
- 命令或应答如果包含crc，则crc校验失败自动丢弃
- 地址为空默认自动填充为广播地址
- 命令帧中不能再包含 - + ; 等关键字符

例：
发送命令 `-{25}C001:A001:switch1(on):3649;`
表示由本机（地址A001）向目标（地址C001）发送命令 switch1 ，传递参数 on

目标设备执行switch1命令后返回应答`+{26}A001:C001:switch1(is on):955E;`
表示发送给A001的对于命令switch1的应答，结果为is on

收到命令帧，会调用命令对应的执行函数
收到应答帧，会调用命令对应的回调函数，回调函数常用于设备间通讯，发送查询指令后接收并处理结果


## 配置参数

FBCmd包含一个配置结构体`Settings_FBCmd`，使用时需要在自己的配置子对象中继承这个结构体

配置项目：

```
//是否启用输入回显
bool echo=false;

//是否启用安静模式，安静模式无任何返回，包括应答帧也不会发送
bool quiet=false;

//当前设备地址
char address[4]={'0','0','0','0'};

//帧结束附加发送的结束字符，如回车符
char end_char[2]={0,0};

//发送消息自动添加crc校验
bool auto_crc=true;

//解析消息必须验证crc，如果为true，没有crc的命令帧将被丢弃
bool required_crc=false;

//指向当前FBCmd实例的指针
void* Cmd=NULL;

```

## 命令的添加

FBCmd内部存在一个包含所有命令的列表，称为map，要将自己的函数添加为FBCmd支持的命令，需要调用`void add_map(Cmd_Map _map)`

### Cmd_Map

添加到map中的是Cmd_Map结构

```
struct Cmd_Map{
      String name;
      funcP func;
      funcPcallback callback;
};
```

|   name   |    命令名称    |
| -------- | -------------- |
| func     | 命令执行的函数，收到CMD_SYN请求调用此函数 |
| callback | 应答回调函数，收到CMD_ACK请求调用此函数   |

#### funcP

命令函数`typedef void (*funcP)(Cmd_Frame &input,Cmd_Frame &output);`

##### Cmd_Frame &input

命令解析完毕后的Cmd_Frame结构

##### Cmd_Frame &output

应答帧，由命令执行函数填充，函数执行完毕，若帧有效，自动发送应答

#### funcPcallback

回调函数`typedef void (*funcPcallback)(Cmd_Frame &input);`



#### 实例

```

typedef struct Settings:
  virtual public Settings_FBCmd
{
uint16_t  _version=1;
  Settings(){
    bind(this,sizeof(*this),_version);
  }
}Settings;

void cmd1(Cmd_Frame &input,Cmd_Frame &output){
  String p=input.data;
  output.out("I'm cmd2");

}
void callback(Cmd_Frame &input){
  String p=input.data;
  if (p=="something"){
    //do something
  }

}

void setup() {
  FBCmd Cmd;
  Settings setting;
  FBSerial serial;

  serial.bind(115200);
  Cmd.bind(serial,setting);


  //添加命令
  struct Cmd_Map m[]={
   {"cmd1",&cmd1},
   {"cmd3",&cmd1,&callback},
  };
  Cmd.add_map(m,sizeof(m));

  //或者逐条添加
  Cmd.add_map(Cmd_Map{"cmd4",&cmd1,&callback});


}
```
