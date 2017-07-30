#ifndef FLYBOARD_FBCMD
#define FLYBOARD_FBCMD

#include <Arduino.h>
#include "../System/algorithm/CRC16.h"
#include "../System/STL/vector"
#include "../System/FBSettings/FBSettings.h"
#include "../FBSerial/FBSerial.h"

#ifndef CMD_BUFFER_MAX
  #define CMD_BUFFER_MAX  128 //max buffer
#endif
#ifndef CMD_TYPE_SYN
  #define CMD_TYPE_SYN '-'
#endif
#ifndef CMD_TYPE_ACK
  #define CMD_TYPE_ACK '+'
#endif
#ifndef CMD_FLAG_END
  #define CMD_FLAG_END ';'
#endif

enum CMDTYPE {
  CMD_SYN=0,
  CMD_ACK=1,
 };
 struct Cmd_Frame{
   bool result=false;
   uint16_t id=0;
   CMDTYPE type=CMD_SYN;
   String addr_t="0000";
   String addr_s="0000";
   String cmd="";
   String data="";
   int status=0;
   uint16_t crc=0;
   void out(String _d){
     this->data+=_d;
   }

 };
  typedef void (*funcP)(Cmd_Frame &input,Cmd_Frame &output);
  typedef void (*funcPcallback)(Cmd_Frame &input);
  struct Cmd_Map{
        String name;
        funcP func;
        funcPcallback callback;
  };


	//std::vector<Cmd_Map> CMDList;

  struct Settings_FBCmd:virtual public FBSettings
  {
    bool echo=false;//是否启用输入回显
    bool quiet=false;//是否启用安静模式，安静模式无任何返回，包括应答帧也不会发送
    char address[4]={'0','0','0','0'};//当前设备地址
    char end_char[2]={0,0};//帧结束附加发送的结束字符，如回车符
    bool auto_crc=true;//发送消息自动添加crc校验
    bool required_crc=false;//解析消息必须验证crc，如果为true，没有crc的命令帧将被丢弃
    void* Cmd=NULL;//指向当前FBCmd实例的指针

  };

  class FBCmd
  {
    private:

      String cmd_str="";
      int cmd_len=0;
      Cmd_Frame receive_cf;
      Cmd_Frame loop_cf;
      //获取key对应的函数指针
      std::vector<Cmd_Map> getFunc(String &key);



    public:
      std::vector<Cmd_Map> map;
      Settings_FBCmd* setting=NULL;
      FBSerial* serial=NULL;
      CRC16 crc16;

      static void null(Cmd_Frame &input){};

      FBCmd();
      ~FBCmd();
      //调试
      void Debug_map(std::vector<Cmd_Map> &map);
      void Debug_map();
      void Debug_setting();
      void Debug_CF(Cmd_Frame &cf);

      //加载配置
      void load_setting(Settings_FBCmd &_setting);
      void load_serial(FBSerial &_serial);

      //串口绑定
      void bind(FBSerial &_serial,Settings_FBCmd &_setting);


      //设置
      void set_Endchar(uint8_t c1,uint8_t c2);
      String get_address();
      void set_address(String address);
      void quiet(bool enable);
      void quiet(String enable);
      void echo(bool enable);
      void echo(String enable);

      //设置函数列表
      void add_map(std::vector<Cmd_Map> &_map);
      void add_map(Cmd_Map _map);
      void add_map(Cmd_Map _map[],int _count);
      void set_map(std::vector<Cmd_Map> &_map);


      //解析
      Cmd_Frame receive(char receiveVal);
      Cmd_Frame parse(String &cmd);

      //运行命令
      Cmd_Frame run(Cmd_Frame &cf);
      //运行回调
      void runACK(Cmd_Frame &cf);

      //序列化
      String stringify(Cmd_Frame &cf,bool completely=false);

      void serialOut(Cmd_Frame rcf,bool completely=false);
      void serialOut(String data);

      //loop
      void loop();

  };




#endif
