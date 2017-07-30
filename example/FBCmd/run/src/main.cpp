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

  delay(2000);













// Cmd_Frame cf;
//
// cf.id=23;
// cf.id++;
// cf.cmd="cmddd";
// cf.data="fds,efffd,sdfes,dfdfes,sdf";
// cf.addr_s="re53";
// cf.addr_t="2345664";
//
// Serial.println("stringify:");
// String ss=Cmd.stringify(cf);
// Serial.println(ss);
//
// Serial.println("cf:");
// String c="";
// c="+{}cd(1):C123;";
// Cmd_Frame cc=Cmd.parse(c);
// Cmd.Debug_CF(cc);


// Cmd.run(cf);

// Serial.print("freeMemory()=");
//     Serial.println(freeMemory());
// String cmd="asdf";
// int index=cmd.indexOf(':');
// Serial.println(index);


//Cmd_Map fm={"set",&f};
//  CMDList.push_back(Cmd_Map{"set",&f});
//    CMDList.push_back(fm);
//  l.push_back(struct Cmd_Map{"set",&f});

}

void loop() {
  Cmd.loop();
}
