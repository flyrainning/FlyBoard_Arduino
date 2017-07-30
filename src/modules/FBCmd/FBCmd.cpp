#include "FBCmd.h"

FBCmd::FBCmd(){
}
FBCmd::~FBCmd(){
}
//debug
void FBCmd::Debug_map(std::vector<Cmd_Map> &map){
  Serial.println(F("Debug map -----------------"));
  int size=map.size();

  for(int i=0; i<size; i++) {
    Serial.println(map.at(i).name);
  }
  Serial.println(F("-----------------"));
}
void FBCmd::Debug_map(){
  Debug_map(map);
}
void FBCmd::Debug_setting(){
  Serial.println(F("Debug setting -----------------"));
  Serial.print(F("setting.echo : "));
  Serial.println(setting->echo);
  Serial.print(F("setting.quiet : "));
  Serial.println(setting->quiet);
  Serial.print(F("setting.address : "));
  Serial.println(setting->address);
  Serial.print(F("setting.end_char : "));
  Serial.println(setting->end_char);
  Serial.print(F("setting.auto_crc : "));
  Serial.println(setting->auto_crc);
  Serial.print(F("setting.required_crc : "));
  Serial.println(setting->required_crc);
  Serial.println(F("-----------------"));

}
void FBCmd::Debug_CF(Cmd_Frame &cf){
  Serial.println(F("Debug Cmd_Frame -----------------"));
  Serial.print(F("result : "));
  Serial.println(cf.result);
  Serial.print(F("id : "));
  Serial.println(cf.id);
  Serial.print(F("type : "));
  Serial.println(cf.type);
  Serial.print(F("addr_t : "));
  Serial.println(cf.addr_t);
  Serial.print(F("addr_s : "));
  Serial.println(cf.addr_s);
  Serial.print(F("cmd : "));
  Serial.println(cf.cmd);
  Serial.print(F("data : "));
  Serial.println(cf.data);
  Serial.print(F("status : "));
  Serial.println(cf.status);
  Serial.print(F("crc : "));
  Serial.println(cf.crc,HEX);
  Serial.println(F("-----------------"));
}

void FBCmd::load_setting(Settings_FBCmd &_setting){
  setting=&_setting;
}
void FBCmd::load_serial(FBSerial &_serial){
  serial=&_serial;
}
void FBCmd::bind(FBSerial &_serial,Settings_FBCmd &_setting){
  load_setting(_setting);
  load_serial(_serial);
  setting->Cmd=this;
}


void FBCmd::set_Endchar(uint8_t c1,uint8_t c2){
  setting->end_char[0]=c1;
  setting->end_char[1]=c2;
//  setting->save();
}
String FBCmd::get_address(){
  String addr;
  for (size_t i = 0; i < 4; i++) {
    addr+=setting->address[i];
  }
  return addr;
}
void FBCmd::set_address(String address){
  for (size_t i = 0; i < 4; i++) {
    setting->address[i]=address.charAt(i);
  }
//  setting->save();
}
void FBCmd::quiet(bool enable){
  setting->quiet=enable;
//  setting->save();
}
void FBCmd::quiet(String enable){
  bool enablebol=(enable=="true")?true:false;
  quiet(enablebol);
}
void FBCmd::echo(bool enable){
  setting->echo=enable;
//  setting->save();
}

void FBCmd::echo(String enable){
  bool enablebol=(enable=="true")?true:false;
  echo(enablebol);
}

void FBCmd::add_map(std::vector<Cmd_Map> &_map){
  map.insert(map.end(),_map.begin(),_map.end());
}
void FBCmd::add_map(Cmd_Map _map){
  map.push_back(_map);
}

void FBCmd::add_map(Cmd_Map _map[],int _count){
  int count=_count/sizeof(Cmd_Map);
  for (int i = 0; i < count; i++){
    map.push_back(_map[i]);
  }
}
void FBCmd::set_map(std::vector<Cmd_Map> &_map){
  map=_map;
}

Cmd_Frame FBCmd::receive(char receiveVal) {
    receive_cf.result=false;
    if (setting->echo) serial->write(receiveVal);
    if ((receiveVal==CMD_TYPE_SYN)||(receiveVal==CMD_TYPE_ACK)){
      cmd_str=receiveVal;
      cmd_len=1;
    }else if (receiveVal==CMD_FLAG_END){
      cmd_str+=receiveVal;
      receive_cf=parse(cmd_str);
      cmd_str="";
      cmd_len=0;

    }else{
      if (cmd_len<CMD_BUFFER_MAX){
        cmd_len++;
        cmd_str+=receiveVal;
      }else{
        cmd_str="";
        cmd_len=0;
      }
    }
    return receive_cf;

}
Cmd_Frame FBCmd::parse(const char *cmd){
  String str(cmd);
  return parse(str);
}
Cmd_Frame FBCmd::parse(String &cmd){
  cmd.trim();
  Cmd_Frame cf;
  cf.result=false;
  int p=0;
  int index=0;
  int len=cmd.length();
  int cmdend=cmd.indexOf('(');

  if (cmd.length()<4) return cf;
  if (cmd.charAt(0)==CMD_TYPE_SYN){
    cf.type=CMD_SYN;
  }else if (cmd.charAt(0)==CMD_TYPE_ACK){
    cf.type=CMD_ACK;
  }else{
    cf.status=1;
    return cf;
  }

  //id
  p++;
  if (cmd.charAt(p)=='{'){
    index=cmd.indexOf('}');
    if (index>=p){
      cf.id=cmd.substring(p+1,index).toInt();
      p=index+1;
    }else{
      cf.status=2;
      return cf;
    }
  }
  //addr_t
  index=cmd.indexOf(':',p);
  if ((index<cmdend)&&(index>p)){
    cf.addr_t=cmd.substring(p,index);
    p=index+1;
    //addr_s
    index=cmd.indexOf(':',p);
    if (index>p){
      cf.addr_s=cmd.substring(p,index);
      p=index+1;
    }
  }

  //cmd
  index=cmd.indexOf('(',p);
  if (index>p){
    cf.cmd=cmd.substring(p,index);
    p=index+1;
  }else{
    cf.status=3;
    return cf;
  }
  //data
  index=cmd.indexOf(')',p);
  if (index>=p){
    cf.data=cmd.substring(p,index);
    p=index+1;
  }else{
    cf.status=4;
    return cf;
  }

  //checksum
  if (cmd.charAt(p)==':'){
    if (len>(p+4)){
      String cs=cmd.substring(p+1,p+4);
      uint16_t crcint=crc16.checksum(cmd,0,p-1);
      String cs2=crc16.toHexStr(crcint);
      if (cs==cs2){
        cf.crc=crcint;
      }else{
        cf.status=7;
        return cf;
      }
    }else{
      cf.status=6;
      return cf;
    }
  }else{
    if (setting->required_crc){
      cf.status=6;
      return cf;
    }
  }

  cf.result=true;

  return cf;
}

String FBCmd::stringify(Cmd_Frame &cf,bool completely){
  String str="";
  if (cf.type==CMD_SYN){
    str+=CMD_TYPE_SYN;
  }else{
    str+=CMD_TYPE_ACK;
  }
  if ((completely)||(cf.id>0)) str+='{'+String(cf.id)+'}';
  if ((completely)||(cf.addr_t!="0000")) str+=cf.addr_t+":";
  if ((completely)||(cf.addr_s!="0000")) str+=cf.addr_s+":";
  str+=cf.cmd;
  str+='('+cf.data+')';

  if (setting->auto_crc){
  //  Serial.println("auto crc");
    str+=":"+crc16.checksumToHexStr(str);
  }

  str+=CMD_FLAG_END;
  if (setting->end_char[0]!=0x00) str+=setting->end_char[0];
  if (setting->end_char[1]!=0x00) str+=setting->end_char[1];


  return str;
}

Cmd_Frame FBCmd::run(Cmd_Frame &cf){


  Cmd_Frame rcf;
  rcf.result=false;
  if (cf.id>0) rcf.id=cf.id+1;
  rcf.type=CMD_ACK;
  rcf.addr_s=get_address();
  rcf.addr_t=cf.addr_s;
  rcf.cmd=cf.cmd;

  if ((cf.result)&&(cf.type==CMD_SYN)){
    std::vector<Cmd_Map> flist = getFunc(cf.cmd);
    int size=flist.size();
    for(int i=0; i<size; i++) {
      Cmd_Map act=flist.at(i);
      if(act.func!=NULL){
        rcf.result=true;
        rcf.status++;
        (*act.func)(cf,rcf);
      }
    }
  }
  return rcf;
}
String FBCmd::run(String cmd,String data){
  String res="";
  Cmd_Frame cf;
  cf.result=true;
  cf.cmd=cmd;
  cf.data=data;
  Cmd_Frame result=run(cf);
  if (result.result){
    res=result.data;
  }
  return res;
}

void FBCmd::runACK(Cmd_Frame &cf){

  if ((cf.result)&&(cf.type==CMD_ACK)){
    std::vector<Cmd_Map> flist = getFunc(cf.cmd);
    int size=flist.size();
    for(int i=0; i<size; i++) {
      Cmd_Map act=flist.at(i);
      if(act.callback!=NULL){
        (*act.callback)(cf);
      }
    }
  }

}
void FBCmd::runACK(String cmd,String data){
  Cmd_Frame cf;
  cf.result=true;
  cf.type=CMD_ACK;
  cf.cmd=cmd;
  cf.data=data;
  runACK(cf);
}
std::vector<Cmd_Map> FBCmd::getFunc(String &key) {
  std::vector<Cmd_Map> flist;
  int count=map.size();
  for (int i = 0; i < count; i++){
    if (map.at(i).name==key){
      flist.push_back(map.at(i));
    }
  }
  return flist;
}
void FBCmd::serialOut(Cmd_Frame rcf,bool completely){
  serialOut(stringify(rcf,completely));
}
void FBCmd::serialOut(String data){
  if (setting->quiet) return;
  int len=data.length();
  for (int i = 0; i < len; i++) {
    serial->write(data.charAt(i));
  }
}
void FBCmd::loop(){
  while(serial->available()){
    loop_cf=receive(serial->read());
    if (loop_cf.result){
      if (loop_cf.type==CMD_SYN){
        serialOut(run(loop_cf));
      }else{
        runACK(loop_cf);
      }

    }
  }
}
