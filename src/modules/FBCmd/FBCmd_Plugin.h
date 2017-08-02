#ifndef FLYBOARD_FBCMDPLUGIN
#define FLYBOARD_FBCMDPLUGIN

#include "FBCmd.h"


class FBCmd_Plugin{

public:

  FBSerial* serial=NULL;
  FBCmd* cmd=NULL;

  void bind_FBCmd(FBCmd &_cmd){
    cmd=&_cmd;
    serial=cmd->serial;
  }
  void cmd2(Cmd_Frame &input,Cmd_Frame &output){
    String p=input.data;
    output.out("I'm cmd2");

  }



};


#endif
