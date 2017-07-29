#include <Arduino.h>
#include "flyboard.h"


typedef struct Settings:
  virtual public Settings_FBCmd
{
uint16_t  _version=1;

  Settings(){
    bind(this,sizeof(*this),_version);
  }


}Settings;
