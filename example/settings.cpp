#include <Arduino.h>

#include "../FBSettings.h"

struct cmdsetting
{
  int aaa;
  void loadDefault(){
    this->aaa=999;
  };
};


typedef struct Settings:FBSettings,cmdsetting
{
   Settings(){
     this->_setSize(sizeof(*this));
     this->load();
   };
   void loadDefault(){
     this->cmdsetting::loadDefault();


     this->init3=33;
     this->init4=555;


   };

   char   a;
   unsigned int   init3;
   unsigned int   init4;

}Settings;





void setup() {

Serial.begin(115200);
 Settings setting;
 Serial.println(F(" --- "));
 char a=setting.a;
 Serial.println(a);
 delay(100);
 setting.a='a';
 Serial.println(setting.a);
 delay(100);
 setting.a='d';
 setting.save();
}

void loop() {

}
