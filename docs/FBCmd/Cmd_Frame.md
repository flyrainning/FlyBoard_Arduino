# Cmd_Frame



```
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
  void out(String _d);
};
```
