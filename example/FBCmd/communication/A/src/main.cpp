#include "setting.h"


FBCmd Cmd;
Settings setting;
FBSerial serial;
FBSerial conn;

Timer timer1;
Timer timer2;
Timer timer3;

int sum=0;

//000B和000C返回的结果进行处理
void callback(Cmd_Frame &input){
  if (input.result){
    String value=input.data;
    int val=value.toInt();

    if (input.addr_s=="000B"){//判断数据来自哪个设备
      sum+=val;
    }
    if (input.addr_s=="000C"){
      sum+=val*2;
    }

  }
}

//发送命令
void send(String target_address){
  Cmd_Frame cf;
  cf.addr_t=target_address;
  cf.addr_s=Cmd.get_address();
  cf.cmd="get_value";
  Cmd.serialOut(cf);
}


void setup() {

  //初始化串口，用于调试
  serial.bind(115200);

  //初始化与子设备通讯的软串口
  conn.bind(3,4,9600);


  //FBCmd绑定
  Cmd.bind(conn,setting);

  //添加命令列表，本机发送get_value命令，接收应答
  Cmd.add_map(Cmd_Map{"get_value",&FBCmd::null,&callback});

  //设置本机地址
  Cmd.set_address("000A");
  //设备间通讯，为防止干扰，应关闭回显
  setting.echo=false;
  setting.quiet=false;
  setting.save();


}

void loop() {
  Cmd.loop();
  if (timer1.every_ms(3000)){
    //向000B发送命令
    send("000B");
  }
  if (timer2.every_ms(5000)){
    //向000C发送命令
    send("000C");
  }
  if (timer3.every_ms(2000)){//每2秒向串口输出调试结果
    serial.print("now sum is :");
    serial.println(sum);
  }

}
