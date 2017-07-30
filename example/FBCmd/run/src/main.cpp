#include "setting.h"


FBCmd Cmd;
Settings setting;
FBSerial serial;

Timer timer1;
Timer timer2;
Timer timer3;

#include "cmd.h"


void run_cmd_1(){
  Cmd_Frame cf;
  cf.result=true;
  cf.cmd="cmd1";
  cf.data="I'm cmd1 data";
  Cmd_Frame result=Cmd.run(cf);
  if (result.result){
    serial.println(result.data);
  }
}

void run_cmd_2(){

  String result=Cmd.run("cmd2","I'm cmd2 data");
  serial.println(result);

}


void setup() {

  //初始化串口
  serial.bind(115200);


  //FBCmd绑定
  serial.println("start bind");
  Cmd.bind(serial,setting);

  //添加命令列表，两种方式
  serial.println("add cmd");

  Cmd.add_map(Cmd_Map{"cmd1",&cmd_class::cmd1,&callback});
  Cmd.add_map(Cmd_Map{"cmd2",&cmd2,&callback});
  Cmd.add_map(Cmd_Map{"cmd3",&cmd3});

  //可以通过配置对象直接修改CMD配置，控制程序行为
  setting.echo=true;//打开回显
  setting.quiet=false;//发送响应
  setting.save();



}

void loop() {
  Cmd.loop();
  if (timer1.every_ms(1000)){
    run_cmd_1();
  }
  if (timer2.every_ms(3000)){
    run_cmd_2();
  }
  if (timer3.every_ms(5000)){
    Cmd_Frame cf=Cmd.parse("-cmd3(i'm cmd3 data);");
    Cmd_Frame result=Cmd.run(cf);
    if (result.result){
      serial.println(result.data);
    }
  }
}
