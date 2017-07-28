#include "setting.h"


FBCmd Cmd;
Settings setting;
FBSerial serial;


#include "cmd.h"


void setup() {


  serial.begin(115200);


//Serial.println(setting._version);



 Cmd.bind(serial,setting);

 struct Cmd_Map m[]={
   {"cmd1",&cmd_class::cmd1},
   {"cmd2",&cmd2,&FBCmd::null},
   {"cmd3",&cmd2,&callback},
 };
 Cmd.add_map(m,sizeof(m));
 Cmd.add_map(Cmd_Map{"cmd4",&cmd_class::cmd1,&callback});


delay(1000);
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

  Serial.println("eoff");
  //setting.echo=false;
  //Serial.println(setting.echo);


// cd.load(CMDList,setting);

// cd.Debgu_setting();
// Serial.println("e");
// Serial.println(setting.echo);
// setting.echo=true;
// cd.Debgu_setting();


// cd.Debgu_map();
//   CMDList.push_back(Cmd_Map{"aaset",&f});
// cd.Debgu_map();
//




Serial.println("start");
}

void loop() {
  Serial.println("loop");
  delay(500);

}
