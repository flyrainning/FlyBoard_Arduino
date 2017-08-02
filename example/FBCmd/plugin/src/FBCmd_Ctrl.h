#include <Arduino.h>
#include "flyboard.h"

class FBCmd_Ctrl:public FBCmd_Plugin
{

public:

  FBCmd_Ctrl(FBCmd &_cmd){
    bind_FBCmd(_cmd);

    cmd->add_map(Cmd_Map{"a",&FBCmd_Ctrl::a});


  }


};
