#include "Arduino.h"
#include "FBSettingManager.h"



FBSettingManager::FBSettingManager(){}

void FBSettingManager::debug(){
  debug(setting,_save_size);
}
void FBSettingManager::debug(void* s,int size){
  Serial.println(F("Setting debug ----------"));
  Serial.print(F("Setting size :"));
  Serial.println(size);
  for (unsigned int count=0; count<size; count++){
    Serial.println(((unsigned char*)s)[count]);
  }
  Serial.println(F("Setting debug -------end"));
}


 void FBSettingManager::bind(void* _setting,unsigned int _size,uint16_t version){

   setting=_setting;
   _start_address=_save_address+2;
   this->_setSize(_size);
   this->load(version);
 }
 uint16_t FBSettingManager::load_version(){
   uint16_t DataL = EEPROM.read(_save_address);
   uint16_t DataH = EEPROM.read(_save_address+1);
   return ((DataH<<8) + DataL);
 }
 void FBSettingManager::save_version(uint16_t Data){
   uint16_t DataL = Data&0x00FF;
   uint16_t DataH = Data>>8;
   EEPROM.write(_save_address,   DataL);
   EEPROM.write(_save_address+1, DataH);

 }
 void FBSettingManager::load(uint16_t version){
Serial.println("ver:");
Serial.println(version);
   if ((_save_size>1)&&(_save_size<SETTINGS_EEPROM_MAXSIZE)){
     if (((FBSettings*)setting)->_version==load_version()){
       for (unsigned int count=0; count < _save_size; count++){
         ((unsigned char*)setting)[count]=EEPROM.read(_start_address+count);
       }
       Serial.println("load:");
       debug();
     }else{//保存默认配置
       Serial.println("save:");
       save();
     }
   }

 };
 unsigned int FBSettingManager::get_version(){
   return load_version();
 }
 void FBSettingManager::save(){
   save_version(((FBSettings*)setting)->_version);
   for (unsigned int count=0; count<_save_size; count++){
     EEPROM.write(_start_address + count, ((unsigned char*)setting)[count]);
   }
 };
 void FBSettingManager::clear(){
   for (unsigned int count=0; count<_save_size+2; count++){
       EEPROM.write(_start_address + count,0);
   }
 };
 unsigned int FBSettingManager::_getSize(){
   return this->_save_size;
 };
 void FBSettingManager::_setSize(unsigned int size){
   if (size<=SETTINGS_EEPROM_MAXSIZE)
   this->_save_size=size;
 };
 unsigned int FBSettingManager::_getAddress(){
   return this->_save_address;
 };
 void FBSettingManager::_setAddress(unsigned int addr){
   this->_save_address=addr;
 };
