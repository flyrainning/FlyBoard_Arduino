
#ifndef _FBSETTINGS_H_
#define _FBSETTINGS_H_
#include "Arduino.h"

#include "EEPROM.h"


#ifndef SETTINGS_EEPROM_START_ADDRESS
  #define SETTINGS_EEPROM_START_ADDRESS    0     // Start Address in EEPROM
#endif

#ifndef SETTINGS_EEPROM_MAXSIZE
  #define SETTINGS_EEPROM_MAXSIZE             1022  // EEPROM size
#endif


#ifndef SETTINGS_VERSION_INT
  #define SETTINGS_VERSION_INT            1  //default version
#endif

//struct FBSettings
struct FBSettings
{
   uint16_t _version=SETTINGS_VERSION_INT; //默认版本
   unsigned int _save_address=SETTINGS_EEPROM_START_ADDRESS;// Start Address in EEPROM
   unsigned int _save_size=0;// 实际使用的EEPROM大小，不包括前2个byte
   void* _setting;//实际配置结构体的首地址，仅用于load()和save()

   void bind(void* __setting,unsigned int _size,uint16_t version){
     _setting=__setting;
     this->_setSize(_size);
     this->load(version);
   }
   void load(){
     load(_version);
   }
   void load(uint16_t version){
     _version=version;
     if ((_save_size>1)&&(_save_size<SETTINGS_EEPROM_MAXSIZE)){
       if (version==load_version()){
         unsigned int _save_address_tmp=_save_address;
         unsigned int _save_size_tmp=_save_size;
         void* _setting_tmp=_setting;

         for (unsigned int count=0; count < _save_size_tmp; count++){
           ((unsigned char*)_setting_tmp)[count]=EEPROM.read(_save_address_tmp+count+2);
         }

         _save_address=_save_address_tmp;
         _save_size=_save_size_tmp;
         _setting=_setting_tmp;
       }else{//保存默认配置
         save();
       }
     }

   };
   void save(){
     save_version(this->_version);
     unsigned int _save_address_tmp=_save_address;
     unsigned int _save_size_tmp=_save_size;
     void* _setting_tmp=_setting;
     for (unsigned int count=0; count<_save_size_tmp; count++){
       EEPROM.write(_save_address_tmp + count +2, ((unsigned char*)_setting_tmp)[count]);
     }
   };
   uint16_t load_version(){
     uint16_t DataL = EEPROM.read(_save_address);
     uint16_t DataH = EEPROM.read(_save_address+1);
     return ((DataH<<8) + DataL);
   }
   void save_version(uint16_t Data){
     uint16_t DataL = Data&0x00FF;
     uint16_t DataH = Data>>8;
     EEPROM.write(_save_address,   DataL);
     EEPROM.write(_save_address+1, DataH);

   }
   void clear(){
     unsigned int _save_address_tmp=_save_address;
     unsigned int _save_size_tmp=_save_size;
     for (unsigned int count=0; count<_save_size_tmp+2; count++){
         EEPROM.write(_save_address_tmp + count,0);
     }
   };
   unsigned int _getSize(){
     return this->_save_size+2;
   };
   void _setSize(unsigned int size){
     if (size<=SETTINGS_EEPROM_MAXSIZE)
     this->_save_size=size;
   };

   unsigned int _getAddress(){
     return this->_save_address;
   };
   void _setAddress(unsigned int addr){
     this->_save_address=addr;
   };
   void debug(){
     debug(_setting,_save_size);
   }
   void debug(void* s,unsigned int size){
     Serial.println(F("Setting debug ----------"));
     Serial.print(F("Setting size :"));
     Serial.println(size);
     for (unsigned int count=0; count<size; count++){
       Serial.println(((unsigned char*)s)[count]);
     }
     Serial.println(F("Setting debug -------end"));
   }


};



#endif
