#include "setting.h"


FBCmd Cmd;
Settings setting;
FBSerial serial;
FBSerial conn;



void getvalue(Cmd_Frame &input,Cmd_Frame &output){
  serial.println("get message from "+input.addr_s);
  serial.println("send back 2 ");
  output.out("2");
}

void setup() {

  //初始化串口，用于调试
  serial.bind(115200);

  //初始化与子设备通讯的软串口
  conn.bind(3,4,9600);


  //FBCmd绑定
  Cmd.bind(conn,setting);

  //添加命令列表，接收get_value命令
  Cmd.add_map(Cmd_Map{"get_value",&getvalue});


  //设置本机地址
  Cmd.set_address("000C");
  //设备间通讯，为防止干扰，应关闭回显
  setting.echo=false;
  setting.quiet=false;
  setting.save();


}

void loop() {
  Cmd.loop();
}
