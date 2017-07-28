
#ifndef _SETTINGS_H_
#define _SETTINGS_H_


/*
struct cmdsetting
{
  int aaa;
  void loadDefault(){
    this->aaa=999;
  };
};


typedef struct Settings:FBSettings,cmdsetting
{
   init(){
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

Settings setting;

*/

#include "EEPROM.h"


#ifndef SETTINGS_EEPROM_START_ADDRESS
  #define SETTINGS_EEPROM_START_ADDRESS    0     // Start Address in EEPROM
#endif

#ifndef SETTINGS_EEPROM_MAXSIZE
  #define SETTINGS_EEPROM_MAXSIZE             1024  // EEPROM size
#endif

#ifndef SETTINGS_INIT_KEY
  #define SETTINGS_INIT_KEY            0xFAAF  //
#endif


struct FBSettings
{
   unsigned int   _init_key=0;
   unsigned int   _save_address=SETTINGS_EEPROM_START_ADDRESS;
   unsigned int   _save_size=0;
   unsigned char* _p;
  // virtual void loadDefault()=0;


   void EEPROM_write_short(unsigned int Address, unsigned int Data)
   {
      unsigned int DataL = Data&0x00FF;
      unsigned int DataH = Data>>8;
      EEPROM.write(Address,   DataL);
      EEPROM.write(Address+1, DataH);
   };

   // Read an uint value from EEPROM
   unsigned int EEPROM_read_short(unsigned int Address)
   {
      unsigned int DataL = EEPROM.read(Address);
      unsigned int DataH = EEPROM.read(Address+1);
      return((DataH<<8) + DataL);
   };
   void bind(void* p,unsigned int _count){
     //Serial.println("init");
     _p=(unsigned char*)p;
Serial.println("_count");
Serial.println(_count);
     this->_setSize(_count);
  Serial.println(this->_save_size);
     this->load();
  Serial.println(this->_save_size);

    //  for (int Count=0; Count<20; Count++){
    //    Serial.println(_p[Count]);
    //  }
    // Serial.println("over1");
     //EEPROM_read_block(p, this->_save_address, _save_size);
    //  EEPROM.write(2,100);
    //  EEPROM.write(5,98);
    //  unsigned int Count = 0;
    //  for (Count=0; Count<20; Count++){
    //    unsigned char r=EEPROM.read(Count);
        // *(_p+Count)= r;
  //       _p[Count]=r;
    //     memcpy(_p[Count],&r,1);
      //   Serial.println(r);
  //    }
    //  Serial.println("over3");
    //  for (int Count=0; Count<20; Count++){
    //    Serial.println(_p[Count]);
    //  }
    //  Serial.println("over2");
    //  delay(100000);

   }
   void load(){
     if ((this->_save_size>6)&&(this->_save_size<SETTINGS_EEPROM_MAXSIZE)){
       unsigned int _save_size_tmp=this->_save_size;
       unsigned int _save_address_tmp=this->_save_address;
       unsigned char* _p_tmp=_p;

       for (unsigned int count=0; count < _save_size_tmp; count++){
         _p[count]=EEPROM.read(_save_address_tmp+count);
       }
       this->_save_size=_save_size_tmp;
       this->_save_address=_save_address_tmp;
       _p= _p_tmp;
    //   if (this->_init_key!=0xFAAF){
        //  Serial.println("begin");
        //  FBSettings *s=(FBSettings*)_p;
        //  s->loadDefault();
        //  Serial.println("end");
        //  this->_init_key=0xFAAF;
        //  this->save();

    //   }
     }

   };
   bool isFirstRun(){
     return (this->_init_key!=SETTINGS_INIT_KEY);
   }
   void save(){
     this->_init_key=SETTINGS_INIT_KEY;
       Serial.println(_save_size);
     unsigned int max=this->_save_size;
     unsigned int addr=this->_save_address;
     Serial.println(max);
     Serial.println(addr);
     for (unsigned int count=0; count<max; count++){

         EEPROM.write(addr + count, _p[count]);
     }
   };
   void clear(){

     unsigned int max=this->_save_size;
     unsigned int addr=this->_save_address;
     for (unsigned int count=0; count<max; count++){
         EEPROM.write(addr + count,0);
     }
   };
   unsigned int _getSize(){
     return this->_save_size;
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



};

#endif
