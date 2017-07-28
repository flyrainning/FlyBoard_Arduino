#include <Arduino.h>

#include "flyboard.h"

typedef struct Settings:
  virtual public FBSettings,
  //如果有其他插件，在这里继承所有插件的配置
  virtual public Settings_FBCmd
{
uint16_t  _version=1;//配置版本，若版本号与EEPROM中保存的不同，则使用默认配置

//配置项目，只支持定长类型，不要使用String之类或者动态数组
bool boolvalue=true;
char c='c';
char string[3]={'s','t','r'};
int intvalue=256;


  Settings(){//必须调用bind绑定到当前对象之后才能使用
    bind(this,sizeof(*this),_version);
  }


}Settings;


Settings setting;

void setup() {

Serial.begin(115200);

 Serial.println(setting.c);
 setting.boolvalue=false;
 setting.save();

}

void loop() {
  delay(1000);
}
