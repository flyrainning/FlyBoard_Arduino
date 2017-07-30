#include "setting.h"


FBCmd Cmd;
Settings setting;
FBSerial serial;


#include "cmd.h"


void setup() {

  //初始化串口
  serial.bind(115200);


  //FBCmd绑定
  serial.println("start bind");
  Cmd.bind(serial,setting);

  //添加命令列表，两种方式
  serial.println("add cmd");
  struct Cmd_Map m[]={
   {"cmd1",&cmd_class::cmd1},
   {"cmd2",&cmd2,&FBCmd::null},
   {"cmd3",&cmd2,&callback},
  };
  Cmd.add_map(m,sizeof(m));

  Cmd.add_map(Cmd_Map{"cmd4",&cmd_class::cmd1,&callback});

  //可以通过配置对象直接修改CMD配置，控制程序行为
  setting.echo=true;//打开回显
  setting.quiet=false;//发送响应
  setting.save();

  //Debug
  Cmd.Debug_setting();
  Cmd.Debug_map();


}

void loop() {
  Cmd.loop();
}
