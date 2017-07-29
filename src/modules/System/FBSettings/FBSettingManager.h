
//这是采用配置管理器的版本，弃用
//保留此文件仅供参考

#ifndef _FBSETTINGSMANAGER_H_
#define _FBSETTINGSMANAGER_H_

#include "FBSettings.h"


#include "EEPROM.h"


#ifndef SETTINGS_EEPROM_START_ADDRESS
  #define SETTINGS_EEPROM_START_ADDRESS    0     // Start Address in EEPROM
#endif

#ifndef SETTINGS_EEPROM_MAXSIZE
  #define SETTINGS_EEPROM_MAXSIZE             1022  // EEPROM size
#endif




class FBSettingManager
{

private:
  unsigned int _save_address=SETTINGS_EEPROM_START_ADDRESS;
  unsigned int _save_size=0;
  unsigned int _start_address=0;
  uint16_t load_version();
  void save_version(uint16_t Data);

public:
  void* setting;
  // virtual void loadDefault()=0;

  FBSettingManager();


  void debug();
  void debug(void* s,int size);

  void bind(void* _setting,unsigned int _size,uint16_t version=SETTINGS_VERSION_INT);

  void load(unsigned int version=SETTINGS_VERSION_INT);
  unsigned int get_version();
  void save();
  void clear();
  unsigned int _getSize();
  void _setSize(unsigned int size);
  unsigned int _getAddress();
  void _setAddress(unsigned int addr);

};

#endif
