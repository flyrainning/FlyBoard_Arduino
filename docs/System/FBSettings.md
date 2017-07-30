# FBSettings

## 功能
提供统一的配置管理接口，可以方便的将各种配置信息保存到EEPROM中。

## 使用方法

FBSettings是一个结构体，必须作为其他结构体的基类使用，采用virtual public方式继承。

使用配置功能时，必须自定义一个结构体，继承FBSettings，同时继承所有用到的模块或插件的配置，形成一个包括所有配置项的子类。实例化为一个唯一的配置对象。

其他模块和插件使用之前一般都要绑定这个配置对象，从而取得配置信息。
配置对象必须调用bind()进行初始化，bind后会自动调用load从EEPROM中加载配置。

`bind(void* __setting,unsigned int _size,uint16_t version)`必须传入当前配置对象的地址，当前配置对象的大小（sizeof），配置版本。

若传入的版本号与EEPROM中当前保存版本相同，则加载EEPROM中配置。若不相同，则加载配置对象默认值，并写入EEPROM进行保存，也就是配置初始化。

## 实例


```

typedef struct Settings:
  virtual public FBSettings,
  //如果有其他插件，在这里继承所有其他插件的配置
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


```

也可只定义配置结构体，在代码中调用bind初始化

```


typedef struct Settings:
  virtual public FBSettings,
  //如果有其他插件，在这里继承所有其他插件的配置
  virtual public Settings_FBCmd
{
//配置项目，只支持定长类型，不要使用String之类或者动态数组
bool boolvalue=true;
char c='c';
char string[3]={'s','t','r'};
int intvalue=256;

}Settings;

void setup() {

 Settings setting;
 setting.bind(&setting,sizeof(setting),10);

 Serial.begin(115200);
 Serial.println(setting.c);
 setting.boolvalue=false;
 setting.save();

}

```

## 可选配置

可通过宏定义修改默认配置，定义应在#include "flyboard.h"之前以保证生效

```
#define SETTINGS_EEPROM_START_ADDRESS    0     // Start Address in EEPROM
#define SETTINGS_EEPROM_MAXSIZE             1022  // EEPROM size
#define SETTINGS_VERSION_INT            1  //default version


```

> FBSettings本身会占用2byte，起始地址+最大长度+2不能大于EEPROM大小


## 属性

|     名称      |                     说明                     |
| ------------- | -------------------------------------------- |
| _version      | 当前配置版本                                 |
| _save_address | 配置保存地址，默认0                          |
| _save_size    | 实际使用的EEPROM大小，不包括前2个byte        |
| _setting      | 实际配置结构体的首地址，仅用于load()和save()内部使用 |

## 主要方法

#### void bind(void* __setting,unsigned int _size,uint16_t version)

> 初始化方法，必须调用此方法后才能正常使用

###### 功能

绑定配置子对象

###### 参数

__setting ：子对象地址
_size ：子对象大小
version ：配置版本


#### void load()

从EEPROM中读取配置信息，使用当前_version中记录的版本

#### void load(uint16_t version)

使用指定版本的load()

#### void save()

保存配置信息到EEPROM，修改配置后需调用save()进行写入

#### void clear()

清空EEPROM中的数据，用0x00覆盖

#### void _setSize(unsigned int size)

设置EEPROM实际保存时占用空间大小，应与子对象实际大小相同，否则会造成配置丢失。

#### unsigned int _getSize()

获取实际占用的EEPROM空间大小

#### unsigned int _getAddress()

获取EEPROM中保存的首地址

#### void _setAddress(unsigned int addr)

设置EEPROM中保存的首地址

#### void debug()

以char的方式通过Serial输出所有配置信息
