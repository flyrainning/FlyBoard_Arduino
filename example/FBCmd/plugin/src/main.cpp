#include "setting.h"
#include "FBCmd_Ctrl.h"

FBCmd Cmd;
Settings setting;
FBSerial serial;

FBCmd_Ctrl CC(Cmd);



void setup() {

  //初始化串口
  serial.bind(115200);


  //FBCmd绑定
  serial.println("start bind");
  Cmd.bind(serial,setting);



}

void loop() {
  Cmd.loop();
}
