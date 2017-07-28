#ifndef FLYBOARD_FBCMDBASE
#define FLYBOARD_FBCMDBASE

#include "FBCmd.h"

#ifdef USE_Example

struct Settings_FBCmd_base:virtual public Settings_FBCmd
{
  bool echo2;
};

class FBCmd_base{
private:

public:

  Settings_FBCmd_base* setting=NULL;
  FBSerial* serial=NULL;
  FBCmd* Cmd=NULL;
  void bind(FBCmd &_cmd,Settings_FBCmd_base &_setting){
    cmd=&_cmd;
    setting=&_setting;
    serial=cmd->serial;
    init_map();
  }
  void init_map(){
    struct Cmd_Map m[]={
      {"set2",&FBCmd_base::bb},
      {"set3",&FBCmd_base::bb}
    };
    cmd->add_map(m,sizeof(m));

    cmd->add_map(Cmd_Map{"set3",&FBCmd_base::bb});
  }
  static String bb(String p){
    return "end bb";
  }


};

#endif

#endif
