#include "setting.h"


FBCmd Cmd;
Settings setting;
FBSerial serial;



void setup() {

  //初始化串口
  serial.bind(115200);


  //FBCmd绑定
  serial.println("start bind");
  Cmd.bind(serial,setting);


  Cmd_Frame cf;

  cf.id=23;
  cf.cmd="cmd1";
  cf.data="fds,efffd,sdfes,dfdfes,sdf";
  cf.addr_s="re53";
  cf.addr_t="2342";

  Serial.println("stringify:");
  String ss=Cmd.stringify(cf);
  Serial.println(ss);
  /*
  stringify:
  -{23}2342:re53:cmd1(fds,efffd,sdfes,dfdfes,sdf):A5A1;
  */


  Serial.println("cf:");
  String c="-{12}1234:432a:cmd2(data of cmd2);";
  Cmd_Frame cc=Cmd.parse(c);
  Cmd.Debug_CF(cc);
  /*
  cf:
  Debug Cmd_Frame -----------------
  result : 1
  id : 12
  type : 0
  addr_t : 1234
  addr_s : 432a
  cmd : cmd2
  data : data of cmd2
  status : 0
  crc : 0
  -----------------
  */




}

void loop() {
  Cmd.loop();
}
